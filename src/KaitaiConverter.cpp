/*
 * KaitaiConverter.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "KaitaiConverter.h"
#include "DataChunk.h"
#include "Hurricane.h"

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
  std::shared_ptr<DataChunk> data = mHurricane->extractDataChunk(file);
  if (data)
  {
    //std::ifstream ifs(arcfile, std::ifstream::binary);
    //kaitai::kstream ks(&ifs);

    // TODO: for now just create from complete string instead of istream. Maybe change the complete
    // reader to stream based concept...
    std::string str(reinterpret_cast<char const *>(data->getDataPointer()),
                    data->getSize());
    std::shared_ptr<kaitai::kstream> ks = make_shared<kaitai::kstream>(str);
    return ks;
  }

  // TODO: hm, better create an exception
  return nullptr;
}
