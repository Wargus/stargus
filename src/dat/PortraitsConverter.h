/*
 * PortraitsConverter.h
 *
 *      Author: Andreas Volz
 */

#ifndef PORTRAITSCONVERTER_H
#define PORTRAITSCONVERTER_H

// project
#include "DataHub.h"
#include "Storage.h"

// system

namespace dat
{

class PortraitsConverter : public Converter
{
public:
  PortraitsConverter(std::shared_ptr<Hurricane> hurricane, DataHub &datahub);
  virtual ~PortraitsConverter();

  bool convert();

private:
  /**
   * check all smk files for a portrait, export them, convert to mng and save the raw name
   * @param portrait_list The function fills this vector to later export to LUA
   */
  bool convertMngPortraits(const std::string &arcfile, std::vector<std::string> &portrait_list);


  // if used more often put into a utils namespace...
  /*template<typename T>
  void removeDuplicates(std::vector<T>& vec)
  {
      std::sort(vec.begin(), vec.end());
      vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
  }*/

  DataHub &mDatahub;
};

} /* namespace dat */

#endif /* PORTRAITSCONVERTER_H */
