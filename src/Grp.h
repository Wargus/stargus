/*
 * Grp.h
 *
 *      Author: Andreas Volz
 */

#ifndef GRP_H
#define GRP_H

// Local
#include "Converter.h"
#include "Palette.h"
#include "Storage.h"
#include "Size.h"
#include "Palette2D.h"
#include "libgrp/libgrp.hpp"

// System
#include <string.h>
#include <memory>

/**
 *
 */
class Grp: public Converter
{
public:
  Grp(std::shared_ptr<Hurricane> hurricane);
  Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile);
  Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile, std::shared_ptr<AbstractPalette> pal);
  virtual ~Grp();

  /**
   * Set if the Grp image is saved as 8-bit RGBA or palette PNG
   * Default is palette PNG
   */
  void setRGBA(bool rgba);

  bool getRGBA();

  bool load(const std::string &arcfile);

  /**
   *  Convert a Grp graphic to PNG format
   *
   *  @param file Place to save the file on the drive (relative to game dir)
   */
  bool save(Storage filename);

  void setPalette(std::shared_ptr<AbstractPalette> pal);

  Size getTileSize();

protected: // TODO: maybe back to private after Widget redesign
  std::shared_ptr<AbstractPalette> mPal;
  GRPImage mGRPImage;
  //std::string mArcfile;
  bool mRGBA;
  //int mTransparent;
};

#endif /* GRP_H */
