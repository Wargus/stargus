/*
 * Grp.cpp
 *
 *      Author: Andreas Volz
 */

#include "Grp.h"
#include "endian.h"
#include "Png.h"
#include "FileUtil.h"
#include "Storm.h"
#include "Preferences.h"
#include "Palettes.h"

// C++
#include <cstring>
#include <cstdio>
#include <stdlib.h>



Grp::Grp()
{

}

Grp::~Grp()
{

}



/**
 * Convert a widget from data container as several PNG files
 */
bool ConvertWidgets(const char *mpqfile, const char* arcfile, const char* file, int pale)
{
	unsigned char* palp = NULL;
	unsigned char* gfup = NULL;
	unsigned char* gfup2 = NULL;
	unsigned char* image = NULL;
	int w;
	int h;
	char buf[1024];
	unsigned char* p;
	unsigned char* end;
	bool result = true;

	result = FileExists(mpqfile);

	if(result) {
		Storm mpq(mpqfile);
		result = mpq.extractMemory(arcfile, &gfup, NULL);
		if (result)
		{
			image = ConvertGraphic(0, gfup, &w, &h, gfup2, 0);

			// 0 and 255 are transparent
			p = image;
			end = image + w * h;
			while (p < end) {
				if (!*p) {
					*p = 0xFF;
				}
				++p;
			}

			palp = Palettes[pale];

			free(gfup);

			Preferences &preferences = Preferences::getInstance ();
			sprintf(buf, "%s/graphics/%s/", preferences.getDestDir().c_str(), file);

			sprintf(buf, "%s/graphics/%s/menu.png", preferences.getDestDir().c_str(), file);
			SaveImage(buf, image, palp, 1, 64, 20);

			sprintf(buf, "%s/graphics/%s/menu pressed.png", preferences.getDestDir().c_str(), file);
			SaveImage(buf, image, palp, 2, 64, 20);


			sprintf(buf, "%s/graphics/%s/minimap terrain disabled.png", preferences.getDestDir().c_str(), file);
			SaveImage(buf, image, palp, 3, 64, 20);

			sprintf(buf, "%s/graphics/%s/minimap terrain.png", preferences.getDestDir().c_str(), file);
			SaveImage(buf, image, palp, 4, 64, 20);

			sprintf(buf, "%s/graphics/%s/minimap terrain pressed.png", preferences.getDestDir().c_str(), file);
			SaveImage(buf, image, palp, 5, 64, 20);


			sprintf(buf, "%s/graphics/%s/diplomacy disabled.png", preferences.getDestDir().c_str(), file);
			SaveImage(buf, image, palp, 83, 64, 20);

			sprintf(buf, "%s/graphics/%s/diplomacy.png", preferences.getDestDir().c_str(), file);
			SaveImage(buf, image, palp, 84, 64, 20);

			sprintf(buf, "%s/graphics/%s/diplomacy pressed.png", preferences.getDestDir().c_str(), file);
			SaveImage(buf, image, palp, 85, 64, 20);


			sprintf(buf, "%s/graphics/%s/button left disabled 224x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 224, 104);

			sprintf(buf, "%s/graphics/%s/button left 224x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 224, 107);

			sprintf(buf, "%s/graphics/%s/button left pressed 224x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 224, 110);


			sprintf(buf, "%s/graphics/%s/button left disabled 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 104);

			sprintf(buf, "%s/graphics/%s/button left 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 107);

			sprintf(buf, "%s/graphics/%s/button left pressed 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 110);


			sprintf(buf, "%s/graphics/%s/button disabled 224x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 224, 113);

			sprintf(buf, "%s/graphics/%s/button 224x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 224, 116);

			sprintf(buf, "%s/graphics/%s/button pressed 224x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 224, 119);


			sprintf(buf, "%s/graphics/%s/button disabled 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 113);

			sprintf(buf, "%s/graphics/%s/button 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 116);

			sprintf(buf, "%s/graphics/%s/button pressed 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 119);


			sprintf(buf, "%s/graphics/%s/button right disabled 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 122);

			sprintf(buf, "%s/graphics/%s/button right 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 125);

			sprintf(buf, "%s/graphics/%s/button right pressed 104x28.png", preferences.getDestDir().c_str(), file);
			SaveButton(buf, image, palp, 104, 128);
		}
		else
		{
			result = false;
		}
	}

	free(image);

	return result;
}



void ConvertPal3(unsigned char* image, int w, int h)
{
	int i;

	// FIXME: this isn't correct, there should be partial transparency
	for (i = 0; i < w * h; ++i) {
		if (image[i] < 16 || image[i] > 62) {
			image[i] = 255;
		}
	}
}




/**
**  Convert a graphic to my format.
*/
bool ConvertGfx(const char *mpqfile, const char* arcfile, const char* file, int pale)
{
	unsigned char* palp = NULL;
	unsigned char* gfxp = NULL;
	unsigned char* gfxp2 = NULL;
	unsigned char* image = NULL;
	int w;
	int h;
	char buf[1024];
	bool result = true;

	Storm mpq(mpqfile);
	result = mpq.extractMemory(arcfile, &gfxp, NULL);
	if (result)
	{

		image = ConvertGraphic(1, gfxp, &w, &h, gfxp2, 0);

		palp = Palettes[pale];

		free(gfxp);

		if (pale == 3) {
			ConvertPal3(image, w, h);
		}
		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), GRAPHICS_PATH, file);
		Png::save(buf, image, w, h, palp, 255);

		free(image);
	}
	else
	{
		result = false;
	}

	return result;
}

/**
**  Convert a uncompressed graphic to my format.
*/
bool ConvertGfu(const char *mpqfile, const char* arcfile, const char* file, int pale)
{
	unsigned char* palp = NULL;
	unsigned char* gfup = NULL;
	unsigned char* gfup2 = NULL;
	unsigned char* image = NULL;
	int w;
	int h;
	char buf[8192] = {'\0'};
	unsigned char* p;
	unsigned char* end;
	bool result = true;

	Storm mpq(mpqfile);
	result = mpq.extractMemory(arcfile, &gfup, NULL);
	if (result)
	{
		image = ConvertGraphic(0, gfup, &w, &h, gfup2, 0);

		// 0 and 255 are transparent
		p = image;
		end = image + w * h;
		while (p < end) {
			if (!*p) {
				*p = 0xFF;
			}
			++p;
		}

		palp = Palettes[pale];


		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), GRAPHICS_PATH, file);

		Png::save(buf, image, w, h, palp, 255);

		free(image);
	}
	else
	{
		result = false;
	}
	free(gfup);

	return result;
}

/**
 * Save Image part of a Widget as PNG file
 */
void SaveImage(char *name, unsigned char *image, unsigned char *palp, int id, int w, int h)
{
	unsigned char *buf = (unsigned char *)malloc(w * h);
	int i;

	for (i = 0; i < h; ++i) {
		memcpy(buf + w*i, image + id*28*64 + 64*i, w);
	}

	Png::save(name, buf, w, h, palp, 255);

	free(buf);
}

/**
 * Save Button part of a Widget as PNG
 */
void SaveButton(char *name, unsigned char *image, unsigned char *palp, int size, int id)
{
	unsigned char *button;
	int i, j;

	button = (unsigned char *)malloc(size * 28);

#define copyimage(dst, src) \
	for (j = 0; j < 28; ++j) { \
		memcpy((dst + size*j), (src + 64*j), 8); \
	}

	copyimage(button + 0, image + (id - 1) * 28 * 64);
	for (i = 8; i < size - 8; i += 8) {
		copyimage(button + i, image + id * 28 * 64);
	}
	copyimage(button + size - 8, image + (id + 1) * 28 * 64);

	for (i = 0; i < size * 28; ++i) {
		if (button[i] == 41) {
			button[i] = 255;
		}
	}

	Png::save(name, button, size, 28, palp, 255);

	free(button);
}


/**
**  Decode a entry(frame) into image.
*/
void DecodeGfxEntry(int index, unsigned char* start,
	unsigned char* image, int ix, int iy, int iadd)
{
	unsigned char* bp;
	unsigned char* sp;
	unsigned char* dp;
	int xoff;
	int yoff;
	int width;
	int height;
	int offset;
	unsigned char* rows;
	int h;
	int w;
	int ctrl;

	bp = start + index * 8;
	xoff = FetchByte(bp);
	yoff = FetchByte(bp);
	width = FetchByte(bp);
	height = FetchByte(bp);
	offset = FetchLE32(bp);

//	printf("%2d: +x %2d +y %2d width %2d height %2d offset %d\n",
//		index, xoff, yoff, width, height, offset);

	rows = start + offset - 6;
	dp = image + xoff - ix + (yoff - iy) * iadd;

	for (h = 0; h < height; ++h) {
//		printf("%2d: row-offset %2d\t", index, AccessLE16(rows + h * 2));
		sp = rows + AccessLE16(rows + h * 2);
		for (w = 0; w < width; ) {
			ctrl = *sp++;
//			printf("%02X", ctrl);
			if (ctrl & 0x80) {  // transparent
				ctrl &= 0x7F;
//				printf("-%d,", ctrl);
				memset(dp+h*iadd+w,255,ctrl);
				w+=ctrl;
			} else if (ctrl & 0x40) {  // repeat
				ctrl &= 0x3F;
//				printf("*%d,", ctrl);
				memset(dp + h * iadd + w, *sp++, ctrl);
				w += ctrl;
			} else {						// set pixels
				ctrl &= 0x3F;
//				printf("=%d,", ctrl);
				memcpy(dp + h * iadd + w, sp, ctrl);
				sp += ctrl;
				w += ctrl;
			}
		}
		//dp[h * iadd + width - 1] = 0;
//		printf("\n");
	}
}

/**
**  Decode a entry(frame) into image.
*/
void DecodeGfuEntry(int index, unsigned char* start,
	unsigned char* image, int ix, int iy, int iadd)
{
	unsigned char* bp;
	unsigned char* sp;
	unsigned char* dp;
	int i;
	int xoff;
	int yoff;
	int width;
	int height;
	int offset;

	bp = start + index * 8;
	xoff = FetchByte(bp);
	yoff = FetchByte(bp);
	width = FetchByte(bp);
	height = FetchByte(bp);
	offset = FetchLE32(bp);
	// High bit of width
	if (offset < 0) {
		offset &= 0x7FFFFFFF;
		width += 256;
	}

//	printf("%2d: +x %2d +y %2d width %2d height %2d offset %d\n",
//		index, xoff, yoff, width, height, offset);

	sp = start + offset - 6;
	dp = image + xoff - ix + (yoff - iy) * iadd;
	for (i = 0; i < height; ++i) {
		memcpy(dp, sp, width);
		dp += iadd;
		sp += width;
	}
}

/**
**  Convert graphics into image.
*/
unsigned char* ConvertGraphic(int gfx, unsigned char* bp, int *wp, int *hp,
	unsigned char* bp2, int start2)
{
	int i;
	int count;
	int length;
	int max_width;
	int max_height;
	int minx;
	int miny;
	int best_width;
	int best_height;
	unsigned char* image;
	int IPR;

	int endereco;

	// Init pointer to 2nd animation
	if (bp2) {
		count = FetchLE16(bp2);
		max_width = FetchLE16(bp2);
		max_height = FetchLE16(bp2);
	}
	count = FetchLE16(bp);
	max_width = FetchLE16(bp);
	max_height = FetchLE16(bp);


//	printf("Entries %2d Max width %3d height %3d, ", count,
//		max_width, max_height);

	// Find best image size
	minx = 999;
	miny = 999;
	best_width = 0;
	best_height = 0;
	for (i = 0; i < count; ++i) {
		unsigned char* p;
		int xoff;
		int yoff;
		int width;
		int height;

		p = bp + i * 8;
		xoff = FetchByte(p);
		yoff = FetchByte(p);
		width = FetchByte(p);
		height = FetchByte(p);
		endereco = FetchLE32(p);
		if( endereco&0x80000000 ) {		// high bit of width
			width += 256;
		}
		if( xoff<minx ) minx=xoff;
		if( yoff<miny ) miny=yoff;
		if( xoff+width>best_width ) best_width=xoff+width;
		if( yoff+height>best_height ) best_height=yoff+height;
	}
	// FIXME: the image isn't centered!!

#if 0
	// Taken out, must be rewritten.
	if (max_width - best_width < minx) {
		minx = max_width - best_width;
		best_width -= minx;
	} else {
		best_width = max_width - minx;
	}
	if (max_height - best_height < miny) {
		miny = max_height - best_height;
		best_height -= miny;
	} else {
		best_height = max_width - miny;
	}

	//best_width -= minx;
	//best_height -= miny;
#endif

//	printf("Best image size %3d, %3d\n", best_width, best_height);

	minx = 0;
	miny = 0;

	if (gfx) {
		best_width = max_width;
		best_height = max_height;
		IPR = 17;  // st*rcr*ft 17!
		if (count < IPR) {  // images per row !!
			IPR = 1;
			length = count;
		} else {
			length = ((count + IPR - 1) / IPR) * IPR;
		}
	} else {
		max_width = best_width;
		max_height = best_height;
		IPR = 1;
		length = count;
	}

	image = (unsigned char *)malloc(best_width * best_height * length);

	//  Image: 0, 1, 2, 3, 4,
	//         5, 6, 7, 8, 9, ...
	if (!image) {
		printf("Can't allocate image\n");
		// TODO: more flexible error handling than calling GUI dialog from conversation routine needed
		//error("Memory error", "Could not allocate enough memory to read archive.");
	}
	// Set all to transparent.
	memset(image, 255, best_width * best_height * length);

	if (gfx) {
		for (i = 0; i < count; ++i) {
			// Hardcoded support for worker with resource repairing
			if (i >= start2 && bp2) {
				DecodeGfxEntry(i, bp2,
					image + best_width * (i % IPR) + best_height * best_width * IPR * (i / IPR),
					minx, miny, best_width * IPR);
			} else {
				DecodeGfxEntry(i, bp,
					image + best_width * (i % IPR) + best_height * best_width * IPR * (i / IPR),
					minx, miny, best_width * IPR);
			}
		}
	} else {
		for (i = 0; i < count; ++i) {
			DecodeGfuEntry(i, bp,
				image + best_width * (i % IPR) + best_height * best_width * IPR * (i / IPR),
				minx, miny, best_width * IPR);
		}
	}

	*wp = best_width * IPR;
	*hp = best_height * (length / IPR);

	return image;
}
