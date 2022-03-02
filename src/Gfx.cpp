/*
 * Gfx.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include <Palette.h>
#include "Gfx.h"
#include "endian.h"
#include "Preferences.h"
#include "Png.h"
#include "Storm.h"

// System
#include <cstring>


Gfx::Gfx(std::shared_ptr<Hurricane> hurricane) :
	Converter(hurricane)
{

}

Gfx::~Gfx()
{

}
bool Gfx::convert(const std::string &arcfile, const std::string &file)
{
	return convert(arcfile, file, 0);
}

bool Gfx::convert(const std::string &arcfile, const std::string &file, int pale)
{
	unsigned char* palp = NULL;
	unsigned char* gfxp = NULL;
	unsigned char* gfxp2 = NULL;
	unsigned char* image = NULL;
	int w;
	int h;
	char buf[1024];
	bool result = true;

	result = mHurricane->extractMemory(arcfile, &gfxp, NULL);
	if (result)
	{

		image = ConvertGraphic(1, gfxp, &w, &h, gfxp2, 0);

		palp = Palettes[pale];

		free(gfxp);

		if (pale == 3) {
			ConvertPal3(image, w, h);
		}
		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), GRAPHICS_PATH, file.c_str());
		Png::save(buf, image, w, h, palp, 255);

		free(image);
	}
	else
	{
		result = false;
	}

	return result;
}
