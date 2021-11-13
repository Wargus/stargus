/*
 * Gfu.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Gfu.h"
#include "endian.h"
#include "Storm.h"
#include "Preferences.h"
#include "Palettes.h"
#include "Png.h"

// System
#include <cstring>

Gfu::Gfu()
{
	// TODO Auto-generated constructor stub

}

Gfu::~Gfu()
{
	// TODO Auto-generated destructor stub
}


bool Gfu::convert(const char *mpqfile, const char* arcfile, const char* file, int pale)
{
	unsigned char* palp = NULL;
	unsigned char* gfup = NULL;
	unsigned char* gfup2 = NULL;
	unsigned char* image = NULL;
	int w;
	int h;
	char buf[8192] = {'\0'};
	unsigned char* p;
	unsigned char* end;
	bool result = true;

	Storm mpq(mpqfile);
	result = mpq.extractMemory(arcfile, &gfup, NULL);
	if (result)
	{
		image = ConvertGraphic(0, gfup, &w, &h, gfup2, 0);

		// 0 and 255 are transparent
		p = image;
		end = image + w * h;
		while (p < end) {
			if (!*p) {
				*p = 0xFF;
			}
			++p;
		}

		printf("Palette: %d", pale);
		palp = Palettes[pale];


		Preferences &preferences = Preferences::getInstance ();
		sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), GRAPHICS_PATH, file);

		Png::save(buf, image, w, h, palp, 255);

		free(image);
	}
	else
	{
		result = false;
	}
	free(gfup);

	return result;
}


