/*
 * AbstractPalette.cpp
 *
 *      Author: Andreas Volz
 */

#include "AbstractPalette.h"
#include "Palette.h"
#include "Palette2D.h"
#include "NoValidPaletteException.h"

using namespace std;

AbstractPalette::~AbstractPalette()
{

}

bool AbstractPalette::write(const std::string &filename)
{
  bool result = true;

  std::shared_ptr<DataChunk> dc_pal = createDataChunk();
  result = dc_pal->write(filename);

  return result;
}

bool AbstractPalette::read(const std::string &filename)
{
  bool result = true;

  std::shared_ptr<DataChunk> dc_pal = make_shared<DataChunk>();
  result = dc_pal->read(filename);
  if(result)
  {
    load(dc_pal);
  }

  return result;
}

std::shared_ptr<AbstractPalette> AbstractPalette::create(std::shared_ptr<DataChunk> rawPalette)
{
  if((rawPalette->getSize() == 256 * 3) || (rawPalette->getSize() == 256 * 3)) // RGBx/WPE size type
  {
    return make_shared<Palette>(rawPalette);
  }
  else if(!(rawPalette->getSize() % (256 * 3))) // PCX2D size type (size 3 and 4 are yet in the if statement)
  {
    return make_shared<Palette2D>(rawPalette);
  }

  // no valid palette
  throw NoValidPaletteException(rawPalette->getSize());

  // will never go here...
  return nullptr;
}
