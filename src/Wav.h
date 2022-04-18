/*
 * Wav.h
 *
 *      Author: Andreas Volz
 */

#ifndef WAV_H
#define WAV_H

// project
#include "Converter.h"
#include "Logger.h"
#include "Storage.h"

// system
#include <string>

class Wav : public Converter
{
public:
  Wav(std::shared_ptr<Hurricane> hurricane);
  Wav(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile);
  virtual ~Wav();

  bool convert(const std::string &arcfile, Storage storage);

private:
  Logger mLogger;
};

#endif /* WAV_H*/
