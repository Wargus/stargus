/*
 * KaitaiConverter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "KaitaiConverter.h"
#include "DataChunk.h"
#include "Hurricane.h"

// system
#include <iostream>

using namespace std;

KaitaiConverter::KaitaiConverter(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane)
{

}

KaitaiConverter::~KaitaiConverter()
{

}

std::shared_ptr<kaitai::kstream> KaitaiConverter::getKaitaiStream(const std::string &file)
{
  std::shared_ptr<std::istream> stream = mHurricane->extractStream(file);

  std::string s;
  std::ostringstream os;
  os<<stream->rdbuf();
  s=os.str();

  std::shared_ptr<kaitai::kstream> ks = make_shared<kaitai::kstream>(s);

  return ks;
}
