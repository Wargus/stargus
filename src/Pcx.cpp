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
#include "Hurricane.h"

// System
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

Pcx::Pcx(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane), mLogger("startool.Pcx"), rawImage(0), mImageParserPos(nullptr), mWidth(0), mHeight(0)
{
}

Pcx::Pcx(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
  Converter(hurricane), mLogger("startool.Pcx"), rawImage(0), mImageParserPos(nullptr), mWidth(0), mHeight(0)
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
    extractPalette();
  }
  else
  {
    result = false;
  }

  return result;
}

bool Pcx::savePNG(const std::string &filename)
{
  bool result = true;
  char buf[8192] =
  { '\0' };

  if (mRawData)
  {
    Preferences &preferences = Preferences::getInstance();
    sprintf(buf, "%s/%s/%s", preferences.getDestDir().c_str(), GRAPHICS_PATH, filename.c_str());
    Png::save(buf, rawImage, mWidth, mHeight, mPalette->getDataChunk()->getDataPointer(), 0);
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
  int max_index = ((mWidth * mHeight) / length) - 1;
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

    //printf("w: %d / h:%d\n", mWidth, mHeight);

    for (int i = 0; i < length; i++)
    {
      if (dynamic_index)
      {
        index++;
      }

      int rel_index = i + (index * length);

      //printf("pal_pos: %d\n", rawImage[rel_index]);
      //printf("-> r:%x / g:%x / b:%x\n", pal[rawImage[rel_index]*3], pal[rawImage[rel_index]*3+1], pal[rawImage[rel_index]*3+2]);

      int start_pal_dest = start * RGB_BYTE_SIZE + i * RGB_BYTE_SIZE;

      pal[start_pal_dest + pos_r] = pal[rawImage[rel_index] * RGB_BYTE_SIZE + pos_r];
      pal[start_pal_dest + pos_g] = pal[rawImage[rel_index] * RGB_BYTE_SIZE + pos_g];
      pal[start_pal_dest + pos_b] = pal[rawImage[rel_index] * RGB_BYTE_SIZE + pos_b];
    }
  }
}

void Pcx::extractHeader()
{
  if (mRawData)
  {
    memcpy(&pcxh, mRawData->getDataPointer(), sizeof(struct PCXheader));
    pcxh.Xmin = ConvertLE16(pcxh.Xmin);
    pcxh.Ymin = ConvertLE16(pcxh.Ymin);
    pcxh.Xmax = ConvertLE16(pcxh.Xmax);
    pcxh.Ymax = ConvertLE16(pcxh.Ymax);
    pcxh.BytesPerLine = ConvertLE16(pcxh.BytesPerLine);

    mWidth = pcxh.Xmax - pcxh.Xmin + 1;
    mHeight = pcxh.Ymax - pcxh.Ymin + 1;
  }
}

void Pcx::extractImage()
{
  int y;
  int count;
  unsigned char *dest = NULL;
  unsigned char ch = 0;

  rawImage = (unsigned char *) malloc(mWidth * mHeight);
  mImageParserPos = mRawData->getDataPointer() + sizeof(struct PCXheader);

  for (y = 0; y < mHeight; ++y)
  {
    count = 0;
    dest = rawImage + y * mWidth;
    for (int i = 0; i < mWidth; ++i)
    {
      if (!count)
      {
        ch = *mImageParserPos++;
        if ((ch & 0xc0) == 0xc0)
        {
          count = ch & 0x3f;
          ch = *mImageParserPos++;
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
}

void Pcx::extractPalette()
{
  unsigned char *dest = NULL;
  unsigned char ch = 0;

  unsigned char *pal = NULL;

  if (mRawData)
  {
    // allocate enough space for RGB information
    pal = (unsigned char *) malloc(RGB_SIZE); // memory management later given to DataChunk...
    dest = pal;
    do
    {
      ch = *mImageParserPos++;
    }
    while (ch != 0x0c);   // search the 'magic ID' that shows the start of RGB information next

    // copy RGB information to destination
    for (int i = 0; i < RGB_SIZE; ++i)
    {
      *dest++ = *mImageParserPos++;
    }

    std::shared_ptr<DataChunk> data = make_shared<DataChunk>(&pal, RGB_SIZE);
    mPalette = make_shared<Palette>(data);
  }
}

