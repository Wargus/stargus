#include "GRPImage.hpp"
#include "PngExporter.h"

#include <string.h>
#include <iostream>

using namespace std;

//#define VERBOSE 10 // debug

GRPImage::GRPImage(std::vector<char> *inputImage, bool removeDuplicates) :
  mCurrentPalette(nullptr),
  mNumberOfFrames(0),
  mMaxImageWidth(0),
  mMaxImageHeight(0),
  mUncompressed(false)
{
  LoadImage(inputImage, removeDuplicates);
}

GRPImage::GRPImage(std::string filePath, bool removeDuplicates) :
  mCurrentPalette(nullptr),
  mNumberOfFrames(0),
  mMaxImageWidth(0),
  mMaxImageHeight(0),
  mUncompressed(false)
{
  LoadImage(filePath, removeDuplicates);
}

GRPImage::~GRPImage()
{
  CleanGRPImage();
  if(mCurrentPalette != NULL)
  {
    mCurrentPalette = NULL;
  }
}

bool GRPImage::DetectUncompressed(std::vector<char> *inputImage)
{
  bool uncompressed = false;

  std::vector<char>::iterator currentDataPosition = inputImage->begin();

  // jump over the basic GRP header info
  currentDataPosition += 2;

  // jump over the maximum image width & height
  currentDataPosition += 2;
  currentDataPosition += 2;

  //Temporary image demension placeholders
  uint8_t tempWidth = 0;
  uint8_t tempHeight = 0;
  uint32_t tempDataOffset = 0;

  uint32_t firstOffset = 0;
  int imagePayload = 0;

  //Create a hash table to stop the creation of duplicates
  std::unordered_map<uint32_t, bool> uniqueGRPImages;
  std::unordered_map<uint32_t, bool>::const_iterator uniqueGRPCheck;

  //Load each GRP Header into a GRPFrame & Allocate
  for(int currentGRPFrame = 0; currentGRPFrame < mNumberOfFrames; currentGRPFrame++)
  {
    //Jump over the image xOffset
    currentDataPosition += 1;

    //Jump over the image yOffset
    currentDataPosition += 1;

    //Read in the image width
    std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &tempWidth);
    currentDataPosition += 1;

    //Read in the image height
    std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &tempHeight);
    currentDataPosition += 1;

    //Read in the image dataOffset
    std::copy(currentDataPosition, (currentDataPosition + 4),(char *) &tempDataOffset);
    currentDataPosition += 4;

    uniqueGRPCheck = uniqueGRPImages.find(tempDataOffset);
    if(uniqueGRPCheck == uniqueGRPImages.end())
    {
      imagePayload += tempWidth * tempHeight;
    }

    uniqueGRPImages.insert(std::make_pair<uint32_t,bool>((uint32_t)tempDataOffset,true));

    if(firstOffset == 0)
    {
      firstOffset = tempDataOffset;
    }
  }

  //cout << "completeImageSize: "  << to_string(imagePayload + firstOffset) << endl;

  if(firstOffset + imagePayload == inputImage->size())
  {
    uncompressed = true;
  }
  else
  {
    uncompressed = false;
  }

  return uncompressed;
}

void GRPImage::DecodeHeader(std::vector<char> *inputImage)
{
  std::vector<char>::iterator currentDataPosition = inputImage->begin();

  //Get basic GRP header info
  std::copy(currentDataPosition,(currentDataPosition + 2),(char *) &mNumberOfFrames);
  currentDataPosition += 2;

  //Get the maximum image width & height
  std::copy(currentDataPosition, (currentDataPosition + 2),(char *) &mMaxImageWidth);
  currentDataPosition += 2;

  std::copy(currentDataPosition, (currentDataPosition + 2),(char *) &mMaxImageHeight);
  currentDataPosition += 2;
}

void GRPImage::LoadImage(std::vector<char> *inputImage, bool removeDuplicates)
{
  CleanGRPImage();
  std::vector<char>::iterator currentDataPosition = inputImage->begin();

  DecodeHeader(inputImage);

  mUncompressed = DetectUncompressed(inputImage);

  // jump over the basic GRP header info
  currentDataPosition += 2;

  // jump over the maximum image width & height
  currentDataPosition += 2;
  currentDataPosition += 2;

  if(mUncompressed)
  {
    //cout << "uncompressed Grp" << endl;
  }

#if VERBOSE >= 2
  std::cout << "GRP Image Number of Frames: " << mNumberOfFrames << " maxWidth: " << mMaxImageWidth << " maxHeight: " << mMaxImageHeight << '\n';
#endif

  //Temporary image demension placeholders
  uint8_t tempValue1 = 0;
  uint8_t tempValue2 = 0;
  uint32_t tempDataOffset = 0;

  //Create a hash table to stop the creation of duplicates
  std::unordered_map<uint32_t, bool> uniqueGRPImages;
  std::unordered_map<uint32_t, bool>::const_iterator uniqueGRPCheck;

  int bestWidth = 0;
  int bestHeight = 0;

  //Load each GRP Header into a GRPFrame & Allocate
  for(int currentGRPFrame = 0; currentGRPFrame < mNumberOfFrames; currentGRPFrame++)
  {
    GRPFrame *currentImageFrame = new GRPFrame;

    //Read in the image xOffset
    std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &tempValue1);
    currentDataPosition += 1;

    //Read in the image yOffset
    std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &tempValue2);
    currentDataPosition += 1;
    currentImageFrame->SetImageOffsets(tempValue1, tempValue2);

    //Read in the image width
    std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &tempValue1);
    currentDataPosition += 1;

    //Read in the image height
    std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &tempValue2);
    currentDataPosition += 1;
    currentImageFrame->SetImageSize(tempValue1, tempValue2);

    //Read in the image dataOffset
    std::copy(currentDataPosition, (currentDataPosition + 4),(char *) &tempDataOffset);
    currentDataPosition += 4;
    currentImageFrame->SetDataOffset(tempDataOffset);

    // calculate the best width for that image (only for uncompressed)
    if(mUncompressed)
    {
      if (currentImageFrame->GetXOffset() + currentImageFrame->GetImageWidth() > bestWidth)
      {
        bestWidth = currentImageFrame->GetXOffset() + currentImageFrame->GetImageWidth();
      }

      if (currentImageFrame->GetYOffset() + currentImageFrame->GetImageHeight() > bestHeight)
      {
        bestHeight = currentImageFrame->GetYOffset() + currentImageFrame->GetImageHeight();
      }
      mMaxImageWidth = bestWidth;
      mMaxImageHeight = bestHeight;
    }

#if VERBOSE >= 2
    std::cout << "Current Frame: " << currentGRPFrame << " Width: " << (int) currentImageFrame->GetImageWidth() << " Height: "
              << (int) currentImageFrame->GetImageHeight() << "\nxPosition: " << (int) currentImageFrame->GetXOffset()
              << " yPosition: " << (int) currentImageFrame->GetYOffset() << " with offset " << (int)currentImageFrame->GetDataOffset() << '\n';
#endif
    uniqueGRPCheck = uniqueGRPImages.find(currentImageFrame->GetDataOffset());
    if(removeDuplicates && (uniqueGRPCheck != uniqueGRPImages.end()))
    {

    }
    else
    {
      //The GRPImage is unique save in the unordered set
      uniqueGRPImages.insert(std::make_pair<uint32_t,bool>(currentImageFrame->GetDataOffset(),true));

      //Decode Frame here
      if(mUncompressed)
      {
        DecodeGRPFrameDataUncompressed(inputImage, currentImageFrame);
      }
      else
      {
        DecodeGRPFrameData(inputImage, currentImageFrame);
      }

      mImageFrames.push_back(currentImageFrame);
    }
  }

  if (removeDuplicates)
  {
    mNumberOfFrames = mImageFrames.size();
  }
}

void GRPImage::LoadImage(std::string filePath, bool removeDuplicates)
{
  DataChunk dcImage;
  dcImage.read(filePath);
  vector<char> vecImage = dcImage.getCharVector();

  LoadImage(&vecImage, removeDuplicates);
}

void GRPImage::DecodeGRPFrameDataUncompressed(std::vector<char> *inputData, GRPFrame *targetFrame)
{
  if(targetFrame == NULL || (targetFrame->frameData.size() == 0))
  {
    GRPImageNoFrameLoaded noFrameLoaded;
    noFrameLoaded.SetErrorMessage("No GRP Frame is loaded");
  }
  if(mCurrentPalette == NULL)
  {
    GRPImageNoLoadedPaletteSet noPaletteLoaded;
    noPaletteLoaded.SetErrorMessage("No palette has been set or loaded");
  }

  //Seek to the Row offset data
  std::vector<char>::iterator currentDataPosition = inputData->begin();
  currentDataPosition += targetFrame->GetDataOffset();

  //The currentRow (x coordinate) that the decoder is at, it is used to
  //set the image position.
  int currentProcessingRow = 0;

  //The initial byte of data from the GRPFile
  //It is often the operation that will be done
  //of the proceding data
  uint8_t rawPacket;

  //The struct keeps a (X,Y) coordinates to the position
  //of the referenced color to allow for drawing on the screen
  //or Imagemagick to convert.
  UniquePixel currentUniquePixel;

  //Goto each row and process the row data
  for(int currentProcessingHeight = 0; currentProcessingHeight < targetFrame->GetImageHeight(); currentProcessingHeight++)
  {

#if VERBOSE >= 2
    //std::cout << "Current row offset is: " << (targetFrame->GetDataOffset() + (imageRowOffsets.at(currentProcessingHeight))) << '\n';
#endif
    //Seek to the point of the first byte in the rowData from the
    //1.Skip over to the Frame data
    //2.Skip over the size of the targetFrame->size() last time read bytes
    currentDataPosition = inputData->begin() + targetFrame->frameData.size();
    currentDataPosition += (targetFrame->GetDataOffset());

    currentProcessingRow = 0;

    while(currentProcessingRow < targetFrame->GetImageWidth())
    {

        std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &rawPacket);
        currentDataPosition += 1;

        currentUniquePixel.xPosition = currentProcessingRow;
        currentUniquePixel.yPosition = currentProcessingHeight;
        currentUniquePixel.colorPaletteReference = rawPacket;
        targetFrame->frameData.push_back(currentUniquePixel);

        currentProcessingRow++;
    }
  }

#if VERBOSE >= 5
  std::cout << "Frame data is size: " << targetFrame->frameData.size() << '\n';
  for(std::list<UniquePixel>::iterator it = targetFrame->frameData.begin(); it != targetFrame->frameData.end(); it++)
  {
    std::cout << '(' << it->xPosition << ',' << it->yPosition << ") = " << (int) it->colorPaletteReference << '\n';
  }
#endif
}

void GRPImage::DecodeGRPFrameData(std::vector<char> *inputData, GRPFrame *targetFrame)
{
  if(targetFrame == NULL || (targetFrame->frameData.size() == 0))
  {
    GRPImageNoFrameLoaded noFrameLoaded;
    noFrameLoaded.SetErrorMessage("No GRP Frame is loaded");
  }
  if(mCurrentPalette == NULL)
  {
    GRPImageNoLoadedPaletteSet noPaletteLoaded;
    noPaletteLoaded.SetErrorMessage("No palette has been set or loaded");
  }


  //Seek to the Row offset data
  std::vector<char>::iterator currentDataPosition = inputData->begin();
  currentDataPosition += targetFrame->GetDataOffset();

  //Create a vector of all the Image row offsets
  std::vector<uint16_t> imageRowOffsets;
  imageRowOffsets.resize(targetFrame->GetImageHeight());

  //Read in the ImageRow offsets
  for (int currentReadingRowOffset = 0; currentReadingRowOffset < targetFrame->GetImageHeight(); currentReadingRowOffset++)
  {
    std::copy(currentDataPosition, (currentDataPosition + 2),(char *) &imageRowOffsets.at(currentReadingRowOffset));
    currentDataPosition += 2;
  }

  //The currentRow (x coordinate) that the decoder is at, it is used to
  //set the image position.
  int currentProcessingRow = 0;

  //The initial byte of data from the GRPFile
  //It is often the operation that will be done
  //of the proceding data
  uint8_t rawPacket;

  //The references to a particular color
  uint8_t convertedPacket;

  //The struct keeps a (X,Y) coordinates to the position
  //of the referenced color to allow for drawing on the screen
  //or Imagemagick to convert.
  UniquePixel currentUniquePixel;


  //Goto each row and process the row data
  for(int currentProcessingHeight = 0; currentProcessingHeight < targetFrame->GetImageHeight(); currentProcessingHeight++)
  {

#if VERBOSE >= 2
    std::cout << "Current row offset is: " << (targetFrame->GetDataOffset() + (imageRowOffsets.at(currentProcessingHeight))) << '\n';
#endif
    //Seek to the point of the first byte in the rowData from the
    //1.Skip over to the Frame data
    //2.Skip over by the Row offset mentioned in the list
    currentDataPosition = inputData->begin();
    currentDataPosition += (targetFrame->GetDataOffset() + imageRowOffsets.at(currentProcessingHeight));

    currentProcessingRow = 0;

    while(currentProcessingRow < targetFrame->GetImageWidth())
    {
      std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &rawPacket);
      currentDataPosition += 1;
      if(!(rawPacket & 0x80))
      {
        //Repeat Operation (The first byte indicates a repeat pixel operation)
        //The next byte indicates how far down the row to repeat.
        if(rawPacket & 0x40)
        {
          rawPacket &= 0x3f;
          std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &convertedPacket);
          currentDataPosition += 1;

          //Set the Player color (Not implemented yet :|
          //covertedPacket = tableof unitColor[ colorbyte+gr_gamenr];
          int operationCounter = rawPacket;
          currentUniquePixel.xPosition = currentProcessingRow;
          do
          {

            currentUniquePixel.yPosition = currentProcessingHeight;
            currentUniquePixel.colorPaletteReference = convertedPacket;
            targetFrame->frameData.push_back(currentUniquePixel);
            currentUniquePixel.xPosition++;
          }
          while (--operationCounter);

          currentProcessingRow += rawPacket;
        }
        else
        {
          //Copy Pixel Operation, and how many pixels to copy directly
          int operationCounter = rawPacket;
          if(operationCounter > 0)
          {
            do
            {
              std::copy(currentDataPosition, (currentDataPosition + 1),(char *) &convertedPacket);
              currentDataPosition += 1;

              currentUniquePixel.xPosition = currentProcessingRow;
              currentUniquePixel.yPosition = currentProcessingHeight;
              currentUniquePixel.colorPaletteReference = convertedPacket;
              targetFrame->frameData.push_back(currentUniquePixel);
              currentProcessingRow++;
            }
            while (--operationCounter);
          }
        }
      }
      else
      {
        //Skip the next "rawPacket" # of pixels
        rawPacket &= 0x7f;
        currentProcessingRow += rawPacket;
      }
    }
  }

#if VERBOSE >= 5
  std::cout << "Frame data is size: " << targetFrame->frameData.size() << '\n';
  for(std::list<UniquePixel>::iterator it = targetFrame->frameData.begin(); it != targetFrame->frameData.end(); it++)
  {
    std::cout << '(' << it->xPosition << ',' << it->yPosition << ") = " << (int) it->colorPaletteReference << '\n';
  }
#endif

}

uint16_t GRPImage::getNumberOfFrames() const
{
  return mNumberOfFrames;
}
uint16_t GRPImage::getMaxImageWidth() const
{
  return mMaxImageWidth;
}
uint16_t GRPImage::getMaxImageHeight() const
{
  return mMaxImageHeight;
}

void GRPImage::SetColorPalette(std::shared_ptr<Palette> selectedColorPalette)
{
  if(selectedColorPalette)
    mCurrentPalette = selectedColorPalette;
}

void GRPImage::SaveConvertedPNG(std::string outFilePath, int startingFrame, int endingFrame, bool singleStitchedImage, int imagesPerRow)
{
  if(!mCurrentPalette)
  {
    GRPImageNoLoadedPaletteSet noPalette;
    noPalette.SetErrorMessage("No loaded set");
  }

  shared_ptr<PaletteImage> paletteImage;

  if(imagesPerRow >= mNumberOfFrames)
  {
    imagesPerRow = mNumberOfFrames;
  }

  int image_width = (mMaxImageWidth * imagesPerRow);
  int image_height = (mMaxImageHeight * (ceil( (float)mNumberOfFrames/imagesPerRow)));

  if(singleStitchedImage)
  {
    // create the complete image with all stitched small images
    paletteImage = make_shared<PaletteImage>(Size(image_width, image_height));
  }
  else
  {
    // create later in the loop the small ones...
  }
  Color currentPalettePixel;
  std::stringstream fileOutPath;
  int currentImageDestinationColumn = 0;
  int currentImageDestinationRow = 0;

  for(int currentProcessingFrame = startingFrame; currentProcessingFrame < endingFrame; ++currentProcessingFrame)
  {
    GRPFrame *currentFrame = mImageFrames.at(currentProcessingFrame);

    // create a image for each frame
    if(!singleStitchedImage)
    {
      //cout << "image size: " << to_string(currentFrame->GetImageWidth()) << "/" <<  to_string(currentFrame->GetImageHeight()) << endl;
      paletteImage = make_shared<PaletteImage>(Size(currentFrame->GetImageWidth(), currentFrame->GetImageHeight()));
    }

    //If a row in a stitched image is complete, move onto the next row
    if(singleStitchedImage && (currentImageDestinationRow >= imagesPerRow))
    {
      currentImageDestinationColumn++;
      currentImageDestinationRow = 0;
    }

    //Start appling the pixels with the refence colorpalettes
    for (std::list<UniquePixel>::iterator currentProcessPixel = currentFrame->frameData.begin(); currentProcessPixel != currentFrame->frameData.end(); currentProcessPixel++)
    {
      if(singleStitchedImage)
      {
        Pos pixel_pos((currentFrame->GetXOffset() + currentProcessPixel->xPosition) + (mMaxImageWidth * currentImageDestinationRow),
                      (currentFrame->GetYOffset() + currentProcessPixel->yPosition) + (mMaxImageHeight * currentImageDestinationColumn) );

        paletteImage->at(pixel_pos) = currentProcessPixel->colorPaletteReference;
      }
      else
      {
        Pos pixel_pos((currentProcessPixel->xPosition),
                      (currentProcessPixel->yPosition));
        //cout << "put color to: " << to_string(pixel_pos.getX()) << "/" << to_string(pixel_pos.getY()) << endl;

        paletteImage->at(pixel_pos) = currentProcessPixel->colorPaletteReference;
      }

    }

    //If not stitched it's time to write the current frame to a file
    if(!singleStitchedImage)
    {
      string frameOutput = "frame" + to_string(currentProcessingFrame) + "_" + outFilePath;

      PngExporter::save(frameOutput, *paletteImage, *mCurrentPalette, 0);
    }
    //Otherwise continue writing down the row
    else
    {
      currentImageDestinationRow++;
    }

  }
  //Now that all the pixels are in place, lets write the result to disk
  if(singleStitchedImage)
  {
    PngExporter::save(outFilePath, *paletteImage, *mCurrentPalette, 0);
  }
}

#if HAVE_IMAGEMAGICKPP
void GRPImage::SaveConvertedImage(std::string outFilePath, int startingFrame, int endingFrame, bool singleStitchedImage, int imagesPerRow)
{

  if(!mCurrentPalette)
  {
    GRPImageNoLoadedPaletteSet noPalette;
    noPalette.SetErrorMessage("No loaded set");
  }
  MagickCore::MagickCoreGenesis(NULL, MagickCore::MagickFalse);
  Magick::Image *convertedImage;
  //Due to how Imagemagick creates the image it must be set before usage and must be resized proportionally
  if(imagesPerRow >= mNumberOfFrames)
  {
    imagesPerRow = mNumberOfFrames;
  }
  if(singleStitchedImage)
  {
    convertedImage = new Magick::Image(Magick::Geometry((mMaxImageWidth * imagesPerRow), (mMaxImageHeight * (ceil( (float)mNumberOfFrames/imagesPerRow)))), "transparent");
  }
  else
  {
    convertedImage = new Magick::Image(Magick::Geometry(mMaxImageWidth, mMaxImageHeight), "transparent");
    //We will erase the image after writing the last processed image to disk
    convertedImage->backgroundColor("transparent");
  }
  Color currentPalettePixel;
  std::stringstream fileOutPath;
  Magick::ColorRGB currentMagickPixel;
  currentMagickPixel.alpha(0);
  int currentImageDestinationColumn = 0;
  int currentImageDestinationRow = 0;


  for(int currentProcessingFrame = startingFrame; currentProcessingFrame < endingFrame; ++currentProcessingFrame)
  {
    GRPFrame *currentFrame = mImageFrames.at(currentProcessingFrame);

    //If a row in a stitched image is complete, move onto the next row
    if(singleStitchedImage && (currentImageDestinationRow >= imagesPerRow))
    {
      currentImageDestinationColumn++;
      currentImageDestinationRow = 0;
    }

    //Start appling the pixels with the refence colorpalettes
    for (std::list<UniquePixel>::iterator currentProcessPixel = currentFrame->frameData.begin(); currentProcessPixel != currentFrame->frameData.end(); currentProcessPixel++)
    {
      currentPalettePixel = mCurrentPalette->at(currentProcessPixel->colorPaletteReference);

      currentMagickPixel.red(currentPalettePixel.getRed() / 255);
      currentMagickPixel.green(currentPalettePixel.getGreen() / 255);
      currentMagickPixel.blue(currentPalettePixel.getBlue() / 255);


      if(singleStitchedImage)
      {
        convertedImage->pixelColor(((currentFrame->GetXOffset() + currentProcessPixel->xPosition) + (mMaxImageWidth * currentImageDestinationRow)), ((currentFrame->GetYOffset() + currentProcessPixel->yPosition) + (mMaxImageHeight * currentImageDestinationColumn)), currentMagickPixel);
      }
      else
      {
        convertedImage->pixelColor((currentFrame->GetXOffset() + currentProcessPixel->xPosition), (currentFrame->GetYOffset() + currentProcessPixel->yPosition), currentMagickPixel);
      }

    }

    //If not stitched it's time to write the current frame to a file
    if(!singleStitchedImage)
    {
      fileOutPath << std::setw(3) << std::setfill('0') << currentProcessingFrame << outFilePath;
      convertedImage->write(fileOutPath.str());
      fileOutPath.str(std::string());
      convertedImage->erase();
    }
    //Otherwise continue writing down the row
    else
    {
      currentImageDestinationRow++;
    }

  }
  //Now that all the pixels are in place, lets write the result to disk
  if(singleStitchedImage)
  {
    convertedImage->write(outFilePath);
  }


  //Clean up our pointers from earlier.
  delete convertedImage;
  convertedImage = NULL;

}
#else
void GRPImage::SaveConvertedImage(std::string outFilePath, int startingFrame, int endingFrame, bool singleStitchedImage, int imagesPerRow)
{
  GRPImageImageMagickNotCompiledIn compiledError;
  compiledError.SetErrorMessage("Imagemagick was not compiled into libgrp, method unavailable");
  throw compiledError;
}

#endif /* HAVE_IMAGEMAGICKPP */
void GRPImage::CleanGRPImage()
{
  if(mImageFrames.size() != 0)
  {
    for(std::vector<GRPFrame *>::iterator currentDeleteFrame = mImageFrames.begin(); currentDeleteFrame != mImageFrames.end(); currentDeleteFrame++)
    {
      delete *currentDeleteFrame;
      *currentDeleteFrame = NULL;
    }
    mImageFrames.resize(0);
  }
}

