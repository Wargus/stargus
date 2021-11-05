/*
 * Png.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Png.h"
#include "FileUtil.h"

// System
#include <cstring>
#include <stdlib.h>
#include <zlib.h>

Png::Png()
{
}

Png::~Png()
{

}

//----------------------------------------------------------------------------
//  PNG
//----------------------------------------------------------------------------

/**
**  Save a png file.
**
**  @param name         File name
**  @param image        Graphic data
**  @param w            Graphic width
**  @param h            Graphic height
**  @param pal          Palette
**  @param transparent  Image uses transparency
*/
int Png::save(const char* name, unsigned char* image, int w,
	int h, unsigned char* pal, int transparent)
{
	FILE* fp;
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned char** lines;
	int i;

	CheckPath(name);

	if (!(fp = fopen(name, "wb"))) {
		printf("%s:", name);
		perror("Can't open file");
		fflush(stdout); fflush(stderr);
		return 1;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fclose(fp);
		return 1;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(fp);
		return 1;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		// FIXME: must free buffers!!
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}
	png_init_io(png_ptr, fp);

	// zlib parameters
	png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

	// prepare the file information
	png_set_IHDR(png_ptr, info_ptr, w, h, 8, PNG_COLOR_TYPE_PALETTE, 0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_set_invalid(png_ptr, info_ptr, PNG_INFO_PLTE);
	png_set_PLTE(png_ptr, info_ptr, (png_colorp) pal, 256);

	if (transparent != -1) {
		png_byte trans[256];

		memset(trans, 0xFF, sizeof(trans));
		trans[transparent] = 0x0;
		png_set_tRNS(png_ptr, info_ptr, trans, 256, 0);
	}

	// write the file header information
	png_write_info(png_ptr, info_ptr);

	// set transformation

	// prepare image
	lines = (unsigned char **)malloc(h * sizeof(*lines));
	if (!lines) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}

	for (i = 0; i < h; ++i) {
		lines[i] = image + i * w;
	}

	png_write_image(png_ptr, lines);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	free(lines);

	return 0;
}
