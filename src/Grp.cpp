/*
 * Grp.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Grp.h"
#include "endian.h"
#include "Png.h"
#include "FileUtil.h"
#include "Storm.h"
#include "Preferences.h"

// System
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

Grp::Grp(std::shared_ptr<Hurricane> hurricane) :
	Converter(hurricane),
	mLogger("startool.Grp")
{
}

Grp::Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
	Converter(hurricane),
	mLogger("startool.Grp")
{
	load(arcfile);
}

Grp::Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile, std::shared_ptr<Palette> pal) :
	Converter(hurricane),
	mLogger("startool.Grp"),
	mPal(pal)
{
	load(arcfile);
}

Grp::Grp(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile, const std::string &palFile) :
		Converter(hurricane),
		mLogger("startool.Grp"),
		mPalFile(palFile)
{
	load(arcfile);
}

std::shared_ptr<kaitai::kstream> Grp::getKaitaiStream(const std::string &file)
{
	std::shared_ptr<DataChunk> data = mHurricane->extractDataChunk(file);
	if (data)
	{
		//std::ifstream ifs(arcfile, std::ifstream::binary);
		//kaitai::kstream ks(&ifs);

		// TODO: for now just create from complete string instead of istream. Maybe change the complete
		// reader to stream based concept...
		std::string str( reinterpret_cast<char const*>(data->getDataPointer()), data->getSize() ) ;
		std::shared_ptr<kaitai::kstream> ks = make_shared<kaitai::kstream>(str);
		return ks;
	}

	// TODO: hm, better create an exception
	return nullptr;
}

void Grp::setPalette(std::shared_ptr<Palette> pal)
{
	mPal = pal;
	mPalFile.clear();
}

void Grp::setPalette(const std::string &palFile)
{
	mPalFile = palFile;
	mPal = nullptr;
}

bool Grp::load(const std::string &arcfile)
{
	mArcfile = arcfile;

	mGrp_ks = getKaitaiStream(mArcfile);

	std::shared_ptr<grp_file_t> grp_loc(new grp_file_t(mGrp_ks.get()));
	mGrp_ko = grp_loc;

	return true;
}

bool Grp::save(const std::string &filename)
{
	std::vector<grp_file_t::image_frame_type_t*>* frames_vec = mGrp_ko->image_frames();

	for(unsigned int i = 0; i < frames_vec->size(); i++)
	{
		grp_file_t::image_frame_type_t *frame =  frames_vec->at(i);

		std::vector<grp_file_t::line_offset_type_t*>* line_offset_vec = frame->line_offsets();

		for(unsigned int n = 0; n < line_offset_vec->size(); n++)
		{
			grp_file_t::line_offset_type_t* line_offset = line_offset_vec->at(n);

			u_int16_t offset = line_offset->offset();
			//cout << "offset: " << offset << endl;

			const string &rle_offset = line_offset->rle_offsets();

			for(const char& c : rle_offset)
			{
				printf("%d ", (unsigned char)c);
			}

			cout << endl;
		}
	}

	return true;
}
#if 0
	bool result = true;
	char buf[8192] = {'\0'};

	std::shared_ptr<DataChunk> rawData = mHurricane->extractDataChunk(mArcfile);
	if (rawData)
	{
		vector<char> img_vec = rawData->getCharVector();

		//GRPImage myGRPImage(&img_vec, false);

		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s", preferences.getDestDir().c_str(), GRAPHICS_PATH, filename.c_str());
		CheckPath(buf);

		if(mPal)
		{
			/*ColorPalette myGRPPallete;

			std::shared_ptr<DataChunk> rawPal = mPal->getDataChunk();

			std::vector<char> pal_vec = mPal->getDataChunk()->getCharVector();
			myGRPPallete.LoadPalette(&pal_vec);

			myGRPImage.SetColorPalette(&myGRPPallete);*/

			//myGRPImage.SaveConvertedImage(buf, 0, myGRPImage.getNumberOfFrames(), true, 17);

			unsigned char *img = nullptr;
			int image_width = 0;
			int image_height = 0;
			//myGRPImage.GetConvertedImage(&img, &image_width, &image_height, 0, myGRPImage.getNumberOfFrames(), true, 17);

			sprintf(buf, "%s/%s/%s", preferences.getDestDir().c_str(), GRAPHICS_PATH, filename.c_str());
			//Png::save(buf, img, image_width, image_height, mPal->getDataChunk()->getDataPointer(), 0);

			//printf("w:%d, h:%d\n", myGRPImage.getMaxImageWidth(), myGRPImage.getMaxImageHeight());

		}
		else if(!mPalFile.empty())
		{
			/*ColorPalette myGRPPallete;

			myGRPPallete.LoadPalette(mPalFile);

			myGRPImage.SetColorPalette(&myGRPPallete);*/

			//myGRPImage.SaveConvertedImage(buf, 0, myGRPImage.getNumberOfFrames(), true, 17);
		}
		else
		{
			//myGRPImage.SaveConvertedImage(buf, 0, myGRPImage.getNumberOfFrames(), true, 17);
		}



	}
	else
	{
		result = false;
	}

	return result;
}
#endif
Grp::~Grp()
{

}


void Grp::DecodeGfuEntry(int index, unsigned char* start,
	unsigned char* image, int ix, int iy, int iadd)
{
	unsigned char* bp;
	unsigned char* sp;
	unsigned char* dp;
	int i;
	int xoff;
	int yoff;
	int width;
	int height;
	int offset;

	bp = start + index * 8;
	xoff = FetchByte(bp);
	yoff = FetchByte(bp);
	width = FetchByte(bp);
	height = FetchByte(bp);
	offset = FetchLE32(bp);
	// High bit of width
	if (offset < 0) {
		offset &= 0x7FFFFFFF;
		width += 256;
	}

//	printf("%2d: +x %2d +y %2d width %2d height %2d offset %d\n",
//		index, xoff, yoff, width, height, offset);

	sp = start + offset - 6;
	dp = image + xoff - ix + (yoff - iy) * iadd;
	for (i = 0; i < height; ++i) {
		memcpy(dp, sp, width);
		dp += iadd;
		sp += width;
	}
}


void Grp::DecodeGfxEntry(int index, unsigned char* start,
	unsigned char* image, int ix, int iy, int iadd)
{
	unsigned char* bp;
	unsigned char* sp;
	unsigned char* dp;
	int xoff;
	int yoff;
	int width;
	int height;
	int offset;
	unsigned char* rows;
	int h;
	int w;
	int ctrl;

	bp = start + index * 8;
	xoff = FetchByte(bp);
	yoff = FetchByte(bp);
	width = FetchByte(bp);
	height = FetchByte(bp);
	offset = FetchLE32(bp);

//	printf("%2d: +x %2d +y %2d width %2d height %2d offset %d\n",
//		index, xoff, yoff, width, height, offset);

	rows = start + offset - 6;
	dp = image + xoff - ix + (yoff - iy) * iadd;

	for (h = 0; h < height; ++h) {
//		printf("%2d: row-offset %2d\t", index, AccessLE16(rows + h * 2));
		sp = rows + AccessLE16(rows + h * 2);
		for (w = 0; w < width; ) {
			ctrl = *sp++;
//			printf("%02X", ctrl);
			if (ctrl & 0x80) {  // transparent
				ctrl &= 0x7F;
//				printf("-%d,", ctrl);
				memset(dp+h*iadd+w,255,ctrl);
				w+=ctrl;
			} else if (ctrl & 0x40) {  // repeat
				ctrl &= 0x3F;
//				printf("*%d,", ctrl);
				memset(dp + h * iadd + w, *sp++, ctrl);
				w += ctrl;
			} else {						// set pixels
				ctrl &= 0x3F;
//				printf("=%d,", ctrl);
				memcpy(dp + h * iadd + w, sp, ctrl);
				sp += ctrl;
				w += ctrl;
			}
		}
		//dp[h * iadd + width - 1] = 0;
//		printf("\n");
	}
}



void Grp::ConvertPal3(unsigned char* image, int w, int h)
{
	int i;

	// FIXME: this isn't correct, there should be partial transparency
	for (i = 0; i < w * h; ++i) {
		if (image[i] < 16 || image[i] > 62) {
			image[i] = 255;
		}
	}
}

unsigned char* Grp::ConvertGraphic(int gfx, unsigned char* bp, int *wp, int *hp,
	unsigned char* bp2, int start2)
{
	int i;
	int count;
	int length;
	int max_width;
	int max_height;
	int minx;
	int miny;
	int best_width;
	int best_height;
	unsigned char* image;
	int IPR;

	int endereco;

	// Init pointer to 2nd animation
	if (bp2) {
		count = FetchLE16(bp2);
		max_width = FetchLE16(bp2);
		max_height = FetchLE16(bp2);
	}
	count = FetchLE16(bp);
	max_width = FetchLE16(bp);
	max_height = FetchLE16(bp);


//	printf("Entries %2d Max width %3d height %3d, ", count,
//		max_width, max_height);

	// Find best image size
	minx = 999;
	miny = 999;
	best_width = 0;
	best_height = 0;
	for (i = 0; i < count; ++i) {
		unsigned char* p;
		int xoff;
		int yoff;
		int width;
		int height;

		p = bp + i * 8;
		xoff = FetchByte(p);
		yoff = FetchByte(p);
		width = FetchByte(p);
		height = FetchByte(p);
		endereco = FetchLE32(p);
		if( endereco&0x80000000 ) {		// high bit of width
			width += 256;
		}
		if( xoff<minx ) minx=xoff;
		if( yoff<miny ) miny=yoff;
		if( xoff+width>best_width ) best_width=xoff+width;
		if( yoff+height>best_height ) best_height=yoff+height;
	}
	// FIXME: the image isn't centered!!

#if 0
	// Taken out, must be rewritten.
	if (max_width - best_width < minx) {
		minx = max_width - best_width;
		best_width -= minx;
	} else {
		best_width = max_width - minx;
	}
	if (max_height - best_height < miny) {
		miny = max_height - best_height;
		best_height -= miny;
	} else {
		best_height = max_width - miny;
	}

	//best_width -= minx;
	//best_height -= miny;
#endif

//	printf("Best image size %3d, %3d\n", best_width, best_height);

	minx = 0;
	miny = 0;

	if (gfx) {
		best_width = max_width;
		best_height = max_height;
		IPR = 17;  // st*rcr*ft 17!
		if (count < IPR) {  // images per row !!
			IPR = 1;
			length = count;
		} else {
			length = ((count + IPR - 1) / IPR) * IPR;
		}
	} else {
		max_width = best_width;
		max_height = best_height;
		IPR = 1;
		length = count;
	}

	image = (unsigned char *)malloc(best_width * best_height * length);

	//  Image: 0, 1, 2, 3, 4,
	//         5, 6, 7, 8, 9, ...
	if (!image) {
		printf("Can't allocate image\n");
		// TODO: more flexible error handling than calling GUI dialog from conversation routine needed
		//error("Memory error", "Could not allocate enough memory to read archive.");
	}
	// Set all to transparent.
	memset(image, 255, best_width * best_height * length);

	if (gfx) {
		for (i = 0; i < count; ++i) {
			// Hardcoded support for worker with resource repairing
			if (i >= start2 && bp2) {
				DecodeGfxEntry(i, bp2,
					image + best_width * (i % IPR) + best_height * best_width * IPR * (i / IPR),
					minx, miny, best_width * IPR);
			} else {
				DecodeGfxEntry(i, bp,
					image + best_width * (i % IPR) + best_height * best_width * IPR * (i / IPR),
					minx, miny, best_width * IPR);
			}
		}
	} else {
		for (i = 0; i < count; ++i) {
			DecodeGfuEntry(i, bp,
				image + best_width * (i % IPR) + best_height * best_width * IPR * (i / IPR),
				minx, miny, best_width * IPR);
		}
	}

	*wp = best_width * IPR;
	*hp = best_height * (length / IPR);

	return image;
}
