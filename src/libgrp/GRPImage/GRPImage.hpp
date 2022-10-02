/*!
 *  \brief     The main
 *  \details   This class runs all the underlying generic functions required
 * 				for nearly all objects in the framework
 *  \author    Bradley Clemetson, from GRPLib Authors
 *  \version   1.0.0
 *  \date      Jan 13, 2013
 *  \copyright LGPLv2
 *  \section basicsGRPFormat Basic Format Aspects
 *  \section conventions Naming Conventions
 *  \section av
 *  \image html GRPFileLayout.png
 */
#ifndef GRPImage_Header
#define GRPImage_Header

#include "Palette.h"

#include "libgrp/GRPFrame/GRPFrame.hpp"

#include "libgrp/Exceptions/GRPImage/GRPImageException.hpp"
#include <list>
#include <fstream>

//Gives the ability to convert images to other formats.
#if HAVE_IMAGEMAGICKPP
#include <sstream>
#include <iomanip>
#include <Magick++/Image.h>
#include <Magick++/Pixels.h>
#endif

//Allow Windows to use 8/16/32 byte values
#if defined(_WIN32)
#include <stdint.h>
typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;
#else
#include <unordered_map>
#include <inttypes.h>
#endif

enum GRPImageType {STANDARD, SHADOW};

class GRPImage
{

public:
  //!Set image data from memory
  /*! Use the image data that is loaded in a the specified
   * vector.
   * \pre The inputInput vector must be defined and contain
   *      valid grp image data. Otherwise there will be decoding
   *      errors. (garbled up junk images)
   * \param[in] inputPalette The memory location of the image
   *      to be decoded/encoded.
   * \param[in] removeDuplicates Remove GRPFrames that are the same
   * \warning This will not make a copy of the std::vector<char> data
   *      so if you delete the vector before/during processing it will likly crash.
   * \note Same thing as LoadImage, but on object construction*/
  GRPImage(std::vector<char> *inputImage, bool removeDuplicates = true);

  //!Load image data from a file (.grp)
  /*! Load a GRP file to use when decoding/encoding
   * a GRPImage.
   * \pre Filepath must be to a valid .grp image file
   * \post The file is loaded into memory for the GRPImage
   * \param[in] filePath The file path to the grp image file
   * \param[in] removeDuplicates Remove GRPFrames that are the same
   * \note NA*/
  GRPImage(std::string filePath, bool removeDuplicates = true);

  //!Deallocates the GRPImage and it's data
  /*! Deallocated all data related to the GRP Image
   * \pre NA
   * \post Data is deleted
   * \note NA*/
  ~GRPImage();

  //!Set image data from memory
  /*! Use the image data that is loaded in a the specified
   * vector.
   * \pre The inputInput vector must be defined and contain
   *      valid grp image data. Otherwise there will be decoding
   *      errors. (garbled up junk images)
   * \param[in] inputPalette The memory location of the image
   *      to be decoded/encoded.
   * \param[in] removeDuplicates Remove GRPFrames that are the same
   * \warning This will not make a copy of the std::vector<char> data
   *      so if you delete the vector before/during processing it will likly crash.
   * \note NA*/
  void LoadImage(std::vector<char> *inputImage, bool removeDuplicates = true);

  //!Load image data from a file (.grp)
  /*! Load a GRP file to use when decoding/encoding
   * a GRPImage.
   * \pre Filepath must be to a valid .grp image file
   * \post The file is loaded into memory for the GRPImage
   * \param[in] filePath The file path to the grp image file
   * \note NA*/
  void LoadImage(std::string filePath, bool removeDuplicates = true);

  //!Return the number of frames in a GRPImage
  /*! Return the number of frames in a GRP image animation.
   * \pre GRP image data must be defined and loaded into
   *      imageData.
   * \returns The number of image frames in a GRP Image.
   * \note NA*/
  uint16_t getNumberOfFrames() const;

  //!Return the maximum width of any GRP image Frame
  /*! Returns the maximum width of any GRP image Frame
   *  allowing for easier decoding and encoding to a
   *  single image.
   * \pre GRPImage must be defined and have imageData loaded
   * \returns The maximum width of any individual GRP Frame.
   * \note NA*/
  uint16_t getMaxImageWidth() const;
  //!Return the maximum height of any GRP image Frame
  /*! Returns the maximum height of any GRP image Frame
   *  allowing for easier decoding and encoding to a
   *  single image.
   * \pre GRPImage must be defined and have imageData loaded
   * \returns The maximum height of any individual GRP Frame.
   * \note NA*/
  uint16_t getMaxImageHeight() const;

  //!Set the desired colorPalette to use
  /*!Sets the colorPalette that will be used as reference for image
   *conversion.
   * \param[in] selectedColorPalette The Palette to apply to images
   * \warning GRPImage will not delete the color palette upon deallocation,
   * \warning If the palette is not the correct palette for the image
   *      during the conversion process you may get a invalidColors or
   *      throw exception
   * \note NA*/
  void SetColorPalette(std::shared_ptr<Palette> selectedColorPalette);

  //!Save the GRPImage frames to a file via ImageMaigck
  /*!Save the GRPImage frames into the file format of your choosing
   * \pre GRPImage is loaded.
   * \post Outputs a image to the ourFilePath.
   * \param[in] outFilePath The output image file path.
   * \param[in] startingFrame The first image that you would like saved.
   * \param[in] endingFrame The frame you would like to stop saving on.
   * \param[in] singleStitchedImage Stitch the GRP frames together into one image.
   * \param[in] imagesPerRow If stitching is enabled, how many images should be save per row.
   * \note NA*/
  void SaveConvertedImage(std::string outFilePath, int startingFrame, int endingFrame, bool singleStitchedImage = true, int imagesPerRow = 10);

  void SaveConvertedPNG(std::string outFilePath, int startingFrame, int endingFrame, bool singleStitchedImage, int imagesPerRow);

protected:

  //!Deleted any GRPImage data for reuse
  /*! Deallocated all data related to the GRP Image
   * \pre NA
   * \post Data is deleted
   * \note NA*/
  void CleanGRPImage();

  //!Decode the GRPFrameData
  /*!Decode the GRP compression and save the unique pixels to the GRPFrame datastruct
   * \pre GRPImage Loaded
   * \post GRPImage Frame is decoded into the frame
   * \param[in] inputData A vector of the GRPImage file data
   * \param[in] targetFrame The frame to store the resulting image data
   * \note NA*/
  void DecodeGRPFrameData(std::vector<char> *inputData, GRPFrame *targetFrame);

  /*!Decode the GRP uncompressed data and save the unique pixels to the GRPFrame datastruct
   *
   */
  void DecodeGRPFrameDataUncompressed(std::vector<char> *inputData, GRPFrame *targetFrame);

private:
  bool DetectUncompressed(std::vector<char> *inputImage);

  void DecodeHeader(std::vector<char> *inputImage);

  //The decoded GRPFrames
  std::vector<GRPFrame *> mImageFrames;

  //The palette that will be used during conversion
  std::shared_ptr<Palette> mCurrentPalette;


  //GRPimage Header
  uint16_t mNumberOfFrames;
  uint16_t mMaxImageWidth;
  uint16_t mMaxImageHeight;
  bool mUncompressed;
};
#endif
