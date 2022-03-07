/*
 * Pcx.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "endian.h"
#include "Pcx.h"
#include "Preferences.h"
#include "Storm.h"
#include "Png.h"
#include "Hurricane.h"

// System
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

Pcx::Pcx(std::shared_ptr<Hurricane> hurricane) :
	Converter(hurricane),
	mLogger("startool.Pcx"),
	rawImage(0),
	mImageParserPos(nullptr),
	mWidth(0),
	mHeight(0)
{
}

Pcx::Pcx(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
	Converter(hurricane),
	mLogger("startool.Pcx"),
	rawImage(0),
	mImageParserPos(nullptr),
	mWidth(0),
	mHeight(0)
{
	load(arcfile);
}

Pcx::~Pcx()
{
	free(rawImage);
}

bool Pcx::load(const std::string &arcfile)
{
	bool result = true;

	mRawData = mHurricane->extractDataChunk(arcfile);
	if (mRawData)
	{
		free(rawImage);
		extractHeader();
		extractImage();
		extractPalette();
	}
	else
	{
		result = false;
	}

	return result;
}

bool Pcx::savePNG(const std::string &filename)
{
	bool result = true;
	char buf[8192] = {'\0'};

	if (mRawData)
	{
		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s", preferences.getDestDir().c_str(), GRAPHICS_PATH, filename.c_str());
		Png::save(buf, rawImage, mWidth, mHeight, mPalette->getDataChunk()->getDataPointer(), 0);
	}
	else
	{
		result = false;
	}

	return result;
}

std::shared_ptr<Palette> Pcx::getPalette()
{
	return mPalette;
}

void Pcx::extractHeader()
{
	if(mRawData)
	{
		memcpy(&pcxh, mRawData->getDataPointer(), sizeof(struct PCXheader));
		pcxh.Xmin = ConvertLE16(pcxh.Xmin);
		pcxh.Ymin = ConvertLE16(pcxh.Ymin);
		pcxh.Xmax = ConvertLE16(pcxh.Xmax);
		pcxh.Ymax = ConvertLE16(pcxh.Ymax);
		pcxh.BytesPerLine = ConvertLE16(pcxh.BytesPerLine);

		mWidth = pcxh.Xmax - pcxh.Xmin + 1;
		mHeight = pcxh.Ymax - pcxh.Ymin + 1;
	}
}

void Pcx::extractImage()
{
	int y;
	int count;
	unsigned char *dest = NULL;
	unsigned char ch = 0;

	rawImage = (unsigned char*) malloc(mWidth * mHeight);
	mImageParserPos = mRawData->getDataPointer() + sizeof(struct PCXheader);

	for (y = 0; y < mHeight; ++y)
	{
		count = 0;
		dest = rawImage + y * mWidth;
		for (int i = 0; i < mWidth; ++i)
		{
			if (!count)
			{
				ch = *mImageParserPos++;
				if ((ch & 0xc0) == 0xc0)
				{
					count = ch & 0x3f;
					ch = *mImageParserPos++;
				}
				else
				{
					count = 1;
				}
			}
			dest[i] = ch;
			--count;
		}
	}
}

void Pcx::extractPalette()
{
	unsigned char *dest = NULL;
	unsigned char ch = 0;
	int rgb_size = 256 * 3;
	unsigned char *pal = NULL;

	if(mRawData)
	{
		// allocate enough space for RGB information
		pal = (unsigned char*) malloc(rgb_size);
		dest = pal;
		do
		{
			ch = *mImageParserPos++;
		} while (ch != 0x0c); // search the 'magic ID' that shows the start of RGB information next

		// copy RGB information to destination
		for (int i = 0; i < rgb_size; ++i)
		{
			*dest++ = *mImageParserPos++;

		}

		std::shared_ptr<DataChunk> data = make_shared<DataChunk>(&pal, rgb_size);
		mPalette = make_shared<Palette>(data);
	}
}



