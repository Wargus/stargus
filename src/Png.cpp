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

int Png::save(const std::string &name, PaletteImage &palImage, unsigned char *pal, int transparent)
{
  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned char **lines;
  int i;

  unsigned char *image = palImage.getRawData();

  CheckPath(name);

  if (!(fp = fopen(name.c_str(), "wb")))
  {
    printf("%s:", name.c_str());
    perror("Can't open file");
    fflush(stdout);
    fflush(stderr);
    return 1;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
  {
    fclose(fp);
    return 1;
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    return 1;
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    // FIXME: must free buffers!!
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return 1;
  }
  png_init_io(png_ptr, fp);

  // zlib parameters
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

  // prepare the file information
  png_set_IHDR(png_ptr, info_ptr, palImage.getWidth(), palImage.getHeight(), 8, PNG_COLOR_TYPE_PALETTE, 0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  png_set_invalid(png_ptr, info_ptr, PNG_INFO_PLTE);
  png_set_PLTE(png_ptr, info_ptr, (png_colorp) pal, 256);

  if (transparent != -1)
  {
    png_byte trans[256];

    memset(trans, 0xFF, sizeof(trans));
    trans[transparent] = 0x0;
    png_set_tRNS(png_ptr, info_ptr, trans, 256, 0);
  }

  // write the file header information
  png_write_info(png_ptr, info_ptr);

  // set transformation

  // prepare image
  lines = (unsigned char **) malloc(palImage.getHeight() * sizeof(*lines));
  if (!lines)
  {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return 1;
  }

  for (i = 0; i < palImage.getHeight(); ++i)
  {
    lines[i] = image + i * palImage.getWidth();
  }

  png_write_image(png_ptr, lines);
  png_write_end(png_ptr, info_ptr);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);

  free(lines);

  return 0;
}


int Png::saveRGBA(const std::string &name, PaletteImage &palImage, unsigned char *pal, int transparent)
{
  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  png_bytep *row_pointers = NULL;
  const int RGBA_BYTE_SIZE = 4;
  const int RGB_BYTE_SIZE = 3;

  unsigned char *image = palImage.getRawData();

  CheckPath(name);

  if (!(fp = fopen(name.c_str(), "wb")))
  {
    printf("%s:", name.c_str());
    perror("Can't open file");
    fflush(stdout);
    fflush(stderr);
    return 1;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
  {
    fclose(fp);
    return 1;
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    return 1;
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    // FIXME: must free buffers!!
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return 1;
  }
  png_init_io(png_ptr, fp);

  // zlib parameters
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

  // prepare the file information
  png_set_IHDR(png_ptr, info_ptr, palImage.getWidth(), palImage.getHeight(), 8, PNG_COLOR_TYPE_RGBA, 0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  // write the file header information
  png_write_info(png_ptr, info_ptr);

  row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * palImage.getHeight());


  for (int h_pos = 0; h_pos < palImage.getHeight(); ++h_pos)
  {
    row_pointers[h_pos] = (unsigned char *) malloc(palImage.getWidth() * RGBA_BYTE_SIZE);

    unsigned char *img_line_pal = image + h_pos * palImage.getWidth();

    for (int w_pos = 0; w_pos < palImage.getWidth(); w_pos++)
    {
      unsigned char pal_pos = img_line_pal[w_pos];
      //printf("pal_pos (w:%d/h:%d) pal:%d\n", w_pos, h_pos,(int) pal_pos);

      unsigned char color_r = 0;
      unsigned char color_g = 0;
      unsigned char color_b = 0;
      unsigned char color_a = 0;

      if (pal_pos != 255)
      {
        color_r = pal[pal_pos * RGB_BYTE_SIZE + 0];
        color_g = pal[pal_pos * RGB_BYTE_SIZE + 1];
        color_b = pal[pal_pos * RGB_BYTE_SIZE + 2];
        color_a = transparent;
      }

      row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 0] = color_r;
      row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 1] = color_g;
      row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 2] = color_b;
      row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 3] = color_a;
    }

  }

  png_set_rows(png_ptr, info_ptr, row_pointers);
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);

  if (NULL != row_pointers)
  {
    for (int h_pos = 0; h_pos < palImage.getHeight(); ++h_pos)
    {
      free(row_pointers[h_pos]);
    }

    free(row_pointers);
    row_pointers = NULL;
  }

  return 0;
}
