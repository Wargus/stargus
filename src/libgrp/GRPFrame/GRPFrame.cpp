#include "GRPFrame.hpp"
GRPFrame::GRPFrame()
{
  xOffset = 0;
  yOffset = 0;
  width = 0;
  height = 0;
}

void GRPFrame::SetImageSize(const uint8_t &inputFrameWidth, const uint8_t &inputFrameHeight)
{
  if(inputFrameWidth <= 0 || inputFrameHeight <= 0)
  {
    GRPFrameInvalidFrameDemensions badDemensions;
    badDemensions.SetErrorMessage("Invalid Frame width");
    throw badDemensions;
  }
  width = inputFrameWidth;
  height = inputFrameHeight;
}

uint8_t GRPFrame::GetImageWidth()
{
  return width;
}
uint8_t GRPFrame::GetImageHeight()
{
  return height;
}

void GRPFrame::SetImageOffsets(const uint8_t &inputXOffset, const uint8_t &inputYOffset)
{
  xOffset = inputXOffset;
  yOffset = inputYOffset;
}
uint8_t GRPFrame::GetXOffset()
{
  return xOffset;
}
uint8_t GRPFrame::GetYOffset()
{
  return yOffset;
}
void GRPFrame::SetDataOffset(const uint32_t &inputDataOffset)
{
  dataOffset = inputDataOffset;
}
uint32_t GRPFrame::GetDataOffset()
{
  return dataOffset;
}