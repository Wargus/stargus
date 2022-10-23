#ifndef GRPFrame_Header
#define GRPFrame_Header

/*!GRPFrame Datastructure
 *  \brief     A datastructure for holding a the specific image data
 *  \details   Contains one image from the a GRPImage, this data structure
 *              is normally in a list or vector of images.
 *  \author    Bradley Clemetson
 *  \version   1.0.0
 *  \date      July 8, 2013
 *  \copyright LGPLv2
 */

#include <list>
#include "../Exceptions/GRPFrame/GRPFrameException.hpp"

//Allow Windows to use 8/16/32 byte values
#if defined(_WIN32)
#include <stdint.h>
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
#else
#include <inttypes.h>
#endif

//Used to map what pixels are in a image
//are set to Palette values and location
//Position 0,0 is the upper left corner
struct UniquePixel
{
  int xPosition;
  int yPosition;
  uint8_t colorPaletteReference;
};

class GRPFrame
{
public:
  GRPFrame();


  //!Sets the Image Size
  /*!Sets the size of the frame width and height
   * \pre NA
   * \param[in] inputFrameWidth The image frame width (Normally GrpFrame's maxWidth)
   * \param[in] inputFrameHeight The image frame height (Normally GrpFrame's maxHeight)
   * \note Would like to use this is query the owner GRPImage if bigger then maxWidth or maxheight*/
  void SetImageSize(const uint8_t &inputFrameWidth, const uint8_t &inputFrameHeight);

  //!Gets the image width
  /*!Gets the Image width
   * \pre NA
   * \returns The image width
   * \note NA*/
  uint8_t GetImageWidth();

  //!Gets the image height
  /*!Gets the Image height
   * \pre NA
   * \returns The image height
   * \note NA*/
  uint8_t GetImageHeight();

  //!Sets the Image Size
  /*!Sets the size of the frame width and height
   * \pre NA
   * \param[in] inputXOffset The initial image X offset where the start of the image is to be drawn
   * \param[in] inputYOffset The initial image Y offset where the start of the image is to be drawn
   * \note Would like to use this is query the owner GRPImage if bigger then maxWidth or maxheight*/
  void SetImageOffsets(const uint8_t &inputXOffset, const uint8_t &inputYOffset);

  //!Gets the image X offset
  /*!Gets the Image X offset
   * \pre NA
   * \returns The image X offset
   * \note NA*/
  uint8_t GetXOffset();

  //!Gets the image Y offset
  /*!Gets the Image Y offset
   * \pre NA
   * \returns The image Y offset
   * \note NA*/
  uint8_t GetYOffset();

  //!Sets the Image Size
  /*!Sets the size of the frame width and height
   * \pre NA
   * \param[in] inputDataOffset The initial image X offset where the start of the image is to be drawn
   * \note Would like to use this is query the owner GRPImage if bigger inputDataOffset is bigger then whole file*/
  void SetDataOffset(const uint32_t &inputDataOffset);

  //!Gets the image data offset
  /*!Gets the Image data offset
   * \pre NA
   * \returns The image data offset
   * \note NA*/
  uint32_t GetDataOffset();



  //The unique pixel data, to be placed on to the final converted canvas
  //or screen surface
  std::list<UniquePixel> frameData;

protected:

  //The drawing image width/height of the image in the frame
  uint8_t width;
  uint8_t height;

  //Tells us where to begin drawing
  uint8_t xOffset;
  uint8_t yOffset;

  //Offset of the Framedata (starting at the beginning of the GRPfile)
  uint32_t dataOffset;
private:
};

#endif