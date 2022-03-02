/*
 * Grp.cpp
 *
 *      Author: Andreas Volz
 */

#include <Palette.h>
#include "Grp.h"
#include "endian.h"
#include "Png.h"
#include "FileUtil.h"
#include "Storm.h"
#include "Preferences.h"
#include <cstring>
#include <cstdio>
#include <stdlib.h>



Grp::Grp()
{

}

Grp::~Grp()
{

}


void Grp::DecodeGfuEntry(int index, unsigned char* start,
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


void Grp::DecodeGfxEntry(int index, unsigned char* start,
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



void Grp::ConvertPal3(unsigned char* image, int w, int h)
{
	int i;

	// FIXME: this isn't correct, there should be partial transparency
	for (i = 0; i < w * h; ++i) {
		if (image[i] < 16 || image[i] > 62) {
			image[i] = 255;
		}
	}
}

unsigned char* Grp::ConvertGraphic(int gfx, unsigned char* bp, int *wp, int *hp,
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
