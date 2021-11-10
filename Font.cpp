/*
 * Font.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Font.h"
#include "endian.h"
#include "Png.h"
#include "FileUtil.h"
#include "Storm.h"
#include "Preferences.h"
#include "Palettes.h"
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

Font::Font(std::shared_ptr<Hurricane> hurricane) :
	mHurricane (hurricane), mLogger("startool.Font")
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
bool Font::convert(const std::string &arcfile, const std::string &file, int pale)
{
	unsigned char* palp;
	unsigned char* fntp;
	unsigned char* image;
	int w;
	int h;
	char buf[8192] = {'\0'};
	bool result = true;

	LOG4CXX_TRACE(mLogger, "convert:" + arcfile + "," + file);

	palp = Palettes[pale];

	result = mHurricane->extractMemory(arcfile, &fntp, NULL);
	if (result)
	{
		image = Font::convertImage(fntp, &w, &h);
		/*image =*/ Font::convertImage2(fntp, &w, &h);
		free(fntp);
		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), FONT_PATH, file.c_str());
		CheckPath(buf);
		Png::save(buf, image, w, h, palp, 255);

		free(image);
	}

	return result;
}

typedef struct	_FontHeader {
	char name[5];	//	Always is "FONT "
	unsigned int highIndex;	//	Index of the last letter in file
	unsigned int maxWidth;	//	Maximum width
	unsigned int maxHeight;	//	Maximum height
	//DWORD	Unk1;		//	Unknown / Unused
} FontHeader;

typedef struct  _FontLetterRaw {
	unsigned int width;		//	Width of the letter
	unsigned int height;		//	Height of the letter
	unsigned int xOffset;	//	X Offset for the topleft corner of the letter.
	unsigned int yOffset;	//	Y Offset for the topleft corner of the letter.
} FontLetterRaw;


unsigned char* Font::convertImage2(unsigned char* start, int *wp, int *hp)
{
	FontHeader header;

	unsigned char* bp;

	LOG4CXX_DEBUG(mLogger, "convertImage2");

	bp = start;
	header.name[0] = FetchByte(bp);
	header.name[1] = FetchByte(bp);
	header.name[2] = FetchByte(bp);
	header.name[3] = FetchByte(bp);
	header.name[4] = '\0'; FetchByte(bp);

	header.highIndex = FetchByte(bp);
	header.maxWidth = FetchByte(bp);
	header.maxHeight = FetchByte(bp);

	if(strncpy(header.name, "FONT", 5))
	{
		LOG4CXX_DEBUG(mLogger, "FONT header found");
		LOG4CXX_DEBUG(mLogger, "Header: " +
				toString(header.highIndex) + "/" +
				toString(header.maxWidth) + "/" +
				toString(header.maxHeight));

		bp += 2; // DWORD unused

		for(unsigned int i = 0; i < 222; i++) //223 = image size 2899 / 13 => just a hack to understand the algorithm
		{
			FontLetterRaw letter;
			letter.width = FetchByte(bp);
			letter.height = FetchByte(bp);
			letter.xOffset = FetchByte(bp);
			letter.yOffset = FetchByte(bp);
			LOG4CXX_DEBUG(mLogger, "FontLetterRaw: " +
					toString(letter.width) + "/" +
					toString(letter.height) + "/" +
					toString(letter.xOffset) + "/" +
					toString(letter.yOffset));
		}
	}
/*
	bp = start + 5;  // skip "FONT "
	//printf("%s %s \n", start, start + 5);
	count = FetchByte(bp);
	count -= 32;
	max_width = FetchByte(bp);
	max_height = FetchByte(bp);

*/
	return NULL;
}

/**
**  Convert font into raw image data
*/
unsigned char* Font::convertImage(unsigned char* start, int *wp, int *hp)
{
	int i;
	int count;
	int max_width;
	int max_height;
	int width;
	int height;
	int w;
	int h;
	int xoff;
	int yoff;
	unsigned char* bp;
	unsigned char* dp;
	unsigned char* image;
	unsigned* offsets;
	int image_width;
	int image_height;
	int IPR;

	bp = start + 5;  // skip "FONT "
	//printf("%s %s \n", start, start + 5);
	count = FetchByte(bp);
	count -= 32;
	max_width = FetchByte(bp);
	max_height = FetchByte(bp);

	IPR = 15;  // 15 characters per row
	image_width = max_width * IPR;
	image_height = (count + IPR - 1) / IPR * max_height;

//	printf("Font: count %d max-width %2d max-height %2d\n",
//		count, max_width, max_height);

	offsets = (unsigned *)malloc(count * sizeof(uint32_t));
	for (i = 0; i < count; ++i) {
		offsets[i] = FetchLE32(bp);
//		printf("%03d: offset %d\n", i, offsets[i]);
	}

	image = (unsigned char *)malloc(image_width * image_height);
	if (!image) {
		printf("Can't allocate image\n");
		// TODO: more flexible error handling than calling GUI dialog from conversation routine needed
		//error("Memory error", "Could not allocate enough memory to read archive.");
	}
	memset(image, 255, image_width * image_height);

	for (i = 0; i < count; ++i) {
		if (!offsets[i]) {
//			printf("%03d: unused\n", i);
			continue;
		}
		bp = start + offsets[i];
		width = FetchByte(bp);
		height = FetchByte(bp);
		xoff = FetchByte(bp);
		yoff = FetchByte(bp);

//		printf("%03d: width %d height %d xoff %d yoff %d\n",
//			i, width, height, xoff, yoff);

		dp = image + xoff + yoff * max_width + i * (max_width * max_height);
		h = w = 0;
		for (;;) {
			int ctrl;
			ctrl = FetchByte(bp);
			w += (ctrl >> 3) & 0x1F;
			if (w >= width) {
				w -= width;
				++h;
				if (h >= height) {
					break;
				}
			}
			dp[h * max_width + w] = ctrl & 0x07;
			++w;
			if (w >= width) {
				w -= width;
				++h;
				if (h >= height) {
					break;
				}
			}
		}
	}
	free(offsets);

	*wp = max_width;
	*hp = max_height * count;

	return image;
}


