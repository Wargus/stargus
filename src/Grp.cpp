/*
 * Grp.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include <PngExporter.h>
#include "Grp.h"
#include "endian.h"
#include "FileUtil.h"
#include "Storm.h"
#include "Logger.h"

// System
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

static Logger logger = Logger("startool.Grp");

Grp::Grp(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane),
  mRGBA(false),
  mGFX(true),
  mTransparent(254)
{
}

Grp::Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
  Converter(hurricane),
  mRGBA(false),
  mGFX(true),
  mTransparent(254)
{
  load(arcfile);
}

Grp::Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile, std::shared_ptr<Palette> pal) :
  Converter(hurricane),
  mPal(pal),
  mRGBA(false),
  mGFX(true),
  mTransparent(254)
{
  load(arcfile);
}

Grp::~Grp()
{

}

void Grp::setGFX(bool gfx)
{
  mGFX = gfx;
}
bool Grp::getGFX()
{
  return mGFX;
}

void Grp::setPalette(std::shared_ptr<Palette> pal)
{
  mPal = pal;
}

void Grp::setPalette2D(std::shared_ptr<Palette2D> pal)
{
  mPal2D = pal;
}

void Grp::setRGBA(bool rgba)
{
  mRGBA = rgba;
}

bool Grp::getRGBA()
{
  return mRGBA;
}

bool Grp::load(const std::string &arcfile)
{
  mArcfile = arcfile;

  return true;
}

bool Grp::save(Storage filename)
{
  unsigned char *gfxp = NULL;
  unsigned char *gfxp2 = NULL;
  unsigned char *image = NULL;
  int w;
  int h;
  bool result = true;

  result = mHurricane->extractMemory(mArcfile, &gfxp, NULL);
  if (result)
  {

    image = ConvertGraphic(getGFX(), gfxp, &w, &h, gfxp2);

    if(!getGFX())
    {
      unsigned char *p;
      unsigned char *end;

      // 0 and 255 are transparent
      p = image;
      end = image + w * h;
      while (p < end)
      {
        if (!*p)
        {
          *p = mTransparent;
        }
        ++p;
      }
    }

    DataChunk dc_image(&image, w * h);
    PaletteImage palImage(dc_image, Size(w, h));

    if (!getRGBA())
    {
      PngExporter::save(filename.getFullPath(), palImage, *mPal, mTransparent);
    }
    else
    {
      if(mPal && !mPal2D)
      {
        PngExporter::saveRGBA(filename.getFullPath(), palImage, *mPal, mTransparent);
      }
      else if(mPal2D)
      {
        PngExporter::saveRGBA(filename.getFullPath(), palImage, *mPal2D, mTransparent);
      }
    }

    // TODO: wrap into DataChunk
    free(gfxp);
  }
  else
  {
    result = false;
  }



  return result;
}

Size Grp::getTileSize()
{
  return mTilesize;
}

void Grp::setTransparent(int transparent)
{
  mTransparent = transparent;
}

void Grp::DecodeGfuEntry(int index, unsigned char *start, unsigned char *image, int ix, int iy, int iadd)
{
  unsigned char *bp;
  unsigned char *sp;
  unsigned char *dp;
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
  if (offset < 0)
  {
    offset &= 0x7FFFFFFF;
    width += 256;
  }

//	printf("%2d: +x %2d +y %2d width %2d height %2d offset %d\n",
//		index, xoff, yoff, width, height, offset);

  sp = start + offset - 6;
  dp = image + xoff - ix + (yoff - iy) * iadd;
  for (i = 0; i < height; ++i)
  {
    memcpy(dp, sp, width);
    dp += iadd;
    sp += width;
  }
}

void Grp::DecodeGfxEntry(int index, unsigned char *start, unsigned char *image, int ix, int iy, int iadd)
{
  unsigned char *bp;
  unsigned char *sp;
  unsigned char *dp;
  int xoff;
  int yoff;
  int width;
  int height;
  int offset;
  unsigned char *rows;
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

  for (h = 0; h < height; ++h)
  {
//		printf("%2d: row-offset %2d\t", index, AccessLE16(rows + h * 2));
    sp = rows + AccessLE16(rows + h * 2);
    for (w = 0; w < width;)
    {
      ctrl = *sp++;
//			printf("%02X", ctrl);
      if (ctrl & 0x80)
      {
        // transparent
        ctrl &= 0x7F;
//				printf("-%d,", ctrl);
        memset(dp + h * iadd + w, mTransparent, ctrl);
        w += ctrl;
      }
      else if (ctrl & 0x40)
      {
        // repeat
        ctrl &= 0x3F;
//				printf("*%d,", ctrl);
        memset(dp + h * iadd + w, *sp++, ctrl);
        w += ctrl;
      }
      else
      {
        // set pixels
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

unsigned char *Grp::ConvertGraphic(bool gfx, unsigned char *bp, int *wp, int *hp, unsigned char *bp2)
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
  unsigned char *image;
  int IPR;

  int endereco;

  // Init pointer to 2nd animation
  if (bp2)
  {
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
  for (i = 0; i < count; ++i)
  {
    unsigned char *p;
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

    if (endereco & 0x80000000)
    {
      // high bit of width
      width += 256;
    }
    if (xoff < minx)
      minx = xoff;

    if (yoff < miny)
      miny = yoff;

    if (xoff + width > best_width)
      best_width = xoff + width;

    if (yoff + height > best_height)
      best_height = yoff + height;
  }
  // FIXME: the image isn't centered!!

//	printf("Best image size %3d, %3d\n", best_width, best_height);

  minx = 0;
  miny = 0;

  if (gfx)
  {
    best_width = max_width;
    best_height = max_height;
    IPR = 17;  // st*rcr*ft 17!
    if (count < IPR)
    {
      // images per row !!
      IPR = 1;
      length = count;
    }
    else
    {
      length = ((count + IPR - 1) / IPR) * IPR;
    }
  }
  else
  {
    max_width = best_width;
    max_height = best_height;
    IPR = 1;
    length = count;
  }

  image = (unsigned char *) malloc(best_width * best_height * length);

  Size tilesize(best_width, best_height);
  mTilesize = tilesize;

  //  Image: 0, 1, 2, 3, 4,
  //         5, 6, 7, 8, 9, ...
  if (!image)
  {
    printf("Can't allocate image\n");
  }
  // Set all to transparent.
  memset(image, mTransparent, best_width * best_height * length);

  if (gfx)
  {
    for (i = 0; i < count; ++i)
    {
        DecodeGfxEntry(i, bp, image + best_width * (i % IPR) + best_height * best_width * IPR * (i / IPR), minx, miny,
                       best_width * IPR);
    }
  }
  else
  {
    for (i = 0; i < count; ++i)
    {
      DecodeGfuEntry(i, bp, image + best_width * (i % IPR) + best_height * best_width * IPR * (i / IPR), minx, miny,
                     best_width * IPR);
    }
  }

  *wp = best_width * IPR;
  *hp = best_height * (length / IPR);

  return image;
}
