/*
 * Font.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include <Palette.h>
#include "Font.h"
#include "endian.h"
#include "Png.h"
#include "FileUtil.h"
#include "Storm.h"
#include "Preferences.h"
#include "StringUtil.h"

// C
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/**
**		Path the font files. (default=$DIR/graphics/ui/fonts)
*/
#define FONT_PATH		"graphics/ui/fonts"

using namespace std;

Font::Font(std::shared_ptr<Hurricane> hurricane) :
	mLogger("startool.Font"),
	mHurricane (hurricane)
{

}

Font::~Font()
{

}

/**
**  Convert a font to PNG image format.
**
**  @return true if everything is ok
*/
bool Font::convert(const std::string &arcfile, const std::string &file)
{
	unsigned char* palp;
	unsigned char* image;
	int w;
	int h;
	char buf[8192] = {'\0'};
	bool result = true;
	int pale = 2; // Cmdicons_Palette -> but no Idea why this palette is applied for fonts

	LOG4CXX_TRACE(mLogger, "convert:" + arcfile + "," + file);

	palp = Palettes[pale];

	shared_ptr<DataChunk> data = mHurricane->extractDataChunk(arcfile);
	if (data)
	{
		image = Font::convertImage(data->getDataPointer(), &w, &h);
		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), FONT_PATH, file.c_str());
		CheckPath(buf);
		Png::save(buf, image, w, h, palp, 255);

		free(image);
	}

	return result;
}

typedef struct	_FontHeader {
	char name[5];	//	[0-4] Always is "FONT"
	uint8_t lowIndex;	//	Index of the first letter in file
	uint8_t highIndex;	//	Index of the last letter in file
	uint8_t maxWidth;	//	Maximum width
	uint8_t maxHeight;	//	Maximum height
	//DWORD	Unk1;		//	Unknown / Unused
} FontHeader;

// size of this header struct has to be 4xbyte!
typedef struct  _FontLetterHeader {
	uint8_t width;		//	Width of the letter
	uint8_t height;		//	Height of the letter
	uint8_t xOffset;	//	X Offset for the topleft corner of the letter.
	uint8_t yOffset;	//	Y Offset for the topleft corner of the letter.
} FontLetterHeader;

unsigned char* Font::convertImage(unsigned char* start, int *wp, int *hp)
{
	char buf[1024];
	FontHeader header;
	unsigned char *bp = nullptr;
	unsigned char *image = nullptr;
	unsigned char *dp = nullptr;
	unsigned int *offsets = nullptr;
	int image_width = 0;
	int image_height = 0;

	LOG4CXX_DEBUG(mLogger, "convertImage2");

	bp = start;

	header.name[0] = FetchByte(bp);
	header.name[1] = FetchByte(bp);
	header.name[2] = FetchByte(bp);
	header.name[3] = FetchByte(bp);
	header.name[4] = '\0';

	header.lowIndex = FetchByte(bp);
	header.highIndex = FetchByte(bp);
	header.maxWidth = FetchByte(bp);
	header.maxHeight = FetchByte(bp);

	unsigned int letterCount = header.highIndex - header.lowIndex;

	if(!strncmp(header.name, "FONT", 4))
	{
		sprintf(buf, "li:%i / hi:%i / mw:%i / mh:%i", header.lowIndex, header.highIndex, header.maxWidth, header.maxHeight);
		LOG4CXX_DEBUG(mLogger, string("FONT header found: ") + buf);

		//bp += 2; // DWORD unused

		image_width = header.maxWidth;
		image_height = letterCount * header.maxHeight;
		sprintf(buf, "w:%i / h:%i", image_width, image_height);
		LOG4CXX_DEBUG(mLogger, string("Image size: ") + buf);

		// calculate the offsets for each font letter header
		offsets = (unsigned int*)malloc(letterCount * sizeof(FontLetterHeader));
		for (unsigned int i = 0; i < letterCount; ++i)
		{
			offsets[i] = FetchLE32(bp);
		}

		// allocate the memory to fill with raw image data
		image = (unsigned char *)malloc(image_width * image_height);
		if (!image)
		{
			LOG4CXX_FATAL(mLogger, "Can't allocate image memory");
		}

		// Give image a transparent background
		memset(image, 255, image_width * image_height);

		// do this for all letters
		for(unsigned int i = 0; i < letterCount; i++)
		{
			if (!offsets[i])
			{
				continue;
			}

			FontLetterHeader letter;

			// set pointer to each letter header start...
			bp = start + offsets[i];

			letter.width = FetchByte(bp);
			letter.height = FetchByte(bp);
			letter.xOffset = FetchByte(bp);
			letter.yOffset = FetchByte(bp);
			sprintf(buf, "%i# w:%i / h:%i / x:%i / y:%i", i, letter.width, letter.height, letter.xOffset, letter.yOffset);
			LOG4CXX_DEBUG(mLogger, string("FontLetterRaw: ") + buf);

			dp = image + letter.xOffset + letter.yOffset * header.maxWidth  + i * (header.maxWidth  * header.maxHeight);
			int w = 0;
			int h = 0;

			// copy all data from each letter and convert it
			// who ever coded this algorithm didn't document it - but it seems to work!!
			for (;;) {
				int ctrl;
				ctrl = FetchByte(bp);
				w += (ctrl >> 3) & 0x1F;
				if (w >= letter.width) {
					w -= letter.width;
					++h;
					if (h >= letter.height) {
						break;
					}
				}
				dp[h * header.maxWidth + w] = ctrl & 0x07;
				++w;
				if (w >= letter.width) {
					w -= letter.width;
					++h;
					if (h >= letter.height) {
						break;
					}
				}
			}
		}
	}
	else
	{
		LOG4CXX_WARN(mLogger, "No Font Header found!");
	}

	*wp = header.maxWidth;
	*hp = header.maxHeight * letterCount;

	// free the offset memory as it's not longer used
	free(offsets);

	return image;
}



