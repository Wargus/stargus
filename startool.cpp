//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//   Utility for Stratagus - A free fantasy real time strategy game engine
//
/**@name startool.c - Extract files from star archives. */
//
//      (c) Copyright 2002-2012 by Jimmy Salmon and Pali Rohár
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; version 2 dated June, 1991.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//      02111-1307, USA.
//

//@{

/*----------------------------------------------------------------------------
--  Includes
----------------------------------------------------------------------------*/

#include "endian.h"
#include "startool.h"
#include <stratagus-gameutils.h>

//----------------------------------------------------------------------------

/**
**  Palette N27, for credits cursor
*/
static unsigned char* Pal27;

/**
**  Original archive buffer.
*/
static unsigned char* ArchiveBuffer;

/**
**  Offsets for each entry into original archive buffer.
*/
static unsigned char** ArchiveOffsets;

/**
**  Fake empty entry
*/
static unsigned int EmptyEntry[] = { 1, 1, 1 };

static char* ArchiveDir;

/**
**  What CD Type is it?
*/
static int CDType;

// Width of game font
static int game_font_width;

/**
**  File names.
*/
static char* UnitNames[110];
static int UnitNamesLast = 0;

//----------------------------------------------------------------------------
//  TOOLS
//----------------------------------------------------------------------------



/**
**  Check if path exists - DOESN'T create any directories/files
*/
bool FileExists(const char *filename)
{
    struct stat buffer;
    return stat(filename, &buffer) == 0 ? true : false;
}

//----------------------------------------------------------------------------
//  PNG
//----------------------------------------------------------------------------

/**
**  Save a png file.
**
**  @param name         File name
**  @param image        Graphic data
**  @param w            Graphic width
**  @param h            Graphic height
**  @param pal          Palette
**  @param transparent  Image uses transparency
*/
int SavePNG(const char* name, unsigned char* image, int w,
	int h, unsigned char* pal, int transparent)
{
	FILE* fp;
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned char** lines;
	int i;

	if (!(fp = fopen(name, "wb"))) {
		printf("%s:", name);
		perror("Can't open file");
		fflush(stdout); fflush(stderr);
		return 1;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fclose(fp);
		return 1;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(fp);
		return 1;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		// FIXME: must free buffers!!
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}
	png_init_io(png_ptr, fp);

	// zlib parameters
	png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

	// prepare the file information
	png_set_IHDR(png_ptr, info_ptr, w, h, 8, PNG_COLOR_TYPE_PALETTE, 0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
	png_set_invalid(png_ptr, info_ptr, PNG_INFO_PLTE);
	png_set_PLTE(png_ptr, info_ptr, (png_colorp) pal, 256);

	if (transparent != -1) {
		png_byte trans[256];

		memset(trans, 0xFF, sizeof(trans));
		trans[transparent] = 0x0;
		png_set_tRNS(png_ptr, info_ptr, trans, 256, 0);
	}

	// write the file header information
	png_write_info(png_ptr, info_ptr);

	// set transformation

	// prepare image
	lines = (unsigned char **)malloc(h * sizeof(*lines));
	if (!lines) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}

	for (i = 0; i < h; ++i) {
		lines[i] = image + i * w;
	}

	png_write_image(png_ptr, lines);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	free(lines);

	return 0;
}

//----------------------------------------------------------------------------
//  Archive
//----------------------------------------------------------------------------

/**
**  Open the archive file.
**
**  @param file  Archive file name
**  @param type  Archive type requested
*/
/*int OpenArchive(const char *file)
{
	//
	//  Open the archive file
	//
	MpqFD = fopen(file, "rb");
	if (!MpqFD) {
		printf("Can't open %s\n", file);
		return -1;
	}

	if (Mpq->ReadInfo(MpqFD, mpq_listfile)) {
		printf("MpqReadInfo failed\n");
		fclose(MpqFD);
		MpqFD = NULL;
		return -1;
	}

	return 0;
}*/

/**
**  Extract/uncompress entry.
**
**  @param name  Name of the entry to extract
**
**  @return      Pointer to uncompressed entry
*/
/*unsigned char *ExtractEntry(const char *name)
{
	int i;
	unsigned char *buf;

	buf = NULL;
	for (i = 0; i < Mpq->FileCount; ++i) {
		// initially all lowercase
		char *lowername = strdup(name);
		for (unsigned int l = 0; l < strlen(lowername); l++) {
			lowername[l] = tolower(lowername[l]);
		}
		if (!strcmp(lowername, Mpq->FilenameTable + i * PATH_MAX)) {
			EntrySize = Mpq->BlockTable[i * 4 + 2];
			buf = (unsigned char *)malloc(EntrySize + 1);
			Mpq->ExtractTo(buf, i, MpqFD);
			printf("extracted: %s (%d, %d bytes)\n", name, i, EntrySize);
			break;
		}
	}
	if (i == Mpq->FileCount) {
		printf("Not found: %s\n", name);
		exit(-1);
	}

	return buf;
}*/

/**
**  Close the archive file.
*/
/*int CloseArchive(void)
{
	if (MpqFD) {
		fclose(MpqFD);
		MpqFD = NULL;
	}
	return 0;
}*/





//----------------------------------------------------------------------------
//		Map
//----------------------------------------------------------------------------

/**
**  Convert map
**
**  @extracted in case of installation the map files are yet extracted from mpq file
*/
bool ConvertMap(const char *mpqfile, const char *arcfile, const char *file, bool extracted)
{
	FILE *fd;
	char buf[1024];
	char buf2[1024];
	bool ret = true;

	ret = FileExists(mpqfile);

	if(ret) {

		sprintf(buf, "%s/%s", Dir, file);
		CheckPath(buf);

		if(!extracted)
		{
			// TODO: The .scm files could be deleted after conversation
			int error = ExtractMPQFile(mpqfile, arcfile, buf, false);
			if (error == ERROR_SUCCESS)
			{
				ConvertScm(buf);
			}
			else
			{
				ret = false;
			}

		}
		else // local installation filesystem case
		{
			sprintf(buf2, "%s/%s", ArchiveDir, file);
			CheckPath(buf2);

			//ConvertScm(buf2, buf, mpq_listfile);
		}

	}

	return ret;
}

//----------------------------------------------------------------------------
//  Palette
//----------------------------------------------------------------------------

/**
**  Convert palette.
**
**  @param pal  Pointer to palette
**
**  @return     Pointer to palette
*/
unsigned char* ConvertPalette(unsigned char* pal)
{
	int i;

	// PNG needs 0-256
	for (i = 0; i < 768; ++i) {
		pal[i] <<= 2;
	}

	return pal;
}

/**
**		Convert rgbx to rgb
*/
unsigned char* ConvertPaletteRGBXtoRGB(unsigned char* pal)
{
	int i;
	int j;

	for( i=0; i<256; ++i ) {
		for( j=0; j<3; ++j ) {
			pal[i*3+j]=pal[i*4+j];
		}
	}

	return pal;
}

/**
**  Convert rgb to my format.
*/
bool ConvertRgb(const char *mpqfile, const char *arcfile, const char *file)
{
	unsigned char *palp;
	char buf[8192] = {'\0'};
	FILE* f;
	int i;
	size_t l;

	bool ret = true;

	ret = FileExists(mpqfile);
	if(ret) {

		sprintf(buf, "%s.wpe", arcfile);

		int err_ret = ExtractMPQEntry(mpqfile, arcfile, &palp, NULL);
		if (err_ret == ERROR_SUCCESS) {

			ConvertPaletteRGBXtoRGB(palp);

			//
			//  Generate RGB File.
			//
			sprintf(buf, "%s/%s/%s.rgb", Dir, TILESET_PATH, file);
			CheckPath(buf);
			f = fopen(buf, "wb");
			if (!f) {
				perror("");
				printf("Can't open %s\n", buf);
				error("Memory error", "Could not allocate enough memory to read archive.");
			}
			if (fwrite(palp, 1, 256 * 3, f) != 256 * 3) {
				printf("Can't write %d bytes\n", 256 * 3);
				fflush(stdout);
			}

			fclose(f);

			//
			//  Generate GIMP palette
			//
			sprintf(buf, "%s/%s/%s.gimp", Dir, TILESET_PATH, file);
			CheckPath(buf);
			f = fopen(buf, "wb");
			if (!f) {
				perror("");
				printf("Can't open %s\n", buf);
				error("Memory error", "Could not allocate enough memory to read archive.");
			}
			fprintf(f, "GIMP Palette\n# Stratagus %c%s -- GIMP Palette file\n",
				toupper(*file), file + 1);

			for (i = 0; i < 256; ++i) {
				// FIXME: insert nice names!
				fprintf(f, "%d %d %d\t#%d\n", palp[i * 3], palp[i * 3 + 1], palp[i * 3 + 2], i);
			}

			fclose(f);

			free(palp);
		}
		else {
			ret = false;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
//  Tileset
//----------------------------------------------------------------------------

#ifdef MAKE_CCL
void SaveCCL(const unsigned char *map __attribute__((unused)),
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
	fprintf(f, "  \"image\", \"tilesets/.png\",\n");
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

/**
**  Decode a minitile into the image.
*/
void DecodeMiniTile(unsigned char* image, int ix, int iy, int iadd,
	unsigned char* mini, int index, int flipx, int flipy)
{
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			image[(y + iy * 8) * iadd + ix * 8 + x] =
				mini[index + (flipy ? (7 - y) : y) * 8 + (flipx ? (7 - x) : x)];
		}
	}
}

/**
**  Convert tiles into image.
*/
unsigned char* ConvertTile(unsigned char* mini, const char* mega, int msize,
	const char* map __attribute__((unused)),	int mapl __attribute__((unused)), int *wp, int *hp)

{
	unsigned char* image;
	const unsigned short* mp;
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
	image = (unsigned char *)calloc(1, height * width);

	for (i = 0; i < numtiles; ++i) {
		//mp = (const unsigned short *)(mega + img2tile[i] * 32);
		mp = (const unsigned short *)(mega + i * 32);
		for (y = 0; y < 4; ++y) {
			for (x = 0; x < 4; ++x) {
				offset = ConvertLE16(mp[x + y * 4]);
				DecodeMiniTile(image,
					x + ((i % TILE_PER_ROW) * 4), y + (i / TILE_PER_ROW) * 4,
					width, mini, (offset / 2) * 64, offset & 1, 0);
			}
		}
	}

	*wp = width;
	*hp = height;
#ifdef MAKE_CCL
	SaveCCL((unsigned char *)map, map2tile, mapl);
	free(map2tile);
#endif
	return image;
}

/**
**  Convert a tileset to my format.
*/
bool ConvertTileset(const char *mpqfile, const char* arcfile, const char* file)
{
	unsigned char* palp;
	unsigned char* megp;
	unsigned char* minp;
	unsigned char* mapp;
	unsigned char* flagp;
	unsigned char* image;
	int w;
	int h;
	int megl;
	int mapl;
	char buf[8192] = {'\0'};
	bool ret = true;

	if (!strcmp(arcfile, "tileset\\Install")) {
		sprintf(buf, "tileset\\install.wpe");
		//palp = ExtractEntry(buf);
		ExtractMPQEntry(mpqfile, buf, &palp, NULL);
		sprintf(buf, "tileset\\install.vr4");
		//minp = ExtractEntry(buf);
		ExtractMPQEntry(mpqfile, buf, &minp, NULL);
	} else {
		sprintf(buf, "%s.wpe", arcfile);
		//palp = ExtractEntry(buf);
		ExtractMPQEntry(mpqfile, buf, &palp, NULL);
		sprintf(buf, "%s.vr4", arcfile);
		//minp = ExtractEntry(buf);
		ExtractMPQEntry(mpqfile, buf, &minp, NULL);
	}
	sprintf(buf, "%s.vx4", arcfile);
	//megp = ExtractEntry(buf);

	size_t megl_len = 0;
	ExtractMPQEntry(mpqfile, buf, &megp, &megl_len);
	megl = megl_len;
	sprintf(buf, "%s.cv5", arcfile);
	//mapp = ExtractEntry(buf);
	size_t mapl_len = 0;
	ExtractMPQEntry(mpqfile, buf, &mapp, &mapl_len);
	mapl = mapl_len;

	sprintf(buf, "%s.vf4", arcfile);
	//flagp = ExtractEntry(buf);
	ExtractMPQEntry(mpqfile, buf, &flagp, NULL);

	image = ConvertTile(minp, (char *)megp, megl, (char *)mapp, mapl, &w, &h);

#ifdef DEBUG
	int flagl = EntrySize;
	sprintf(buf, "%s/%s-flags.txt", Dir, strstr(arcfile, "\\") + 1);
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

	free(megp);
	free(minp);
	free(mapp);
	free(flagp);

	ConvertPaletteRGBXtoRGB(palp);

	sprintf(buf, "%s/%s/%s.png", Dir, TILESET_PATH, file);
	printf("tileset png: %s\n", buf);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 0);

	free(image);
	free(palp);

	return ret;
}

//----------------------------------------------------------------------------
//  Graphics
//----------------------------------------------------------------------------

/**
**  Decode a entry(frame) into image.
*/
void DecodeGfxEntry(int index, unsigned char* start,
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

/**
**  Decode a entry(frame) into image.
*/
void DecodeGfuEntry(int index, unsigned char* start,
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

/**
**  Convert graphics into image.
*/
unsigned char* ConvertGraphic(int gfx, unsigned char* bp, int *wp, int *hp,
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
		error("Memory error", "Could not allocate enough memory to read archive.");
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

void ConvertPal3(unsigned char* image, int w, int h)
{
	int i;

	// FIXME: this isn't correct, there should be partial transparency
	for (i = 0; i < w * h; ++i) {
		if (image[i] < 16 || image[i] > 62) {
			image[i] = 255;
		}
	}
}

/**
**  Convert a graphic to my format.
*/
bool ConvertGfx(const char *mpqfile, const char* arcfile, const char* file, int pale)
{
	unsigned char* palp = NULL;
	unsigned char* gfxp = NULL;
	unsigned char* gfxp2 = NULL;
	unsigned char* image = NULL;
	int w;
	int h;
	char buf[1024];
	bool ret = true;

	ret = FileExists(mpqfile);

	if(ret) {
		int error = ExtractMPQEntry(mpqfile, arcfile, &gfxp, NULL);
		if (error != ERROR_SUCCESS)
		{
			ret = false;
		}

		image = ConvertGraphic(1, gfxp, &w, &h, gfxp2, 0);

		palp = Palettes[pale];

		free(gfxp);

		if (pale == 3) {
			ConvertPal3(image, w, h);
		}

		sprintf(buf, "%s/%s/%s.png", Dir, GRAPHICS_PATH, file);
		CheckPath(buf);
		SavePNG(buf, image, w, h, palp, 255);

		free(image);

		if (error != ERROR_SUCCESS)
		{
			ret = false;
		}
	}

	return ret;
}

/**
**  Convert a uncompressed graphic to my format.
*/
bool ConvertGfu(const char *mpqfile, const char* arcfile, const char* file, int pale)
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
	bool ret = true;

	ret = FileExists(mpqfile);

	if(ret) {

		int error = ExtractMPQEntry(mpqfile, arcfile, &gfup, NULL);
		if (error == ERROR_SUCCESS)
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

			palp = Palettes[pale];



			sprintf(buf, "%s/%s/%s.png", Dir, GRAPHICS_PATH, file);
			CheckPath(buf);
			SavePNG(buf, image, w, h, palp, 255);

			free(image);
			ret = false;
		}
		free(gfup);

	}

	return ret;
}

void SaveImage(char *name, unsigned char *image, unsigned char *palp, int id, int w, int h)
{
	unsigned char *buf = (unsigned char *)malloc(w * h);
	int i;

	for (i = 0; i < h; ++i) {
		memcpy(buf + w*i, image + id*28*64 + 64*i, w);
	}

	SavePNG(name, buf, w, h, palp, 255);

	free(buf);
}


void SaveButton(char *name, unsigned char *image, unsigned char *palp, int size, int id)
{
	unsigned char *button;
	int i, j;

	button = (unsigned char *)malloc(size * 28);

#define copyimage(dst, src) \
	for (j = 0; j < 28; ++j) { \
		memcpy((dst + size*j), (src + 64*j), 8); \
	}

	copyimage(button + 0, image + (id - 1) * 28 * 64);
	for (i = 8; i < size - 8; i += 8) {
		copyimage(button + i, image + id * 28 * 64);
	}
	copyimage(button + size - 8, image + (id + 1) * 28 * 64);

	for (i = 0; i < size * 28; ++i) {
		if (button[i] == 41) {
			button[i] = 255;
		}
	}

	SavePNG(name, button, size, 28, palp, 255);

	free(button);
}

bool ConvertWidgets(const char *mpqfile, const char* arcfile, const char* file, int pale)
{
	unsigned char* palp = NULL;
	unsigned char* gfup = NULL;
	unsigned char* gfup2 = NULL;
	unsigned char* image = NULL;
	int w;
	int h;
	char buf[1024];
	unsigned char* p;
	unsigned char* end;
	bool ret = true;

	ret = FileExists(mpqfile);

	if(ret) {
		int error = ExtractMPQEntry(mpqfile, arcfile, &gfup, NULL);
		if (error == ERROR_SUCCESS)
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

			palp = Palettes[pale];

			free(gfup);

			sprintf(buf, "%s/graphics/%s/", Dir, file);
			CheckPath(buf);

			sprintf(buf, "%s/graphics/%s/menu.png", Dir, file);
			SaveImage(buf, image, palp, 1, 64, 20);

			sprintf(buf, "%s/graphics/%s/menu pressed.png", Dir, file);
			SaveImage(buf, image, palp, 2, 64, 20);


			sprintf(buf, "%s/graphics/%s/minimap terrain disabled.png", Dir, file);
			SaveImage(buf, image, palp, 3, 64, 20);

			sprintf(buf, "%s/graphics/%s/minimap terrain.png", Dir, file);
			SaveImage(buf, image, palp, 4, 64, 20);

			sprintf(buf, "%s/graphics/%s/minimap terrain pressed.png", Dir, file);
			SaveImage(buf, image, palp, 5, 64, 20);


			sprintf(buf, "%s/graphics/%s/diplomacy disabled.png", Dir, file);
			SaveImage(buf, image, palp, 83, 64, 20);

			sprintf(buf, "%s/graphics/%s/diplomacy.png", Dir, file);
			SaveImage(buf, image, palp, 84, 64, 20);

			sprintf(buf, "%s/graphics/%s/diplomacy pressed.png", Dir, file);
			SaveImage(buf, image, palp, 85, 64, 20);


			sprintf(buf, "%s/graphics/%s/button left disabled 224x28.png", Dir, file);
			SaveButton(buf, image, palp, 224, 104);

			sprintf(buf, "%s/graphics/%s/button left 224x28.png", Dir, file);
			SaveButton(buf, image, palp, 224, 107);

			sprintf(buf, "%s/graphics/%s/button left pressed 224x28.png", Dir, file);
			SaveButton(buf, image, palp, 224, 110);


			sprintf(buf, "%s/graphics/%s/button left disabled 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 104);

			sprintf(buf, "%s/graphics/%s/button left 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 107);

			sprintf(buf, "%s/graphics/%s/button left pressed 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 110);


			sprintf(buf, "%s/graphics/%s/button disabled 224x28.png", Dir, file);
			SaveButton(buf, image, palp, 224, 113);

			sprintf(buf, "%s/graphics/%s/button 224x28.png", Dir, file);
			SaveButton(buf, image, palp, 224, 116);

			sprintf(buf, "%s/graphics/%s/button pressed 224x28.png", Dir, file);
			SaveButton(buf, image, palp, 224, 119);


			sprintf(buf, "%s/graphics/%s/button disabled 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 113);

			sprintf(buf, "%s/graphics/%s/button 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 116);

			sprintf(buf, "%s/graphics/%s/button pressed 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 119);


			sprintf(buf, "%s/graphics/%s/button right disabled 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 122);

			sprintf(buf, "%s/graphics/%s/button right 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 125);

			sprintf(buf, "%s/graphics/%s/button right pressed 104x28.png", Dir, file);
			SaveButton(buf, image, palp, 104, 128);
		}
	}

	free(image);

	return ret;
}

struct PCXheader {
	unsigned char Manufacturer;
	unsigned char Version;
	unsigned char Encoding;
	unsigned char BitsPerPixel;
	short Xmin, Ymin, Xmax, Ymax;
	short HDpi, VDpi;
	unsigned char Colormap[48];
	unsigned char Reserved;
	unsigned char NPlanes;
	short BytesPerLine;
	short PaletteInfo;
	short HscreenSize;
	short VscreenSize;
	unsigned char Filler[54];
};

/**
**  Convert 8 bit pcx file to raw image
*/
void ConvertPcxToRaw(unsigned char *pcx, unsigned char **raw, unsigned char **pal,
	int *w, int *h)
{
	struct PCXheader pcxh;
	int y;
	int i;
	int count;
	unsigned char *src;
	unsigned char *dest;
	unsigned char ch;

	ch=0;
	memcpy(&pcxh, pcx, sizeof(struct PCXheader));
	pcxh.Xmin = ConvertLE16(pcxh.Xmin);
	pcxh.Ymin = ConvertLE16(pcxh.Ymin);
	pcxh.Xmax = ConvertLE16(pcxh.Xmax);
	pcxh.Ymax = ConvertLE16(pcxh.Ymax);
	pcxh.BytesPerLine = ConvertLE16(pcxh.BytesPerLine);

	*w = pcxh.Xmax - pcxh.Xmin + 1;
	*h = pcxh.Ymax - pcxh.Ymin + 1;

	*raw = (unsigned char *)malloc(*w * *h);
	src = pcx + sizeof(struct PCXheader);

	for (y = 0; y < *h; ++y) {
		count = 0;
		dest = *raw + y * *w;
		for (i = 0; i < *w; ++i) {
			if (!count) {
				ch = *src++;
				if ((ch & 0xc0) == 0xc0) {
					count = ch & 0x3f;
					ch = *src++;
				} else {
					count = 1;
				}
			}
			dest[i] = ch;
			--count;
		}
	}

	*pal = (unsigned char *)malloc(256 * 3);
	dest = *pal;
	do {
		ch = *src++;
	} while (ch != 12);

	for (i = 0; i < 256 * 3; ++i) {
		*dest++ = *src++;
	}
}

/**
**  Convert a pcx graphic to my format
**
**  @param arcfile File identifier in the MPQ file
**  @param file Place to save the file on the drive (relative)
*/
bool ConvertPcx(const char *mpqfile, const char *arcfile, const char *file)
{
	unsigned char *palp;
	unsigned char *pcxp;
	unsigned char *image;
	char buf[1024];
	int w;
	int h;
	bool ret = true;

	ret = FileExists(mpqfile);

	if(ret) {
		int error = ExtractMPQEntry(mpqfile, arcfile, &pcxp, NULL);
		if (error == ERROR_SUCCESS)
		{
			ConvertPcxToRaw(pcxp, &image, &palp, &w, &h);
			free(pcxp);

			sprintf(buf, "%s/%s/%s.png", Dir, GRAPHICS_PATH, file);
			CheckPath(buf);
			SavePNG(buf, image, w, h, palp, 0);

			free(image);
			free(palp);
		}
		else
		{
			ret = false;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
//  Font
//----------------------------------------------------------------------------

/**
**  Convert font into image.
*/
unsigned char* ConvertFnt(unsigned char* start, int *wp, int *hp)
{
	int i;
	int count;
	int max_width;
	int max_height;
	int width;
	int height;
	int w;
	int h;
	int xoff;
	int yoff;
	unsigned char* bp;
	unsigned char* dp;
	unsigned char* image;
	unsigned* offsets;
	int image_width;
	int image_height;
	int IPR;

	bp = start + 5;  // skip "FONT "
	//printf("%s %s \n", start, start + 5);
	count = FetchByte(bp);
	count -= 32;
	max_width = FetchByte(bp);
	max_height = FetchByte(bp);

	IPR = 15;  // 15 characters per row
	image_width = max_width * IPR;
	image_height = (count + IPR - 1) / IPR * max_height;

//	printf("Font: count %d max-width %2d max-height %2d\n",
//		count, max_width, max_height);

	offsets = (unsigned *)malloc(count * sizeof(uint32_t));
	for (i = 0; i < count; ++i) {
		offsets[i] = FetchLE32(bp);
//		printf("%03d: offset %d\n", i, offsets[i]);
	}

	image = (unsigned char *)malloc(image_width * image_height);
	if (!image) {
		printf("Can't allocate image\n");
		error("Memory error", "Could not allocate enough memory to read archive.");
	}
	memset(image, 255, image_width * image_height);

	for (i = 0; i < count; ++i) {
		if (!offsets[i]) {
//			printf("%03d: unused\n", i);
			continue;
		}
		bp = start + offsets[i];
		width = FetchByte(bp); //crash!!!
		height = FetchByte(bp);
		xoff = FetchByte(bp);
		yoff = FetchByte(bp);

//		printf("%03d: width %d height %d xoff %d yoff %d\n",
//			i, width, height, xoff, yoff);

		dp = image + xoff + yoff * max_width + i * (max_width * max_height);
		h = w = 0;
		for (;;) {
			int ctrl;
			ctrl = FetchByte(bp);
			w += (ctrl >> 3) & 0x1F;
			if (w >= width) {
				w -= width;
				++h;
				if (h >= height) {
					break;
				}
			}
			dp[h * max_width + w] = ctrl & 0x07;
			++w;
			if (w >= width) {
				w -= width;
				++h;
				if (h >= height) {
					break;
				}
			}
		}
	}
	free(offsets);

	*wp = max_width;
	*hp = max_height * count;

	return image;
}

/**
**  Convert a font to my format.
**
**  @return true if everything is ok
*/
bool ConvertFont(const char *mpqfile, const char* arcfile, const char* file, int pale) {
	unsigned char* palp;
	unsigned char* fntp;
	unsigned char* image;
	int w;
	int h;
	char buf[8192] = {'\0'};
	bool ret = true;

	palp = Palettes[pale];

	ret = FileExists(mpqfile);

	if (ret) {
		int error = ExtractMPQEntry(mpqfile, arcfile, &fntp, NULL);
		if (error == ERROR_SUCCESS)
		{
			image = ConvertFnt(fntp, &w, &h);
			free(fntp);

			sprintf(buf, "%s/%s/%s.png", Dir, FONT_PATH, file);
			CheckPath(buf);
			SavePNG(buf, image, w, h, palp, 255);

			free(image);
		}
		else
		{
			ret = false;
		}
	}

	return ret;
}

//----------------------------------------------------------------------------
//		Wav
//----------------------------------------------------------------------------

/**
**  Convert wav to gzipped format
**
**  @param arcfile File identifier in the MPQ file
**  @param file Place to save the file on the drive (relative)
*/
bool ConvertWav(const char *mpqfile, const char *arcfile, const char *file)
{
	char buf[8192] = {'\0'};
	bool ret = true;

	ret = FileExists(mpqfile);

	if(ret) {
		sprintf(buf, "%s/%s/%s.wav.gz", Dir, SOUND_PATH, file);
		CheckPath(buf);

		int error = ExtractMPQFile(mpqfile, arcfile, buf, true);
		if (error != ERROR_SUCCESS)
		{
			ret = false;
		}
	}

	return ret;
}

/**
**  Raw extraction
**
**  @param arcfile File identifier in the MPQ file
**  @param file Place to save the file on the drive (relative)
*/
bool RawExtract(const char *mpqfile, const char *arcfile, const char *file)
{
	char buf[8192] = {'\0'};
	bool ret = true;

	sprintf(buf, "%s/%s", Dir, file);
	CheckPath(buf);

	ret = FileExists(mpqfile);

	if(ret) {
		int error = ExtractMPQFile(mpqfile, arcfile, buf, false);

		if (error != ERROR_SUCCESS)
		{
			ret = false;
		}
	}

	return ret;
}

/**
**  MPQ Sub-extraction
**
**  @param arcfile File identifier in the MPQ file
**  @param file Place to save the file on the drive (relative)
*/
bool MPQSubExtract(const char *mpqfile, const char *arcfile, const char *file)
{
	char buf[8192] = {'\0'};
	bool ret = true;
	sprintf(buf, "%s/%s", Dir, file);
	CheckPath(buf);

	int error = ExtractMPQFile(mpqfile, arcfile, buf, false);

	if (error != ERROR_SUCCESS)
	{
		ret = false;
	}

	return ret;
}

//----------------------------------------------------------------------------
//  Video
//----------------------------------------------------------------------------

/**
**  Convert SMK video to OGV
*/
bool ConvertVideo(const char *mpqfile, const char *arcfile, const char *file)
{
	char buf[8192] = {'\0'};
	bool ret = true;

	ret = FileExists(mpqfile);

	if(ret) {

		snprintf(buf,sizeof(buf),"%s/%s/%s.smk", Dir, VIDEO_PATH, file);
		CheckPath(buf);

		int error = ExtractMPQFile(mpqfile, arcfile, buf, false);
		if (error != ERROR_SUCCESS)
		{
			ret = false;
		}

		string ffmpeg_str = string("ffmpeg -y -i ") + buf + " -codec:v libtheora -qscale:v 31 -codec:a libvorbis -qscale:a 15 -pix_fmt yuv420p " + Dir + "/" + VIDEO_PATH + "/" + file;

		//cout << "video: " << ffmpeg_str << endl;

		int sys_call = system(ffmpeg_str.c_str());
		if(sys_call != 0)
		{
			ret = false;
		}

		remove(buf);
	}

	return ret;
}

//----------------------------------------------------------------------------
//		Panels
//----------------------------------------------------------------------------

unsigned char *CreatePanel(int width, int height)
{
	unsigned char *buf;
	int i, j;

	buf = (unsigned char *)malloc(width * height * 4);
	memset(buf, 0, width * height * 4);

#define pixel2(i, j, r, g, b, a) \
	buf[(j) * width * 4 + (i) * 4 + 0] = r; \
	buf[(j) * width * 4 + (i) * 4 + 1] = g; \
	buf[(j) * width * 4 + (i) * 4 + 2] = b; \
	buf[(j) * width * 4 + (i) * 4 + 3] = a;

#define pixel(i, j) \
	pixel2((i), (j), 0x0, 0x8, 0x40, 0xff)

	for (j = 1; j < height - 1; ++j) {
		for (i = 1; i < width - 1; ++i) {
			pixel2(i, j, 0x0, 0x8, 0x40, 0x80);
		}
	}
	for (i = 3; i < width - 3; ++i) {
		pixel(i, 0);
		pixel(i, height - 1);
	}
	for (i = 3; i < height - 3; ++i) {
		pixel(0, i);
		pixel(width - 1, i);
	}
	// top left
	pixel(1, 1);
	pixel(2, 1);
	pixel(1, 2);
	// top right
	pixel(width - 3, 1);
	pixel(width - 2, 1);
	pixel(width - 2, 2);
	// bottom left
	pixel(1, height - 3);
	pixel(1, height - 2);
	pixel(2, height - 2);
	// bottom right
	pixel(width - 3, height - 2);
	pixel(width - 2, height - 2);
	pixel(width - 2, height - 3);

#undef pixel
#undef pixel2

	return buf;
}

int SavePanel(int width, int height)
{
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned char **lines;
	int i;
	char name[256];
	unsigned char *buf;

	sprintf(name, "%s/graphics/ui/panels/%dx%d.png", Dir, width, height);
	CheckPath(name);

	if (!(fp = fopen(name, "wb"))) {
		fprintf(stderr,"%s:", name);
		perror("Can't open file");
		return 1;
	}

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr) {
		fclose(fp);
		return 1;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		png_destroy_write_struct(&png_ptr, NULL);
		fclose(fp);
		return 1;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		// FIXME: must free buffers!!
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return 1;
	}
	png_init_io(png_ptr, fp);

	// zlib parameters
	png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

	// prepare the file information
	png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB_ALPHA, 0, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	buf = CreatePanel(width, height);

	// write the file header information
	png_write_info(png_ptr, info_ptr);  // write the file header information

	// set transformation

	// prepare image
	lines = (unsigned char **)malloc(height * sizeof(*lines));
	if (!lines) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		free(buf);
		return 1;
	}

	for (i = 0; i < height; ++i) {
		lines[i] = buf + i * width * 4;
	}

	png_write_image(png_ptr, lines);
	png_write_end(png_ptr, info_ptr);

	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);

	free(lines);
	free(buf);

	return 0;
}

void CreatePanels()
{
	SavePanel(264, 288);
	SavePanel(384, 256);
	SavePanel(312, 312);
	SavePanel(288, 128);
	SavePanel(296, 336);
}

//----------------------------------------------------------------------------
//  Main loop
//----------------------------------------------------------------------------

/**
**  Display the usage.
*/
void Usage(const char* name)
{
	printf("%s\n\
Usage: %s archive-directory [destination-directory] [mpqlist-file]\n\
\t-V\tShow version\n\
\t-h\tShow usage\n\
archive-directory\tDirectory which include the archive install.exe or stardat.mpq...\n\
destination-directory\tDirectory where the extracted files are placed.\n\
mpqlist-file\tmpqlist.txt file which contains mpq file names\n"
	,NameLine, name);
}

/**
**		Main
*/
#undef main
int main(int argc, char** argv)
{
	unsigned u;
	char buf[8192] = {'\0'};
	int i;
	FILE* f;

	for (i = 0; i < argc; ++i) {
		if (!strcmp(argv[i], "-V")) {
			printf(VERSION "\n");
			return 0;
		}
		if (!strcmp(argv[i], "-h")) {
			argc = 0;
			break;
		}
	}

	if (argc != 2 && argc != 3 && argc != 4) {
		Usage(argv[0]);
		exit(-1);
	}

	ArchiveDir = argv[1];
	if (argc >= 3) {
		Dir = argv[2];
	} else {
		Dir = "data";
	}
	if (argc >= 4) {
		strcpy(mpq_listfile, argv[3]);
	} else {
		sprintf(mpq_listfile, "%s/mpqlist.txt", Dir);
	}

	sprintf(buf, "%s/extracted", Dir);
	f = fopen(buf, "r");
	if (f) {
		char version[20];
		int len = 0;
		if (fgets(version, 20, f))
			len = 1;
		fclose(f);
		if (len != 0 && strcmp(version, VERSION) == 0) {
			printf("Note: Data is already extracted in Dir \"%s\" with this version of startool\n", Dir);
			fflush(stdout);
		}
	}

	//Mpq = new CMpq;

	printf("Extract from \"%s\" to \"%s\"\n", ArchiveDir, Dir);
	printf("Using mpq list file \"%s\"\n", mpq_listfile);
	printf("Please be patient, the data may take a couple of minutes to extract...\n\n");
	fflush(stdout);

	string mpqfile;
	string submpqfile;

	/// NEW PARSER CODE

	for (i = 0; i <= 1; ++i) {
			Control *c;
			printf("Loop: %d\n", i);
			unsigned len;
			bool extracted = false;

			//i = 0;
			switch (i)
			{
			case 0:
				// CD install.exe renamed to StarCraft.mpq or other main mpq file
				c = CDTodo;
				len = sizeof(CDTodo) / sizeof(*CDTodo);
				extracted = false;
				break;
			case 1:
				// StarDat.mpq or stardat.mpq from CD or hard drive
				c = Todo;
				len = sizeof(Todo) / sizeof(*Todo);
				extracted = true;
				break;
			}

			bool case_func = false;
			for (u = 0; u < len; ++u) {

				switch (c[u].Type) {
					case F:
						if(submpqfile.empty()) {
							sprintf(buf, "%s/%s", ArchiveDir, c[u].ArcFile);
						}
						else {
							sprintf(buf, "%s", submpqfile.c_str());
						}
						printf("FileExists: %s", buf);
						case_func = FileExists(buf);
						if(case_func) {
							mpqfile = buf;
						}
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case Q:
						printf("MPQSubExtract: %s, %s", c[u].File, c[u].ArcFile);
						case_func = MPQSubExtract(mpqfile.c_str(), c[u].ArcFile, c[u].File);
						if(case_func) {
							sprintf(buf, "%s/%s", Dir, c[u].File);
							submpqfile = buf;
						}
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case M: // WORKS!
						printf("ConvertMap: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
						case_func = ConvertMap(mpqfile.c_str(), c[u].ArcFile, c[u].File, extracted);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					/*case R: // UNUSED?
						printf("ConvertRgb: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
						case_func = ConvertRgb(mpqfile.c_str(), c[u].ArcFile, c[u].File);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;*/
					case T:  // WORKS!
						printf("ConvertTileset: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
						case_func = ConvertTileset(mpqfile.c_str(), c[u].ArcFile, c[u].File);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case G: // WORKS!
						printf("ConvertGfx: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
						case_func = ConvertGfx(mpqfile.c_str(), c[u].ArcFile, c[u].File, c[u].Arg1);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case U: // WORKS!
						printf("ConvertGfu: %s, %s, %s",mpqfile.c_str(),  c[u].File, c[u].ArcFile);
						case_func = ConvertGfu(mpqfile.c_str(), c[u].ArcFile, c[u].File, c[u].Arg1);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case I: // WORKS!
						printf("ConvertWidgets: %s, %s, %s",mpqfile.c_str(),  c[u].File, c[u].ArcFile);
						case_func = ConvertWidgets(mpqfile.c_str(), c[u].ArcFile, c[u].File, c[u].Arg1);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case N: // WORKS!
						printf("ConvertFont: %s, %s, %s",mpqfile.c_str(), c[u].File, c[u].ArcFile);
						case_func = ConvertFont(mpqfile.c_str(), c[u].ArcFile, c[u].File, 2);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case W: // WORKS!
					    printf("ConvertWav: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					    case_func = ConvertWav(mpqfile.c_str(), c[u].ArcFile, c[u].File);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
				    case V: // WORKS!
					    printf("ConvertVideo: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
					    case_func = ConvertVideo(mpqfile.c_str(), c[u].ArcFile, c[u].File);
					    printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case H: // WORKS!
						printf("ConvertPcx: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
						case_func = ConvertPcx(mpqfile.c_str(), c[u].ArcFile, c[u].File);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					case E: // WORKS
					    // ConvertChk() for maps instead of Raw??
						printf("RawExtract: %s, %s, %s", mpqfile.c_str(), c[u].File, c[u].ArcFile);
						// TBD: I think campaigns this must be somehow converted to stratagus
						case_func = RawExtract(mpqfile.c_str(), c[u].ArcFile, c[u].File);
						printf("...%s\n", case_func ? "ok" : "nok");
						break;
					default:
						break;
				}
			}
	}

	// remove temporary sub files
	if(!submpqfile.empty()) {
		unlink(submpqfile.c_str());
	}
	
	//delete Mpq;

	CreatePanels();

	sprintf(buf, "%s/extracted", Dir);
	f = fopen(buf, "w");
	fprintf(f, VERSION "\n");
	fclose(f);

	printf("Done.\n");

	return 0;
}

//@}
