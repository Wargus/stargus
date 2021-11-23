/*
 * Tbl.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Tbl.h"
#include "Hurricane.h"

// System
#include <iostream>
#include <fstream>
#include <string>
#include <iconv.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

Tbl::Tbl(std::shared_ptr<Hurricane> hurricane) :
	Converter(hurricane),
	mLogger("startool.Tbl")
{

}

Tbl::~Tbl()
{

}

/**
 * TODO: this is just a raw format parser. Not yet decided what to do with the format
 */
bool Tbl::convert(const std::string &arcfile, const std::string &file)
{
	shared_ptr<DataChunk> data = mHurricane->extractDataChunk(arcfile);
	if (data)
	{
		//std::ifstream ifs(arcfile, std::ifstream::binary);
		//kaitai::kstream ks(&ifs);

		// TODO: for now just create from complete string instead of istream. Maybe change the complete
		// reader to stream based concept...
		std::string str( reinterpret_cast<char const*>(data->getDataPointer()), data->getSize() ) ;
		kaitai::kstream ks(str);

		file_tbl_t file_tbl = file_tbl_t(&ks);

		std::vector<file_tbl_t::tbl_entry_t*>* file_tbl_entry_vec = file_tbl.tbl_entries();

		unsigned int i = 0;
		for(vector<file_tbl_t::tbl_entry_t*>::iterator file_tbl_entry_it = file_tbl_entry_vec->begin(); file_tbl_entry_it != file_tbl_entry_vec->end(); file_tbl_entry_it++)
		{
			file_tbl_t::tbl_entry_t *file_entry = *file_tbl_entry_it;

			std::vector<uint8_t> *entry_char_vec = file_entry->entry();

			cout << i << ":";
			//"#entry: " << entry_char_vec->size() << endl;

			uint8_t last_control = 0;
			for(unsigned int n = 0; n < entry_char_vec->size(); n++)
			{
				uint8_t entry_char = entry_char_vec->at(n);

				// ASCII control characters + special chars
				if((entry_char >= 0 && entry_char <= 31) || entry_char == 127 || entry_char == 0x2a)
				{
					switch(entry_char)
					{
					case 0x0: // ' '
						printf("<NULL>");
						break;
					case 0x0a: // Line Feed
						printf("<LF>");
						break;
					case 0x01: // Start of Heading
						printf("<SOH>");
						break;
					case 0x02: // Start of Text
						printf("<STX>");
						break;
					case 0x03: // End of Text
						printf("<ETX>");
						break;
					case 0x4: // End of Transmission, diamonds card suit
						printf("<EOT>");
						break;
					case 0x6: // Acknowledgement, spade card suit
						printf("<ACK>");
						break;
					case 0x7: // Bell
						printf("<BEL>");
						break;
					case 0x1B: // Escape
						printf("<ESC>");
						break;
					case 0x2a: // '*'
						printf("<ASTERISK>");
						break;
					default:
						printf("<unhandled>: %x", entry_char);
						break;
					}

					last_control = entry_char;
				}
				// printable ASCII characters
				else if(entry_char >= 32 && entry_char <= 126)
				{
					printf("%c", entry_char);
				}
				// printable extendes ASCII characters
				else if(entry_char >= 120 && entry_char <= 255)
				{
					//printf("0x%X", entry_char);

					char inBuf[1024];
					inBuf[0] = (char) entry_char;
					inBuf[1] = '\0';
					char *utf8 = iconvISO2UTF8(inBuf);
					cout << utf8;
					free(utf8);
				}
				else
				{
					LOG4CXX_ERROR(mLogger, "ASCII characters > 255 should not be possible!");
				}
			}
			cout << endl;

			i++;
		}
	}


	return true;
}

char *Tbl::iconvISO2UTF8(char *iso)
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

