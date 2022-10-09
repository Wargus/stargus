/*
 * Png.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "FileUtil.h"
#include "PngExporter.h"
#include "Logger.h"

// System
#include <cstring>
#include <stdlib.h>
#include <zlib.h>
#include <iostream>

using namespace std;

static Logger logger = Logger("startool.PngExporter");

PngExporter::PngExporter()
{
}

PngExporter::~PngExporter()
{

}

bool PngExporter::save(const std::string &name, PaletteImage &palImage,
        std::shared_ptr<AbstractPalette> abs_palette, int transparent, bool rgba)
{
  bool result = false;


  std::shared_ptr<Palette> palette = dynamic_pointer_cast<Palette>(abs_palette);
  if(palette)
  {
    if(rgba)
    {
      result = PngExporter::saveRGBA(name, palImage, *palette, transparent);
    }
    else
    {
      result = PngExporter::saveRGB(name, palImage, *palette, transparent);
    }
  }
  else
  {
    std::shared_ptr<Palette2D> palette2D = dynamic_pointer_cast<Palette2D>(abs_palette);
    if(palette2D)
    {
      result = PngExporter::saveRGBA(name, palImage, *palette2D, transparent);
    }
  }

  return result;
}

bool PngExporter::saveRGB(const std::string &name, PaletteImage &palImage, Palette &palette, int transparent)
{
  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  unsigned char **lines;
  int i;

  std::shared_ptr<DataChunk> palData = palette.createDataChunk();
  unsigned char *pal = palData->getDataPointer();

  const unsigned char *image = palImage.getRawDataPointer();

  CheckPath(name);

  if (!(fp = fopen(name.c_str(), "wb")))
  {
    printf("%s:", name.c_str());
    perror("Can't open file");
    fflush(stdout);
    fflush(stderr);
    return false;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
  {
    fclose(fp);
    return false;
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    return false;
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    free(lines);

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }
  png_init_io(png_ptr, fp);

  // zlib parameters
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

  // prepare the file information
  png_set_IHDR(png_ptr, info_ptr, palImage.getSize().getWidth(), palImage.getSize().getHeight(), 8, PNG_COLOR_TYPE_PALETTE,
               0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
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

  // prepare image
  lines = (unsigned char **) malloc(palImage.getSize().getHeight() * sizeof(*lines));
  if (!lines)
  {
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }

  for (i = 0; i < palImage.getSize().getHeight(); ++i)
  {
    const unsigned char *line = image + i * palImage.getSize().getWidth();
    lines[i] = (unsigned char*) line;
  }

  png_write_image(png_ptr, lines);
  png_write_end(png_ptr, info_ptr);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);

  free(lines);

  return true;
}


bool PngExporter::saveRGBA(const std::string &name, PaletteImage &palImage, Palette &palette, int transparent)
{
  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  png_bytep *row_pointers = NULL;
  const int RGBA_BYTE_SIZE = 4;

  CheckPath(name);

  if (!(fp = fopen(name.c_str(), "wb")))
  {
    printf("%s:", name.c_str());
    perror("Can't open file");
    fflush(stdout);
    fflush(stderr);
    return false;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
  {
    fclose(fp);
    return false;
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    return false;
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    free(row_pointers);
    row_pointers = NULL;

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return false;
  }
  png_init_io(png_ptr, fp);

  // zlib parameters
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

  // prepare the file information
  png_set_IHDR(png_ptr, info_ptr, palImage.getSize().getWidth(), palImage.getSize().getHeight(), 8, PNG_COLOR_TYPE_RGBA, 0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  // write the file header information
  png_write_info(png_ptr, info_ptr);

  row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * palImage.getSize().getHeight());

  for (int h_pos = 0; h_pos < palImage.getSize().getHeight(); ++h_pos)
  {
    row_pointers[h_pos] = (unsigned char *) malloc(palImage.getSize().getWidth() * RGBA_BYTE_SIZE);

    for (int w_pos = 0; w_pos < palImage.getSize().getWidth(); w_pos++)
    {
      unsigned char pal_pos = palImage.at(Pos(w_pos, h_pos));

      Color color;

      if (pal_pos != transparent)
      {
        color = palette.at(pal_pos);
        color.setAlpha(255);
      }

      row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 0] = color.getRed();
      row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 1] = color.getGreen();
      row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 2] = color.getBlue();
      row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 3] = color.getAlpha();
    }

  }

  png_set_rows(png_ptr, info_ptr, row_pointers);
  png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);

  if (NULL != row_pointers)
  {
    for (int h_pos = 0; h_pos < palImage.getSize().getHeight(); ++h_pos)
    {
      free(row_pointers[h_pos]);
    }

    free(row_pointers);
    row_pointers = NULL;
  }

  return true;
}

bool PngExporter::saveRGBA(const std::string &name, PaletteImage &palImage, Palette2D &palette2d, int transparent)
{
  FILE *fp;
  png_structp png_ptr;
  png_infop info_ptr;
  png_bytep *row_pointers = NULL;
  const int RGBA_BYTE_SIZE = 4;
  bool result = true;

  CheckPath(name);

  if (!(fp = fopen(name.c_str(), "wb")))
  {
    printf("%s:", name.c_str());
    perror("Can't open file");
    fflush(stdout);
    fflush(stderr);
    return false;
  }

  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr)
  {
    fclose(fp);
    return false;
  }
  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
  {
    png_destroy_write_struct(&png_ptr, NULL);
    fclose(fp);
    return false;
  }

  if (setjmp(png_jmpbuf(png_ptr)))
  {
    free(row_pointers);
    row_pointers = NULL;

    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);
    return 1;
  }
  png_init_io(png_ptr, fp);

  // zlib parameters
  png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

  // prepare the file information
  png_set_IHDR(png_ptr, info_ptr, palImage.getSize().getWidth(), palImage.getSize().getHeight(), 8, PNG_COLOR_TYPE_RGBA, 0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

  // write the file header information
  png_write_info(png_ptr, info_ptr);

  row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * palImage.getSize().getHeight());

  /*
   * Count how many lines are allocated in case of Exception cleanup later!
   * This is only needed for Palette2D case as this one has dynamic size.
   * If you export an GRP with the wrong Palette2D - Bang!
   */
  int h_pos_allocated = 0;

  try
  {
    for (int h_pos = 0; h_pos < palImage.getSize().getHeight(); ++h_pos)
    {
      row_pointers[h_pos] = (unsigned char *) malloc(palImage.getSize().getWidth() * RGBA_BYTE_SIZE);
      h_pos_allocated = h_pos;

      for (int w_pos = 0; w_pos < palImage.getSize().getWidth(); w_pos++)
      {
        unsigned char pal_pos = palImage.at(Pos(w_pos, h_pos));

        unsigned char pal_beneath = 0;// back palette id #0 (known in the palette format)
        Color reference_beneath_color (0, 0, 0); // back palette id #0 (known in the palette format)

        Color color_result;

        if (pal_pos != transparent)
        {
          const Color &color_orig = palette2d.at(pal_beneath, pal_pos-1);

          color_result = color_orig.blendAgainstReference(reference_beneath_color);
        }

        row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 0] = color_result.getRed();
        row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 1] = color_result.getGreen();
        row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 2] = color_result.getBlue();
        row_pointers[h_pos][w_pos * RGBA_BYTE_SIZE + 3] = color_result.getAlpha();
      }

    }

    png_set_rows(png_ptr, info_ptr, row_pointers);
    png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);
  }
  catch(std::out_of_range &ex)
  {
    LOG4CXX_ERROR(logger, ex.what());
    LOG4CXX_ERROR(logger, "This image couldn't be saved because index out of range error. Very often this happens because wrong palette is used for: " + name);
    result = false;
  }

  png_destroy_write_struct(&png_ptr, &info_ptr);
  fclose(fp);

  if (NULL != row_pointers)
  {
    for (int h_pos = 0; h_pos < h_pos_allocated; ++h_pos)
    {
      free(row_pointers[h_pos]);
    }

    free(row_pointers);
    row_pointers = NULL;
  }

  return result;
}
