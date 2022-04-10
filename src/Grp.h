/*
 * Grp.h
 *
 *      Author: Andreas Volz
 */

#ifndef GRP_H_
#define GRP_H_

// Local
#include "Converter.h"
#include "Palette.h"
#include "Storage.h"

// System
#include <string.h>
#include <memory>

/**
 * Put the code for decoding of Gfu and Gfx in Gfu parent as workaround.
 * Reason seems to be a workaround for "Hardcoded support for worker with resource repairing"
 * TODO: Find a better solution and move to to Gfx/Gfu class
 */
class Grp: public Converter
{
public:
  Grp(std::shared_ptr<Hurricane> hurricane);
  Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile);
  Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile, std::shared_ptr<Palette> pal);
  virtual ~Grp();

  /**
   * Set if the Grp image is saved as 8-bit RGBA or palette PNG
   * Default is palette PNG
   */
  void setRGBA(bool rgba);

  bool getRGBA();

  bool load(const std::string &arcfile);

  bool save(Storage filename);

  void setPalette(std::shared_ptr<Palette> pal);

  void setGFX(bool gfx);
  bool getGFX();

  void setTransparent(int transparent);

  /**
   *  Convert a Grp graphic to PNG format
   *
   *  @param arcfile File identifier in the MPQ file
   *  @param file Place to save the file on the drive (relative to game dir)
   */
  bool savePNG(const std::string &filename);

protected:
  /**
   **  Convert graphics into image.
   */
  unsigned char* ConvertGraphic(bool gfx, unsigned char *bp, int *wp, int *hp, unsigned char *bp2);

  /**
   **  Decode a entry(frame) into image.
   */
  void DecodeGfxEntry(int index, unsigned char *start, unsigned char *image, int ix, int iy, int iadd);

  /**
   **  Decode a entry(frame) into image.
   */
  void DecodeGfuEntry(int index, unsigned char *start, unsigned char *image, int ix, int iy, int iadd);

private:
  Logger mLogger;
  std::shared_ptr<Palette> mPal;
  std::string mArcfile;
  bool mRGBA;
  bool mGFX;
  int mTransparent;

};

#endif /* GRP_H_ */
