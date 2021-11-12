/*
 * Gfx.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Gfx.h"
#include "endian.h"
#include "Preferences.h"
#include "Palettes.h"
#include "Png.h"
#include "Storm.h"

// System
#include <cstring>


Gfx::Gfx()
{
	// TODO Auto-generated constructor stub

}

Gfx::~Gfx()
{
	// TODO Auto-generated destructor stub
}

bool Gfx::convert(const char *mpqfile, const char* arcfile, const char* file, int pale)
{
	unsigned char* palp = NULL;
	unsigned char* gfxp = NULL;
	unsigned char* gfxp2 = NULL;
	unsigned char* image = NULL;
	int w;
	int h;
	char buf[1024];
	bool result = true;

	Storm mpq(mpqfile);
	result = mpq.extractMemory(arcfile, &gfxp, NULL);
	if (result)
	{

		image = ConvertGraphic(1, gfxp, &w, &h, gfxp2, 0);

		palp = Palettes[pale];

		free(gfxp);

		if (pale == 3) {
			ConvertPal3(image, w, h);
		}
		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), GRAPHICS_PATH, file);
		Png::save(buf, image, w, h, palp, 255);

		free(image);
	}
	else
	{
		result = false;
	}

	return result;
}



