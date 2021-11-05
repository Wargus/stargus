/*
 * Pcx.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "endian.h"
#include "Pcx.h"
#include "Preferences.h"
#include "Storm.h"
#include "Png.h"

// System
#include <stdlib.h>
#include <string.h>

Pcx::Pcx()
{

}

Pcx::~Pcx()
{

}

// could stay in cpp files as it's private implementation
struct PCXheader
{
	unsigned char Manufacturer;
	unsigned char Version;
	unsigned char Encoding;
	unsigned char BitsPerPixel;
	short Xmin, Ymin, Xmax, Ymax;
	short HDpi, VDpi;
	unsigned char Colormap[48];
	unsigned char Reserved;
	unsigned char NPlanes;
	short BytesPerLine;
	short PaletteInfo;
	short HscreenSize;
	short VscreenSize;
	unsigned char Filler[54];
};

/**
 **  Convert 8 bit pcx file to raw image
 */
void Pcx::convertToRawImage(unsigned char *pcx, unsigned char **raw,
		unsigned char **pal, int *w, int *h)
{
	struct PCXheader pcxh;
	int y;
	int i;
	int count;
	unsigned char *src;
	unsigned char *dest;
	unsigned char ch;

	ch = 0;
	memcpy(&pcxh, pcx, sizeof(struct PCXheader));
	pcxh.Xmin = ConvertLE16(pcxh.Xmin);
	pcxh.Ymin = ConvertLE16(pcxh.Ymin);
	pcxh.Xmax = ConvertLE16(pcxh.Xmax);
	pcxh.Ymax = ConvertLE16(pcxh.Ymax);
	pcxh.BytesPerLine = ConvertLE16(pcxh.BytesPerLine);

	*w = pcxh.Xmax - pcxh.Xmin + 1;
	*h = pcxh.Ymax - pcxh.Ymin + 1;

	*raw = (unsigned char*) malloc(*w * *h);
	src = pcx + sizeof(struct PCXheader);

	for (y = 0; y < *h; ++y)
	{
		count = 0;
		dest = *raw + y * *w;
		for (i = 0; i < *w; ++i)
		{
			if (!count)
			{
				ch = *src++;
				if ((ch & 0xc0) == 0xc0)
				{
					count = ch & 0x3f;
					ch = *src++;
				}
				else
				{
					count = 1;
				}
			}
			dest[i] = ch;
			--count;
		}
	}

	*pal = (unsigned char*) malloc(256 * 3);
	dest = *pal;
	do
	{
		ch = *src++;
	} while (ch != 12);

	for (i = 0; i < 256 * 3; ++i)
	{
		*dest++ = *src++;
	}
}



/**
**  Convert a pcx graphic to PNG format
**
**  @param arcfile File identifier in the MPQ file
**  @param file Place to save the file on the drive (relative)
*/
bool Pcx::convert(const char *mpqfile, const char *arcfile, const char *file)
{
	unsigned char *palp;
	unsigned char *pcxp;
	unsigned char *image;
	char buf[1024];
	int w;
	int h;
	bool result = true;

	Storm mpq(mpqfile);
	result = mpq.extractMemory(arcfile, &pcxp, NULL);
	if (result)
	{
		convertToRawImage(pcxp, &image, &palp, &w, &h);
		free(pcxp);
		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), GRAPHICS_PATH, file);
		Png::save(buf, image, w, h, palp, 0);

		free(image);
		free(palp);
	}

	return result;
}
