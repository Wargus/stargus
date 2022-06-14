/*
 * UIConsole.h
 *
 *      Author: Andreas Volz
 */

#ifndef UICONSOLE_H
#define UICONSOLE_H

// project
#include "Converter.h"
#include "Storage.h"

// system
#include <string>
#include <memory>

/**
 * Draft idea:
 * - get tconsole.pcx, pconsole.pcx, zconsole.pcx
 * - cut it somewhere in the middle
 * - define an area which is suited as copy fill area
 *   - or provide a contrib one
 * - generate three images
 * - use them in LUA to generate a dynamic width image
 * - or do this all in a script
 */
class UIConsole : public Converter
{
public:
  UIConsole(std::shared_ptr<Hurricane> hurricane);
  virtual ~UIConsole();

  bool convert(Storage pngfile, int left, int right);

private:
  bool callConvert(const std::string &cmd);
};

#endif /* UICONSOLE_H */
