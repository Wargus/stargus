/*
 * Tbl.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Hurricane.h"
#include "StringUtil.h"
#include "Tbl.h"
#include "Logger.h"

// System
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace dat {

static Logger logger = Logger("startool.DataHub.Tbl");

// this is a very local debug print concept. But for this use case of sequence character debugging perfect...
int no_printf(const char *format, ...)
{
  return 0;
}
//#define dbg_printf printf
#define dbg_printf no_printf

Tbl::Tbl()
{

}

Tbl::~Tbl()
{

}

/**
 * TODO: this is just a raw format parser. Not yet decided what to do with the format
 * a debug output looks like this if you uncomment the printf() below. The format isn't yet complete
 * understood. But somehow there're shortcuts and a marker which char should be highlighted in the GUI...
 * r<EOT>Pa<ETX>r<SOH>asit entwickeln<LF>(Für Königin)<NULL>
 */
vector<TblEntry> Tbl::convertFromStream(std::shared_ptr<kaitai::kstream> ks)
{
  file_tbl_t file_tbl = file_tbl_t(ks.get());

  std::vector<file_tbl_t::tbl_entry_t *> *file_tbl_entry_vec = file_tbl.tbl_entries();

  unsigned int i = 0;
  vector<TblEntry> tbl_entry_vec;
  for (vector<file_tbl_t::tbl_entry_t *>::iterator file_tbl_entry_it =
         file_tbl_entry_vec->begin();
       file_tbl_entry_it != file_tbl_entry_vec->end(); file_tbl_entry_it++)
  {
    file_tbl_t::tbl_entry_t *file_entry = *file_tbl_entry_it;

    std::vector<uint8_t> *entry_char_vec = file_entry->entry();

    dbg_printf("%d:", i);

    //"#entry: " << entry_char_vec->size() << endl;

    //uint8_t last_control = 0;

    std::string name1;
    std::string name2;
    std::string name3;
    int shortcut_pos = -1;
    std::string shortcut;

    string entry_str_tmp;
    unsigned int null_counter = 0;
    bool etx = false;
    for (unsigned int n = 0; n < entry_char_vec->size(); n++)
    {
      uint8_t entry_char = entry_char_vec->at(n);

      // ASCII control characters + special chars
      if ((entry_char >= 0 && entry_char <= 31) || entry_char == 127
          || entry_char == 0x2a)
      {
        switch (entry_char)
        {
        case 0x0: // ' '
          dbg_printf("<NULL>");
          if (n == 1) // first char is shortcut special case
          {
            uint8_t last = entry_char_vec->at(n - 1);
            // TODO: special handling of ESC key if I ever come to this point...
            if (last != 0x1B) // !Escape
            {
              shortcut = last;
              entry_str_tmp.clear();
            }
          }
          else
          {
            if (null_counter == 0)
            {
              name1 = entry_str_tmp;
              entry_str_tmp.clear();
            }
            else if (null_counter == 1)
            {
              name2 = entry_str_tmp;
              entry_str_tmp.clear();
            }
            else if (null_counter == 2)
            {
              name3 = entry_str_tmp;
              entry_str_tmp.clear();
            }
            null_counter++;
          }
          break;
        case 0x0a: // Line Feed
          dbg_printf("<LF>");
          entry_str_tmp += " ";
          break;
        case 0x01: // Start of Heading
          dbg_printf("<SOH>");
          if (!etx) // <ETX><SOH> is a special case
          {
            shortcut = entry_char_vec->at(n - 1);
            entry_str_tmp.clear();
          }
          break;
        case 0x02: // Start of Text
          dbg_printf("<STX>");
          shortcut = entry_char_vec->at(n - 1);
          entry_str_tmp.clear();
          break;
        case 0x03: // End of Text
          dbg_printf("<ETX>");
          if (n == 1) // first char is shortcut special case
          {
            shortcut = entry_char_vec->at(n - 1);
            entry_str_tmp.clear();
          }
          else
          {
            shortcut_pos = entry_str_tmp.length();
            etx = true;
          }
          break;
        case 0x4: // End of Transmission, diamonds card suit
          dbg_printf("<EOT>");
          if (n > 0)
          {
            shortcut = entry_char_vec->at(n - 1);
            entry_str_tmp.clear();
          }
          break;
        case 0x6: // Acknowledgement, spade card suit
          dbg_printf("<ACK>");
          break;
        case 0x7: // Bell
          dbg_printf("<BEL>");
          break;
        case 0x1B: // Escape
          dbg_printf("<ESC>");
          break;
        case 0x2a: // '*'
          dbg_printf("<ASTERISK>");
          entry_str_tmp += entry_char;
          break;
        default:
          dbg_printf("<unhandled>: %x", entry_char);
          break;
        }

        //last_control = entry_char;
      }
      // printable ASCII characters
      else if (entry_char >= 32 && entry_char <= 126)
      {
        dbg_printf("%c", entry_char);
        entry_str_tmp += entry_char;
      }
      // printable extended ASCII characters
      else if (entry_char >= 120 && entry_char <= 255)
      {
        char inBuf[2];
        inBuf[0] = (char) entry_char;
        inBuf[1] = '\0';

        char *utf8 = iconvISO2UTF8(inBuf);
        if (utf8)
        {
          dbg_printf("%s", utf8);

          entry_str_tmp += utf8;
          free(utf8);
        }
        else
        {
          LOG4CXX_ERROR(logger, "No UTF-8 conversation possible!");
        }
      }
      else
      {
        LOG4CXX_ERROR(logger, "ASCII characters > 255 should not be possible!");
      }
    }
    dbg_printf("\n");

    // fix trailing characters
    if (shortcut == " ")
    {
      shortcut = "";
    }

    removeDoubleSpaces(name1);
    removeDoubleSpaces(name2);
    removeDoubleSpaces(name3);

    // access the tbl_entry members direct for now as this is a friend class.
    // maybe I change this design later, but for now it's ok
    TblEntry tbl_entry;
    tbl_entry.m_name1 = name1;
    tbl_entry.m_name2 = name2;
    tbl_entry.m_name3 = name3;
    tbl_entry.m_shortcut = shortcut;
    tbl_entry.m_shortcut_pos = shortcut_pos;


    dbg_printf("tbl_entry.name(): %s\n", tbl_entry.name1().c_str());
    dbg_printf("tbl_entry.category1(): %s\n", tbl_entry.name2().c_str());
    dbg_printf("tbl_entry.category2(): %s\n", tbl_entry.name3().c_str());
    dbg_printf("tbl_entry.shortcut(): %s\n", tbl_entry.shortcut().c_str());
    dbg_printf("tbl_entry.shortcut_pos(): %d\n", tbl_entry.shortcut_pos());

    i++;


    tbl_entry_vec.push_back(tbl_entry);
  }

  return tbl_entry_vec;
}

void Tbl::removeDoubleSpaces(std::string &str)
{
  size_t pos;
  while ((pos = str.find("  ")) != std::string::npos)
  {
    str = str.replace(pos, 2, " ");
  }
}

} /* namespace dat */
