/*
 * Font.cpp
 *
 *  Created on: 02.11.2021
 *      Author: Andreas Volz
 */

#include "endian.h"

// C
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/**
**  Convert font into image.
*/
unsigned char* ConvertFnt(unsigned char* start, int *wp, int *hp)
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
		width = FetchByte(bp); //crash!!!
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


