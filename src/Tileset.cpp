/*
 * Terrain.cpp
 *
 *      Author: Aandreas
 */

// Local
#include "Tileset.h"
#include "endian.h"
#include "Storm.h"
#include "FileUtil.h"
#include "Png.h"
#include "Preferences.h"
#include <Hurricane.h>

// System
#include <stdlib.h>

// activate local debug messages
//#define DEBUG 1

//#define MAKE_CCL

/**
 **		How much tiles are stored in a row.
 */
#define TILE_PER_ROW		16

/**
 **		Path to the tileset graphics. (default=$DIR/graphics/tilesets)
 */
#define TILESET_PATH		"graphics/tilesets"

// Function Prototypes
int CountUsedTiles(const unsigned char *map, const unsigned char *mega,
    int *map2tile, int mapl);
void SaveCCL(const std::string &file,
    const unsigned char *map __attribute__((unused)), const int *map2tile,
    int mapl);

using namespace std;

/**
 **		Destination directory of the data
 */

Tileset::Tileset(std::shared_ptr<Hurricane> hurricane) :
    mHurricane(hurricane)
{

}

Tileset::~Tileset()
{

}

/**
 **		Convert rgbx to rgb
 */
unsigned char* Tileset::ConvertPaletteRGBXtoRGB(unsigned char *pal)
{
  int i;
  int j;

  for (i = 0; i < 256; ++i)
  {
    for (j = 0; j < 3; ++j)
    {
      pal[i * 3 + j] = pal[i * 4 + j];
    }
  }

  return pal;
}

/**
 **  Convert rgb to my format.
 */
bool Tileset::ConvertRgb(const std::string &arcfile, const std::string &file)
{
  char buf[8192] =
  { '\0' };
  FILE *f;
  int i;

  bool result = true;
  Preferences &preferences = Preferences::getInstance();

  sprintf(buf, "%s.wpe", arcfile.c_str());

  shared_ptr<DataChunk> data = mHurricane->extractDataChunk(buf);
  unsigned char *palp = data->getDataPointer();
  if (data)
  {

    // Hint: ConvertPaletteRGBXtoRGB() changes the data content direct!
    ConvertPaletteRGBXtoRGB(palp);

    //
    //  Generate RGB File.
    //
    sprintf(buf, "%s/%s/%s.rgb", preferences.getDestDir().c_str(), TILESET_PATH,
        file.c_str());
    CheckPath(buf);
    f = fopen(buf, "wb");
    if (!f)
    {
      perror("");
      printf("Can't open %s\n", buf);
      // TODO: more flexible error handling than calling GUI dialog from conversation routine needed
      //error("Memory error", "Could not allocate enough memory to read archive.");
    }
    if (fwrite(palp, 1, 256 * 3, f) != 256 * 3)
    {
      printf("Can't write %d bytes\n", 256 * 3);
      fflush(stdout);
    }

    fclose(f);

    //
    //  Generate GIMP palette
    //
    sprintf(buf, "%s/%s/%s.gimp", preferences.getDestDir().c_str(),
        TILESET_PATH, file.c_str());
    CheckPath(buf);
    f = fopen(buf, "wb");
    if (!f)
    {
      perror("");
      printf("Can't open %s\n", buf);
      // TODO: more flexible error handling than calling GUI dialog from conversation routine needed
      //error("Memory error", "Could not allocate enough memory to read archive.");
    }
    // TODO: check that correct string is printed with C++
    //fprintf(f, "GIMP Palette\n# Stratagus %c%s -- GIMP Palette file\n",
    //toupper(*file), file + 1);

    for (i = 0; i < 256; ++i)
    {
      // FIXME: insert nice names!
      fprintf(f, "%d %d %d\t#%d\n", palp[i * 3], palp[i * 3 + 1],
          palp[i * 3 + 2], i);
    }

    fclose(f);
  }
  else
  {
    result = false;
  }

  return result;
}

/**
 **  Decode a minitile into the image.
 */
void Tileset::DecodeMiniTile(unsigned char *image, int ix, int iy, int iadd,
    unsigned char *mini, int index, int flipx, int flipy)
{
  for (int y = 0; y < 8; ++y)
  {
    for (int x = 0; x < 8; ++x)
    {
      image[(y + iy * 8) * iadd + ix * 8 + x] = mini[index
          + (flipy ? (7 - y) : y) * 8 + (flipx ? (7 - x) : x)];
    }
  }
}

/**
 **  Convert tiles into image.
 */
unsigned char* Tileset::ConvertTile(const std::string &arcfile,
    unsigned char *mini, unsigned char *mega, int msize,
    unsigned char *map __attribute__((unused)),
    int mapl __attribute__((unused)), int *wp, int *hp)

{
  unsigned char *image;
  const unsigned short *mp;
  int height;
  int width;
  int i;
  int x;
  int y;
  int offset;
  int numtiles;
#ifdef MAKE_CCL
	int *map2tile;

	map2tile = (int *)malloc(mapl / 52 * 16 * sizeof(int));
	CountUsedTiles((unsigned char *)map, (unsigned char *)mega, map2tile, mapl);
#endif
  numtiles = msize / 32;

  width = TILE_PER_ROW * 32;
  height = ((numtiles + TILE_PER_ROW - 1) / TILE_PER_ROW) * 32;
  image = (unsigned char*) calloc(1, height * width);

  for (i = 0; i < numtiles; ++i)
  {
    //mp = (const unsigned short *)(mega + img2tile[i] * 32);
    mp = (const unsigned short*) (mega + i * 32);
    for (y = 0; y < 4; ++y)
    {
      for (x = 0; x < 4; ++x)
      {
        offset = ConvertLE16(mp[x + y * 4]);
        DecodeMiniTile(image, x + ((i % TILE_PER_ROW) * 4),
            y + (i / TILE_PER_ROW) * 4, width, mini, (offset / 2) * 64,
            offset & 1, 0);
      }
    }
  }

  *wp = width;
  *hp = height;
#ifdef MAKE_CCL
	SaveCCL(arcfile, (unsigned char *)map, map2tile, mapl);
	free(map2tile);
#endif
  return image;
}

/**
 **  Convert a tileset to my format.
 */
bool Tileset::ConvertTileset(const std::string &arcfile,
    const std::string &file)
{
  shared_ptr<DataChunk> palp;
  shared_ptr<DataChunk> megp;
  shared_ptr<DataChunk> minp;
  shared_ptr<DataChunk> mapp;
  shared_ptr<DataChunk> flagp;
  unsigned char *image;
  int w;
  int h;
  int megl;
  int mapl;
  char buf[8192] =
  { '\0' };
  bool ret = true;

  // TODO: this seems to be a special fix for one tileset 'installation'. Need to understand this...
  if (!strcmp(arcfile.c_str(), "tileset\\Install"))
  {
    sprintf(buf, "tileset\\install.wpe");
    palp = mHurricane->extractDataChunk(buf);

    sprintf(buf, "tileset\\install.vr4");
    minp = mHurricane->extractDataChunk(buf);
  }
  else
  {
    sprintf(buf, "%s.wpe", arcfile.c_str());
    palp = mHurricane->extractDataChunk(buf);
    sprintf(buf, "%s.vr4", arcfile.c_str());
    minp = mHurricane->extractDataChunk(buf);
  }
  sprintf(buf, "%s.vx4", arcfile.c_str());

  megp = mHurricane->extractDataChunk(buf);
  megl = megp->getSize();
  sprintf(buf, "%s.cv5", arcfile.c_str());

  mapp = mHurricane->extractDataChunk(buf);
  mapl = mapp->getSize();

  sprintf(buf, "%s.vf4", arcfile.c_str());
  flagp = mHurricane->extractDataChunk(buf);

  // TODO: give DataChunk to this function and wrap image class
  image = ConvertTile(file, minp->getDataPointer(), megp->getDataPointer(),
      megl, mapp->getDataPointer(), mapl, &w, &h);

#ifdef DEBUG
	int flagl = EntrySize;
	sprintf(buf, "%s/%s-flags.txt", DestDir, strstr(arcfile, "\\") + 1);
	FILE *fd = fopen(buf, "w");
	int i, j, tiles, start = -1;
	for (i = 0; i < flagl / 32; ++i) {
		unsigned short *s = (unsigned short *)(flagp + 32 * i);
		tiles = 0;
		for (j = 0; j < 16; ++j) {
			if (s[j] == 0) {
				++tiles;
			}
		}
		if (tiles >= 2) {
			if (start == -1) {
				start = i;
			}
			fprintf(fd, "tile %d is unpassable\n", i);
		}
		if (i == flagl / 32 - 1 || tiles < 2) {
			if (i == flagl / 32 - 1) ++i;
			if (start != -1) {
				if (start != i - 1) {
					fprintf(fd, "tile %d-%d unpassable\n", start, i - 1);
				} else {
					fprintf(fd, "tile %d unpassable\n", start);
				}
				start = -1;
			}
		}
	}
	fclose(fd);
#endif

  ConvertPaletteRGBXtoRGB(palp->getDataPointer()); // write to memory pointer!
  Preferences &preferences = Preferences::getInstance();
  sprintf(buf, "%s/%s/%s.png", preferences.getDestDir().c_str(), TILESET_PATH,
      file.c_str());
  printf("tileset png: %s\n", buf);
  Png::save(buf, image, w, h, palp->getDataPointer(), 0);

  // freeing the image is still needed as this isn't wrapped in a smart pointer
  free(image);

  return ret;
}

// TODO: is this needed or working??

#ifdef MAKE_CCL
void SaveCCL(const std::string &file, const unsigned char *map __attribute__((unused)),
	const int *map2tile, int mapl)
{
	int i;
	FILE *f;
	static int savecount = 0;
	char buf[1024];

	sprintf(buf, "save%02d.ccl", savecount++);
	f = fopen(buf, "w");

	fprintf(f, "DefineTileset(\n");
	fprintf(f, "  \"name\", \"\",\n");
	fprintf(f, "  \"image\", \"tilesets/%s.png\",\n", file.c_str());
	fprintf(f, "  \"slots\", {\n");

	fprintf(f,"   \"solid\", { \"light-grass\", \"land\", {\n");
	for (i = 0; i < mapl / 52 * 16; ++i) {
		if (i & 15) {
			fprintf(f, " ");
		} else if (i) {
			fprintf(f, "\t-- %03X\n",i - 16);
		}
		fprintf(f, "%4d,", map2tile[i]);
	}

	fprintf(f, "\n}}})\n");

	fclose(f);
}

/**
**  Count used mega tiles for map.
*/
int CountUsedTiles(const unsigned char* map, const unsigned char* mega,
	int* map2tile, int mapl)
{
	int i;
	int j;
	int used;
	const unsigned char* tp;
	int *img2tile;

	img2tile = (int *)malloc(mapl / 52 * 16 * sizeof(int));

	memset(map2tile, 0, sizeof(map2tile));

	//
	//  Build conversion table.
	//
	for (i = 0; i < mapl / 52; ++i) {
		tp = map + i * 52 + 20;
		for (j = 0; j< 0x10; ++j ) {
			if (((i << 4) | j) > mapl) {
				break;
			}
			map2tile[(i << 4) | j] = AccessLE16(tp + j * 2);
		}
//		printf("\n");
	}

	//
	//  Mark all used mega tiles.
	//
	used = 0;
	for (i = 0; i < mapl / 52 * 16; ++i) {
		if (!map2tile[i]) {
			continue;
		}
		for (j = 0; j < used; ++j) {
			if (img2tile[j] == map2tile[i]) {
				break;
			}
		}
		if (j == used) {
			//
			//  Check unique mega tiles.
			//
			for (j = 0; j < used; ++j) {
				if (!memcmp(mega + img2tile[j] * 32, mega + map2tile[i] * 32, 32)) {
					break;
				}
			}
			if (j == used) {
				img2tile[used++] = map2tile[i];
			}
		}
	}
//	printf("Used mega tiles %d\n", used);
#if 0
	for (i = 0; i < used; ++i) {
		if (!(i % 16)) {
			printf("\n");
		}
		printf("%3d ",img2tile[i]);
	}
	printf("\n");
#endif

	return used;
}
#endif

