/*
 * AbstractPalette.h
 *
 *      Author: Andreas Volz
 */

#ifndef ABSTRACTPALETTE_H
#define ABSTRACTPALETTE_H

// project
#include "DataChunk.h"

// system
#include <memory>

class AbstractPalette
{
public:
  virtual ~AbstractPalette();

  virtual std::shared_ptr<DataChunk> createDataChunk() = 0;

  virtual void load(std::shared_ptr<DataChunk> rawPalette) = 0;

  virtual bool write(const std::string &filename);

  virtual bool read(const std::string &filename);

  /**
   * Creator function for the abstract factory design
   */
  static std::shared_ptr<AbstractPalette> create(std::shared_ptr<DataChunk> rawPalette);

protected:

};

#endif /* ABSTRACTPALETTE_H */
