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
  mRGBA(false)
{
}

Grp::Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
  Converter(hurricane),
  mRGBA(false)
{
  load(arcfile);
}

Grp::Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile, std::shared_ptr<AbstractPalette> pal) :
  Converter(hurricane),
  mPal(pal),
  mRGBA(false)
{
  load(arcfile);
}

Grp::~Grp()
{

}

void Grp::setPalette(std::shared_ptr<AbstractPalette> pal)
{
  mPal = pal;

  mGRPImage.SetColorPalette(pal);
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
  //mArcfile = arcfile;

  std::shared_ptr<DataChunk> dcGrp = mHurricane->extractDataChunk(arcfile);

  std::vector<char> GrpVec = dcGrp->getCharVector();

  if(dcGrp)
  {
    mGRPImage.LoadImage(&GrpVec, false);
  }

  return true;
}

bool Grp::save(Storage filename)
{
  bool result = true;

  int IPR = 17;
  int end_frame = mGRPImage.getNumberOfFrames();

  // all IPR < 17 are buildings or similar and stratagus needs them in one image per row
  if(end_frame < IPR)
  {
    IPR = 1;
  }

  mGRPImage.SaveStitchedPNG(filename.getFullPath(), 0, end_frame, IPR, mRGBA);

  return result;
}

Size Grp::getTileSize()
{
  Size size (mGRPImage.getMaxImageWidth(), mGRPImage.getMaxImageHeight());
  return size;
}
