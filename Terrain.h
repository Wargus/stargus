/*
 * Terrain.h
 *
 *      Author: Andreas Volz
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

class Terrain
{
public:
	Terrain();
	virtual ~Terrain();

	/**
	 * Not sure, but it seems this function generates some Gimp palette.
	 * Maybe there is an external Gimp workflow...
	 */
	bool ConvertRgb(const char *mpqfile, const char *arcfile, const char *file);

	bool ConvertTileset(const char *mpqfile, const char* arcfile, const char* file);

private:
	unsigned char* ConvertPaletteRGBXtoRGB(unsigned char* pal);
	unsigned char* ConvertTile(unsigned char* mini, const char* mega, int msize,
			const char* map __attribute__((unused)),	int mapl __attribute__((unused)), int *wp, int *hp);
	void DecodeMiniTile(unsigned char* image, int ix, int iy, int iadd,
		unsigned char* mini, int index, int flipx, int flipy);
};

#endif /* TERRAIN_H_ */
