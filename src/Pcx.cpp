/*
 * Pcx.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "endian.h"
#include "Pcx.h"
#include "Storm.h"
#include "Png.h"
#include "Hurricane.h"

// System
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

Pcx::Pcx(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane), mLogger("startool.Pcx"), rawImage(0)
{
}

Pcx::Pcx(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
  Converter(hurricane), mLogger("startool.Pcx"), rawImage(0)
{
  load(arcfile);
}

Pcx::~Pcx()
{
  free(rawImage);
}

bool Pcx::load(const std::string &arcfile)
{
  bool result = true;

  mRawData = mHurricane->extractDataChunk(arcfile);
  if (mRawData)
  {
    free(rawImage);
    extractHeader();
    extractImage();
    //extractPalette();
  }
  else
  {
    result = false;
  }

  return result;
}

bool Pcx::savePNG(Storage storage)
{
  bool result = true;

  if (mRawData)
  {
    Png::save(storage.getFullPath().c_str(), mPaletteImage->getPixelData(), mPaletteImage->getWidth(), mPaletteImage->getHeight(), mPalette->getDataChunk()->getDataPointer(), 0);
  }
  else
  {
    result = false;
  }

  return result;
}

std::shared_ptr<Palette> Pcx::getPalette()
{
  return mPalette;
}

void Pcx::copyIndexPalette(int start, int length, int index)
{
  if(mPaletteImage)
  {
    int max_index = ((mPaletteImage->getWidth() * mPaletteImage->getHeight()) / length) - 1;
    //int remain_pixel = (mWidth * mHeight) % length;
    bool dynamic_index = false;

    //printf("max index: %d\n", max_index);
    //printf("remain_pixel: %d\n", remain_pixel);

    if (index > max_index)
    {
      //printf("max index reached!\n");
    }

    if (index == -1)
    {
      dynamic_index = true;
    }

    if (mPalette)
    {
      unsigned char *pal = mPalette->getDataChunk()->getDataPointer();
      int pos_r = 0;
      int pos_g = 1;
      int pos_b = 2;

      //printf("w: %d / h:%d\n", mPaletteImage->getWidth(), mPaletteImage->getHeight());

      for (int i = 0; i < length; i++)
      {
        if (dynamic_index)
        {
          index++;
        }

        int rel_index = i + (index * length);
        //printf("rel_index:%d, i:%d, index:%d, length:%d\n", rel_index, i, index, length);

        //printf("pal_pos: %d\n", rawImage[rel_index]);
        //printf("-> r:%x / g:%x / b:%x\n", pal[rawImage[rel_index]*3], pal[rawImage[rel_index]*3+1], pal[rawImage[rel_index]*3+2]);

        int start_pal_dest = start * RGB_BYTE_SIZE + i * RGB_BYTE_SIZE;

        // TODO: here is a index over bounds bug that I need to find
        pal[start_pal_dest + pos_r] = pal[rawImage[rel_index] * RGB_BYTE_SIZE + pos_r];
        pal[start_pal_dest + pos_g] = pal[rawImage[rel_index] * RGB_BYTE_SIZE + pos_g];
        pal[start_pal_dest + pos_b] = pal[rawImage[rel_index] * RGB_BYTE_SIZE + pos_b];
      }
    }
  }
}

std::shared_ptr<Palette> Pcx::createIndexPalette(int start, int length, int index)
{
  std::shared_ptr<Palette> new_palette = make_shared<Palette>();

  /*if(mPaletteImage && mPalette)
  {
    for (int i = 0; i < length; i++)
    {
      int rel_index = i + (index * length);

      int start_pal_dest = start + i;
    }
  }*/

  return new_palette;
}

void Pcx::copyIndexPaletteIconColor()
{
  copyIndexPalette(0, 16, 0);
}

void Pcx::extractHeader()
{
  if (mRawData)
  {
    struct PCXheader pcxh;

    memcpy(&pcxh, mRawData->getDataPointer(), sizeof(struct PCXheader));
    pcxh.Xmin = ConvertLE16(pcxh.Xmin);
    pcxh.Ymin = ConvertLE16(pcxh.Ymin);
    pcxh.Xmax = ConvertLE16(pcxh.Xmax);
    pcxh.Ymax = ConvertLE16(pcxh.Ymax);
    pcxh.BytesPerLine = ConvertLE16(pcxh.BytesPerLine);

    int width = pcxh.Xmax - pcxh.Xmin + 1;
    int height = pcxh.Ymax - pcxh.Ymin + 1;

    mPaletteImage = make_shared<PaletteImage>(width, height);
  }
}

void Pcx::extractImage()
{
  int y;
  int count;
  unsigned char *dest = NULL;
  unsigned char ch = 0;
  unsigned char *imageParserPos = nullptr;

  if (mRawData)
  {
    rawImage = (unsigned char *) malloc(mPaletteImage->getWidth() * mPaletteImage->getHeight());
    imageParserPos = mRawData->getDataPointer() + sizeof(struct PCXheader);

    for (y = 0; y < mPaletteImage->getHeight(); ++y)
    {
      count = 0;
      dest = rawImage + y * mPaletteImage->getWidth();
      for (int i = 0; i < mPaletteImage->getWidth(); ++i)
      {
        if (!count)
        {
          ch = *imageParserPos++;
          if ((ch & 0xc0) == 0xc0)
          {
            count = ch & 0x3f;
            ch = *imageParserPos++;
          }
          else
          {
            count = 1;
          }
        }
        dest[i] = ch;
        mPaletteImage->addPixel(ch);
        --count;
      }
    }

    // extract palette =>

    unsigned char *pal = NULL;
    mPalette = make_shared<Palette>();

    // allocate enough space for RGB information
    pal = (unsigned char *) malloc(RGB_SIZE); // memory management later given to DataChunk...
    dest = pal;
    do
    {
      ch = *imageParserPos++;
    }
    while (ch != 0x0c);   // search the 'magic ID' that shows the start of RGB information next

    // copy RGB information to destination
    for (int i = 0; i < RGB_SIZE; ++i)
    {
      mPalette->addColorComponent(*imageParserPos);
      *dest++ = *imageParserPos++;
    }

    //std::shared_ptr<DataChunk> data = make_shared<DataChunk>(&pal, RGB_SIZE);
    //mPalette = make_shared<Palette>(data);
  }
}

