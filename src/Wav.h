/*
 * Wav.h
 *
 *      Author: Andreas Volz
 */

#ifndef WAV_H
#define WAV_H

// project
#include "Converter.h"
#include "Storage.h"

// system
#include <string>

class Wav : public Converter
{
public:
  Wav(std::shared_ptr<Hurricane> hurricane);
  Wav(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile);
  virtual ~Wav();

  /**
   * storage the file basename without any file extension to let the converter the flexibility to add own extension
   */
  bool convert(const std::string &arcfile, Storage storage);

private:

};

#endif /* WAV_H*/
