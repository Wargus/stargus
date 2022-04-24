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

    LOG4CXX_TRACE(mLogger, "load(): " + arcfile);
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
    Png::save(storage.getFullPath(), *mPaletteImage, *mPalette, 0);
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

void Pcx::mapIndexPalette(int length, int index, int start)
{
  if (mPaletteImage && mPalette)
  {
    for (int i = 0; i < length; i++)
    {
      int rel_index = i + (index * length);
      int start_pal_dest = start + i;

      unsigned char color_index = mPaletteImage->at(rel_index);

      Color &image_color = mPalette->at(color_index);
      mPalette->at(start_pal_dest) = image_color;
    }
  }
}

void Pcx::mapIndexPaletteTypeIcon(int index)
{
  mapIndexPalette(16, index, 0);
}

void Pcx::mapIndexPaletteTypeSelect(int index)
{
  mapIndexPalette(8, index, 1);
}

void Pcx::map2DPalette()
{
  if (mPaletteImage && mPalette)
  {
    if ((mPaletteImage->getSize().getWidth() == 256) && (mPaletteImage->getSize().getHeight() == 63))
    {
      for (int i = 0; i < mPaletteImage->getSize().getWidth(); i++)
      {
        int num = (rand() % (55 -20  + 1)) + 20;

        unsigned char color_index = mPaletteImage->getPaletteIndex(i, num);

        if(color_index != 255)
        {
          Color image_color = mPalette->at(color_index);

          mPalette->at(i) = image_color;
        }
        else
        {
          Color trans_color(0, 0, 0);
          mPalette->at(i) = trans_color;
        }
      }
    }
  }
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

    mPaletteImage = make_shared<PaletteImage>(Size(width, height));
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
    rawImage = (unsigned char *) malloc(mPaletteImage->getSize().getWidth() * mPaletteImage->getSize().getHeight());
    imageParserPos = mRawData->getDataPointer() + sizeof(struct PCXheader);

    for (y = 0; y < mPaletteImage->getSize().getHeight(); ++y)
    {
      count = 0;
      dest = rawImage + y * mPaletteImage->getSize().getWidth();
      for (int i = 0; i < mPaletteImage->getSize().getWidth(); ++i)
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
        mPaletteImage->addPaletteIndex(ch);
        --count;
      }
    }

    // extract palette =>

    mPalette = make_shared<Palette>();

    do
    {
      ch = *imageParserPos++;
    }
    while (ch != 0x0c);   // search the 'magic ID' that shows the start of RGB information next

    // copy RGB information to destination
    for (int i = 0; i < RGB_SIZE; i += 3)
    {
      unsigned char red = *imageParserPos++;
      unsigned char green = *imageParserPos++;
      unsigned char blue = *imageParserPos++;

      Color rgb(red, green, blue);

      mPalette->addColor(rgb);
    }

  }
}

