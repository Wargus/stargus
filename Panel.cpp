/*
 * Panel.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Panel.h"
#include "FileUtil.h"
#include "Preferences.h"

// System
#include <png.h>
#include <zlib.h>

Panel::Panel()
{

}

Panel::~Panel()
{

}

//----------------------------------------------------------------------------
//		Panels
//----------------------------------------------------------------------------

unsigned char *CreatePanel(int width, int height)
{
	unsigned char *buf;
	int i, j;

	buf = (unsigned char *)malloc(width * height * 4);
	memset(buf, 0, width * height * 4);

#define pixel2(i, j, r, g, b, a) \
	buf[(j) * width * 4 + (i) * 4 + 0] = r; \
	buf[(j) * width * 4 + (i) * 4 + 1] = g; \
	buf[(j) * width * 4 + (i) * 4 + 2] = b; \
	buf[(j) * width * 4 + (i) * 4 + 3] = a;

#define pixel(i, j) \
	pixel2((i), (j), 0x0, 0x8, 0x40, 0xff)

	for (j = 1; j < height - 1; ++j) {
		for (i = 1; i < width - 1; ++i) {
			pixel2(i, j, 0x0, 0x8, 0x40, 0x80);
		}
	}
	for (i = 3; i < width - 3; ++i) {
		pixel(i, 0);
		pixel(i, height - 1);
	}
	for (i = 3; i < height - 3; ++i) {
		pixel(0, i);
		pixel(width - 1, i);
	}
	// top left
	pixel(1, 1);
	pixel(2, 1);
	pixel(1, 2);
	// top right
	pixel(width - 3, 1);
	pixel(width - 2, 1);
	pixel(width - 2, 2);
	// bottom left
	pixel(1, height - 3);
	pixel(1, height - 2);
	pixel(2, height - 2);
	// bottom right
	pixel(width - 3, height - 2);
	pixel(width - 2, height - 2);
	pixel(width - 2, height - 3);

#undef pixel
#undef pixel2

	return buf;
}

int SavePanel(int width, int height)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned char **lines;
	int i;
	char name[256];
	unsigned char *buf;

	Preferences &preferences = Preferences::getInstance ();
	sprintf(name, "%s/graphics/ui/panels/%dx%d.png", preferences.getDestDir().c_str(), width, height);
	CheckPath(name);

	if (!(fp = fopen(name, "wb"))) {
		fprintf(stderr,"%s:", name);
		perror("Can't open file");
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
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, 0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	buf = CreatePanel(width, height);

	// write the file header information
	png_write_info(png_ptr, info_ptr);  // write the file header information

	// set transformation

	// prepare image
	lines = (unsigned char **)malloc(height * sizeof(*lines));
	if (!lines) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		free(buf);
		return 1;
	}

	for (i = 0; i < height; ++i) {
		lines[i] = buf + i * width * 4;
	}

	png_write_image(png_ptr, lines);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	free(lines);
	free(buf);

	return 0;
}
