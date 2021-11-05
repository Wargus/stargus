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
};

bool ConvertRgb(const char *mpqfile, const char *arcfile, const char *file);
//unsigned char* ConvertTile(unsigned char* mini, const char* mega, int msize,
	//const char* map __attribute__((unused)),	int mapl __attribute__((unused)), int *wp, int *hp);
bool ConvertTileset(const char *mpqfile, const char* arcfile, const char* file);

#endif /* TERRAIN_H_ */
