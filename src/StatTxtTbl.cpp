/*
 * Tbl.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Hurricane.h"
#include "StringUtil.h"

// System
#include <iostream>
#include <fstream>
#include <string>
#include <iconv.h>
#include <string.h>
#include <stdlib.h>
#include "StatTxtTbl.h"

using namespace std;

// this is a very local debug print concept. But for this use case of sequence character debugging perfect...
int no_printf(const char *format, ...){	return 0;}
//#define dbg_printf printf
#define dbg_printf no_printf

StatTxtTbl::StatTxtTbl() :
	mLogger("startool.StatTxtTbl")
{

}

StatTxtTbl::~StatTxtTbl()
{

}

/**
 * TODO: this is just a raw format parser. Not yet decided what to do with the format
 * a debug output looks like this if you uncomment the printf() below. The format isn't yet complete
 * understood. But somehow there're shortcuts and a marker which char should be highlighted in the GUI...
 * r<EOT>Pa<ETX>r<SOH>asit entwickeln<LF>(Für Königin)<NULL>
 */
vector<TblEntry> StatTxtTbl::convertFromStream(std::shared_ptr<kaitai::kstream> ks)
{
	file_tbl_t file_tbl = file_tbl_t(ks.get());

	std::vector<file_tbl_t::tbl_entry_t*>* file_tbl_entry_vec = file_tbl.tbl_entries();

	unsigned int i = 0;
	vector<TblEntry> tbl_entry_vec;
	for(vector<file_tbl_t::tbl_entry_t*>::iterator file_tbl_entry_it = file_tbl_entry_vec->begin(); file_tbl_entry_it != file_tbl_entry_vec->end(); file_tbl_entry_it++)
	{
		file_tbl_t::tbl_entry_t *file_entry = *file_tbl_entry_it;

		std::vector<uint8_t> *entry_char_vec = file_entry->entry();

		dbg_printf("%d:", i);

		//"#entry: " << entry_char_vec->size() << endl;

		//uint8_t last_control = 0;
		TblEntry tbl_entry;
		string entry_str_tmp;
		unsigned int null_counter = 0;
		for(unsigned int n = 0; n < entry_char_vec->size(); n++)
		{
			uint8_t entry_char = entry_char_vec->at(n);

			// ASCII control characters + special chars
			if((entry_char >= 0 && entry_char <= 31) || entry_char == 127 || entry_char == 0x2a)
			{
				switch(entry_char)
				{
				case 0x0: // ' '
					dbg_printf("<NULL>");
					if(null_counter == 0)
					{
						tbl_entry.name = entry_str_tmp;
						entry_str_tmp.clear();
					}
					else if(null_counter == 1)
					{
						tbl_entry.category1 = entry_str_tmp;
						entry_str_tmp.clear();
					}
					else if(null_counter == 2)
					{
						tbl_entry.category2 = entry_str_tmp;
						entry_str_tmp.clear();
					}
					null_counter++;
					break;
				case 0x0a: // Line Feed
					dbg_printf("<LF>");
					entry_str_tmp += " ";
					break;
				case 0x01: // Start of Heading
					dbg_printf("<SOH>");
					break;
				case 0x02: // Start of Text
					dbg_printf("<STX>");
					tbl_entry.shortcut = entry_char_vec->at(n-1);
					entry_str_tmp.clear();
					break;
				case 0x03: // End of Text
					dbg_printf("<ETX>");
					tbl_entry.shortcut_pos = entry_str_tmp.length();
					break;
				case 0x4: // End of Transmission, diamonds card suit
					dbg_printf("<EOT>");
					if(n > 0)
					{
						tbl_entry.shortcut = entry_char_vec->at(n-1);
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
			else if(entry_char >= 32 && entry_char <= 126)
			{
				dbg_printf("%c", entry_char);

				entry_str_tmp += entry_char;
			}
			// printable extendes ASCII characters
			else if(entry_char >= 120 && entry_char <= 255)
			{
				char inBuf[1024];
				inBuf[0] = (char) entry_char;
				inBuf[1] = '\0';
				// TODO: valgrind detects this as problem:
				char *utf8 = iconvISO2UTF8(inBuf);
				if(utf8)
				{
					dbg_printf("%s", utf8);

					entry_str_tmp += utf8;
					free(utf8);
				}
				else
				{
					LOG4CXX_ERROR(mLogger, "No UTF-8 conversation possible!");
				}
			}
			else
			{
				LOG4CXX_ERROR(mLogger, "ASCII characters > 255 should not be possible!");
			}
		}
		dbg_printf("\n");

		i++;
		tbl_entry_vec.push_back(tbl_entry);
	}

	return tbl_entry_vec;
}

// TODO: check if this helps to detect encoding https://github.com/freedesktop/uchardet
char *StatTxtTbl::iconvISO2UTF8(char *iso)
{
	char buf[1024] = {'\0'};
    iconv_t iconvDesc = iconv_open ("UTF-8//TRANSLIT//IGNORE", "ISO−8859-1");

    if (iconvDesc == (iconv_t) - 1) {
        /* Something went wrong.  */
        if (errno == EINVAL)
        {
        	snprintf(buf, sizeof(buf), "conversion from '%s' to '%s' not available", "ISO−8859−1", "UTF-8");
        	LOG4CXX_ERROR(mLogger, buf);
        }
        else
        {
        	snprintf(buf, sizeof(buf), "LibIcon initialization failure");
        }

        return NULL;
    }

    size_t iconv_value;
    char * utf8;
    size_t len;
    size_t utf8len;
    char * utf8start;

    len = strlen (iso);
    if (! len)
    {
    	snprintf(buf, sizeof(buf), "iconvISO2UTF8: input String is empty.");
    	LOG4CXX_ERROR(mLogger, buf);
        return NULL;
    }

    /* Assign enough space to put the UTF-8. */
    utf8len = 2 * len;
    utf8 = (char*) calloc (utf8len, sizeof (char));
    if (! utf8)
    {
    	snprintf(buf, sizeof(buf), "iconvISO2UTF8: Calloc failed.");
    	LOG4CXX_ERROR(mLogger, buf);
        return NULL;
    }
    /* Keep track of the variables. */
    utf8start = utf8;

    iconv_value = iconv (iconvDesc, & iso, & len, & utf8, & utf8len);
    /* Handle failures. */
    if (iconv_value == (size_t) - 1)
    {
        switch (errno)
        {
                /* See "man 3 iconv" for an explanation. */
            case EILSEQ:
                snprintf(buf, sizeof(buf), "iconv failed: Invalid multibyte sequence, in string '%s', length %d, out string '%s', length %d\n", iso, (int) len, utf8start, (int) utf8len);
                LOG4CXX_ERROR(mLogger, buf);
                break;
            case EINVAL:
            	snprintf(buf, sizeof(buf), "iconv failed: Incomplete multibyte sequence, in string '%s', length %d, out string '%s', length %d\n", iso, (int) len, utf8start, (int) utf8len);
            	LOG4CXX_ERROR(mLogger, buf);
                break;
            case E2BIG:
            	snprintf(buf, sizeof(buf), "iconv failed: No more room, in string '%s', length %d, out string '%s', length %d\n", iso, (int)  len, utf8start, (int) utf8len);
            	LOG4CXX_ERROR(mLogger, buf);
                break;
            default:
            	snprintf(buf, sizeof(buf), "iconv failed, in string '%s', length %d, out string '%s', length %d\n", iso, (int) len, utf8start, (int) utf8len);
            	LOG4CXX_ERROR(mLogger, buf);
        }
        return NULL;
    }


    if(iconv_close (iconvDesc) != 0) {
    	snprintf(buf, sizeof(buf), "libicon close failed: %s", strerror (errno));
        LOG4CXX_ERROR(mLogger, buf);
    }

    return utf8start;

}

