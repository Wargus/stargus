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

//#include "stargus.h"
#include "startool.h"
#include <stratagus-gameutils.h>

/**
**  Offsets for each entry into original archive buffer.
*/
static unsigned char** ArchiveOffsets;

static char* ArchiveDir;

//----------------------------------------------------------------------------
//  TOOLS
//----------------------------------------------------------------------------

/**
**  Check if path exists, if not make all directories.
*/
void CheckPath(const char* path)
{
	char* cp;
	char* s;

#ifdef WIN32
	cp = _strdup(path);
#else
	cp = strdup(path);
#endif
	s = strrchr(cp, '/');
	if (s) {
		*s = '\0';  // remove file
		s = cp;
		for (;;) {  // make each path element
			s = strchr(s, '/');
			if (s) {
				*s = '\0';
			}
#if defined(_MSC_VER) || defined(WIN32)
			_mkdir(cp);
#else
			mkdir(cp, 0777);
#endif
			if (s) {
				*s++ = '/';
			} else {
				break;
			}
		}
	}
	free(cp);
}

//----------------------------------------------------------------------------
//		PNG
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
int SavePNG(const char *name, unsigned char *image, int w, int h,
	unsigned char *pal, int transparent)
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
//		Archive
//----------------------------------------------------------------------------

/**
**  Open the archive file.
**
**  @param file  Archive file name
**  @param type  Archive type requested
*/
int OpenArchive(const char *file)
{
	//
	//  Open the archive file
	//
	MpqFD = fopen(file, "rb");
	if (!MpqFD) {
		printf("Can't open %s\n", file);
		return -1;
	}

	if (Mpq->ReadInfo(MpqFD, listfile)) {
		printf("MpqReadInfo failed\n");
		fclose(MpqFD);
		MpqFD = NULL;
		return -1;
	}

	return 0;
}

/**
**  Extract/uncompress entry.
**
**  @param name  Name of the entry to extract
**
**  @return      Pointer to uncompressed entry
*/
unsigned char *ExtractEntry(const char *name)
{
	int i;
	unsigned char *buf;

	buf = NULL;
	for (i = 0; i < Mpq->FileCount; ++i) {
		if (!strcmp(name, Mpq->FilenameTable + i * PATH_MAX)) {
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
}

/**
**		Close the archive file.
*/
int CloseArchive(void)
{
	if (MpqFD) {
		fclose(MpqFD);
		MpqFD = NULL;
	}
	return 0;
}

//----------------------------------------------------------------------------
//		Map
//----------------------------------------------------------------------------

/**
**  Convert map
**
**  @extracted in case of installation the map files are yet extracted from mpq file
*/
int ConvertMap(const char *mapfile, const char *file, bool extracted)
{
	FILE *fd;
	char buf[1024];
	char buf2[1024];

	sprintf(buf, "%s/%s", Dir, file);
	CheckPath(buf);

	if(!extracted)
	{
		unsigned char *p;
		p = ExtractEntry(mapfile);
		fd = fopen(buf, "wb");
		if (!fd) {
			free(p);
			return -1;
		}
		fwrite(p, EntrySize, 1, fd);
		fclose(fd);
		free(p);

		ConvertScm(buf, buf, listfile);
	}
	else
	{
		sprintf(buf2, "%s/%s", ArchiveDir, file);
		CheckPath(buf2);

		ConvertScm(buf2, buf, listfile);
	}



	return 0;
}

#ifdef USE_STORMLIB
int ExtractMPQFile(char *szArchiveName, char *szArchivedFile, char *szFileName, bool compress)
{
	HANDLE hMpq   = NULL;          // Open archive handle
	HANDLE hFile  = NULL;          // Archived file handle
	FILE   *file  = NULL;          // Disk file handle
	gzFile gzfile = NULL;          // Compressed file handle
	int    nError = ERROR_SUCCESS; // Result value

	// Open an archive, e.g. "d2music.mpq"
	if(nError == ERROR_SUCCESS) {
		if(!SFileOpenArchive(szArchiveName, 0, STREAM_FLAG_READ_ONLY, &hMpq))
			nError = GetLastError();
	}

	// Open a file in the archive, e.g. "data\global\music\Act1\tristram.wav"
	if(nError == ERROR_SUCCESS) {
		if(!SFileOpenFileEx(hMpq, szArchivedFile, 0, &hFile))
			nError = GetLastError();
	}

	// Create the target file
	if(nError == ERROR_SUCCESS) {
		CheckPath(szFileName);
		if (compress) {
			gzfile = gzopen(szFileName, "wb9");
		} else {
			file = fopen(szFileName, "wb");
		}
	}

	// Read the file from the archive
	if(nError == ERROR_SUCCESS) {
		char  szBuffer[0x10000];
		DWORD dwBytes = 1;

		while(dwBytes > 0) {
			SFileReadFile(hFile, szBuffer, sizeof(szBuffer), &dwBytes, NULL);
			if(dwBytes > 0) {
				if (compress) {
					gzwrite(gzfile, szBuffer, dwBytes);
				} else {
					fwrite(szBuffer, 1, dwBytes, file);
				}
			}
		}
	}

	// Cleanup and exit
	if(file != NULL) {
		fclose(file);
	}
	if(gzfile != NULL) {
		gzclose(gzfile);
	}
	if(hFile != NULL)
		SFileCloseFile(hFile);
	if(hMpq != NULL)
		SFileCloseArchive(hMpq);

	return nError;
}
#endif

//----------------------------------------------------------------------------
//		Palette
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
int ConvertRgb(const char *listfile, const char *file)
{
	unsigned char *palp;
	char buf[1024];
	FILE *f;
	int i;

	sprintf(buf, "%s.wpe", listfile);
	palp = ExtractEntry(buf);
	ConvertPaletteRGBXtoRGB(palp);

	//
	//		Generate RGB File.
	//
	sprintf(buf, "%s/%s/%s.rgb", Dir, TILESET_PATH, file);
	CheckPath(buf);
	f = fopen(buf, "wb");
	if (!f) {
		perror("");
		printf("Can't open %s\n", buf);
		exit(-1);
	}
	if (fwrite(palp, 1, 256 * 3, f) != 256 * 3) {
		printf("Can't write %d bytes\n", 256 * 3);
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
		exit(-1);
	}
	fprintf(f, "GIMP Palette\n# Stratagus %c%s -- GIMP Palette file\n",
		toupper(*file), file + 1);

	for (i = 0; i < 256; ++i) {
		// FIXME: insert nice names!
		fprintf(f, "%d %d %d\t#%d\n", palp[i * 3], palp[i * 3 + 1], palp[i * 3 + 2], i);
	}
	fclose(f);

	free(palp);

	return 0;
}

//----------------------------------------------------------------------------
//		Tileset
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
**		Count used mega tiles for map.
*/
int CountUsedTiles(const unsigned char *map, const unsigned char *mega,
	int *map2tile, int mapl)
{
	int i;
	int j;
	int used;
	const unsigned char *tp;
	int *img2tile;

	img2tile = (int *)malloc(mapl / 52 * 16 * sizeof(int));

	memset(map2tile, 0, sizeof(map2tile));

	//
	//		Build conversion table.
	//
	for (i = 0; i < mapl / 52; ++i) {
		tp = map + i * 52 + 20;
		for (j = 0; j< 0x10; ++j ) {
			if (((i << 4) | j) > mapl) {
				break;
			}
			map2tile[(i << 4) | j] = AccessLE16(tp + j * 2);
		}
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
#if 0
	for (i = 0; i < used; ++i) {
		if (!(i % 16)) {
			DebugLevel1("\n");
		}
		DebugLevel1("%3d " _C_ img2tile[i]);
	}
	DebugLevel1("\n");
#endif

	return used;
}
#endif

/**
**  Decode a minitile into the image.
*/
void DecodeMiniTile(unsigned char *image, int ix, int iy, int iadd,
	unsigned char *mini, int index, int flipx, int flipy)
{
	for (int y = 0; y < 8; ++y) {
		for (int x = 0; x < 8; ++x) {
			image[(y + iy * 8) * iadd + ix * 8 + x] =
				mini[index + (flipy ? (7 - y) : y) * 8 + (flipx ? (7 - x) : x)];
		}
	}
}

/**
**		Convert tiles into image.
*/
unsigned char *ConvertTile(unsigned char *mini, const char *mega, int msize,
	const char *map __attribute__((unused)),
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
int ConvertTileset(const char *listfile, const char *file)
{
	unsigned char *palp;
	unsigned char *megp;
	unsigned char *minp;
	unsigned char *mapp;
	unsigned char *flagp;
	unsigned char *image;
	int w;
	int h;
	int megl;
	int mapl;
	char buf[1024];

	if (!strcmp(listfile, "tileset\\Install")) {
		sprintf(buf, "tileset\\install.wpe");
		palp = ExtractEntry(buf);
		sprintf(buf, "tileset\\install.vr4");
		minp = ExtractEntry(buf);
	} else {
		sprintf(buf, "%s.wpe", listfile);
		palp = ExtractEntry(buf);
		sprintf(buf, "%s.vr4", listfile);
		minp = ExtractEntry(buf);
	}
	sprintf(buf, "%s.vx4", listfile);
	megp = ExtractEntry(buf);
	megl = EntrySize;
	sprintf(buf, "%s.cv5", listfile);
	mapp = ExtractEntry(buf);
	mapl = EntrySize;

	sprintf(buf, "%s.vf4", listfile);
	flagp = ExtractEntry(buf);

	image = ConvertTile(minp, (char *)megp, megl, (char *)mapp, mapl, &w, &h);

#ifdef DEBUG
	int flagl = EntrySize;
	sprintf(buf, "%s/%s-flags.txt", Dir, strstr(listfile, "\\") + 1);
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
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 0);

	free(image);
	free(palp);

	return 0;
}

//----------------------------------------------------------------------------
//		Graphics
//----------------------------------------------------------------------------

/**
**		Decode a entry(frame) into image.
*/
void DecodeGfxEntry(int index,unsigned char* start
		,unsigned char* image,int ix,int iy,int iadd)
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

	bp=start+index*8;
	xoff=FetchByte(bp);
	yoff=FetchByte(bp);
	width=FetchByte(bp);
	height=FetchByte(bp);
	offset=FetchLE32(bp);

	rows=start+offset-6;
	dp=image+xoff-ix+(yoff-iy)*iadd;

	for( h=0; h<height; ++h ) {
		sp=rows+AccessLE16(rows+h*2);
		for( w=0; w<width; ) {
			ctrl=*sp++;
			if( ctrl&0x80 ) {				// transparent
				ctrl&=0x7F;
				memset(dp+h*iadd+w,255,ctrl);
				w+=ctrl;
			} else if( ctrl&0x40 ) {		// repeat
				ctrl&=0x3F;
				memset(dp+h*iadd+w,*sp++,ctrl);
				w+=ctrl;
			} else {						// set pixels
				ctrl&=0x3F;
				memcpy(dp+h*iadd+w,sp,ctrl);
				sp+=ctrl;
				w+=ctrl;
			}
		}
		//dp[h*iadd+width-1]=0;
	}
}

/**
**		Decode a entry(frame) into image.
*/
void DecodeGfuEntry(int index,unsigned char* start
		,unsigned char* image,int ix,int iy,int iadd)
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

	bp=start+index*8;
	xoff=FetchByte(bp);
	yoff=FetchByte(bp);
	width=FetchByte(bp);
	height=FetchByte(bp);
	offset=FetchLE32(bp);
	if( offset<0 ) {						// High bit of width
		offset&=0x7FFFFFFF;
		width+=256;
	}

	sp=start+offset-6;
	dp=image+xoff-ix+(yoff-iy)*iadd;
	for( i=0; i<height; ++i ) {
		memcpy(dp,sp,width);
		dp+=iadd;
		sp+=width;
	}
}

/**
**  Convert graphics into image.
*/
unsigned char* ConvertGraphic(int gfx,unsigned char* bp,int *wp,int *hp
		,unsigned char* bp2,int start2)
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

	if (bp2) {		// Init pointer to 2nd animation
		count=FetchLE16(bp2);
		max_width=FetchLE16(bp2);
		max_height=FetchLE16(bp2);
	}
	count=FetchLE16(bp);
	max_width=FetchLE16(bp);
	max_height=FetchLE16(bp);


	// Find best image size
	minx=999;
	miny=999;
	best_width=0;
	best_height=0;
	for( i=0; i<count; ++i ) {
		unsigned char* p;
		int xoff;
		int yoff;
		int width;
		int height;

		p=bp+i*8;
		xoff=FetchByte(p);
		yoff=FetchByte(p);
		width=FetchByte(p);
		height=FetchByte(p);
		endereco = FetchLE32(p);
		if( endereco&0x80000000 ) {		// high bit of width
			width+=256;
		}
		if( xoff<minx ) minx=xoff;
		if( yoff<miny ) miny=yoff;
		if( xoff+width>best_width ) best_width=xoff+width;
		if( yoff+height>best_height ) best_height=yoff+height;
	}
	// FIXME: the image isn't centered!!

#if 0
	// Taken out, must be rewritten.
	if( max_width-best_width<minx ) {
		minx=max_width-best_width;
		best_width-=minx;
	} else {
		best_width=max_width-minx;
	}
	if( max_height-best_height<miny ) {
		miny=max_height-best_height;
		best_height-=miny;
	} else {
		best_height=max_width-miny;
	}

	//best_width-=minx;
	//best_height-=miny;
#endif

	minx=0;
	miny=0;

	if( gfx ) {
		best_width=max_width;
		best_height=max_height;
		IPR=17;								// st*rcr*ft 17!
		if( count<IPR ) {				// images per row !!
			IPR=1;
			length=count;
		} else {
			length=((count+IPR-1)/IPR)*IPR;
		}
	} else {
		max_width=best_width;
		max_height=best_height;
		IPR=1;
		length=count;
	}

	image = (unsigned char *)malloc(best_width * best_height * length);

	//		Image:		0, 1, 2, 3, 4,
	//				5, 6, 7, 8, 9, ...
	if( !image ) {
		printf("Can't allocate image\n");
		exit(-1);
	}
	// Set all to transparent.
	memset(image,255,best_width*best_height*length);

	if( gfx ) {
		for( i=0; i<count; ++i ) {
	// Hardcoded support for worker with resource repairing
			if (i>=start2 && bp2) DecodeGfxEntry(i,bp2
				,image+best_width*(i%IPR)+best_height*best_width*IPR*(i/IPR)
				,minx,miny,best_width*IPR);
			else DecodeGfxEntry(i,bp
				,image+best_width*(i%IPR)+best_height*best_width*IPR*(i/IPR)
				,minx,miny,best_width*IPR);
		}
	} else {
		for( i=0; i<count; ++i ) {
			DecodeGfuEntry(i,bp
				,image+best_width*(i%IPR)+best_height*best_width*IPR*(i/IPR)
				,minx,miny,best_width*IPR);
		}
	}

	*wp=best_width*IPR;
	*hp=best_height*(length/IPR);

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
int ConvertGfx(const char* listfile, const char* file, int pale)
{
	unsigned char* palp;
	unsigned char* gfxp;
	unsigned char* gfxp2;
	unsigned char* image;
	int w;
	int h;
	char buf[1024];

	gfxp = ExtractEntry(listfile);

	gfxp2 = NULL;
	image = ConvertGraphic(1, gfxp, &w, &h, gfxp2, 0);

	palp = Palettes[pale];

	free(gfxp);

	if (pale == 3) {
		ConvertPal3(image, w, h);
	}

	sprintf(buf, "%s/%s/%s.png", Dir, UNIT_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 255);

	free(image);

	return 0;
}

/**
**  Convert an uncompressed graphic to my format.
*/
int ConvertGfu(const char* listfile, const char* file, int pale)
{
	unsigned char* palp;
	unsigned char* gfup;
	unsigned char* gfup2;
	unsigned char* image;
	int w;
	int h;
	char buf[1024];
	unsigned char* p;
	unsigned char* end;

	gfup = ExtractEntry(listfile);

	gfup2 = NULL;
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

	sprintf(buf, "%s/%s/%s.png", Dir, UNIT_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 255);

	free(image);

	return 0;
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

int ConvertWidgets(const char* listfile, const char* file, int pale)
{
	unsigned char* palp;
	unsigned char* gfup;
	unsigned char* gfup2;
	unsigned char* image;
	int w;
	int h;
	char buf[1024];
	unsigned char* p;
	unsigned char* end;

	gfup = ExtractEntry(listfile);

	gfup2 = NULL;
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


	free(image);

	return 0;
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
*/
void ConvertPcx(const char *listfile, const char *file)
{
	unsigned char *palp;
	unsigned char *pcxp;
	unsigned char *image;
	char buf[1024];
	int w;
	int h;

	pcxp = ExtractEntry(listfile);

	ConvertPcxToRaw(pcxp, &image, &palp, &w, &h);
	free(pcxp);

	sprintf(buf, "%s/%s/%s.png", Dir, UNIT_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 0);

	free(image);
	free(palp);
}

//----------------------------------------------------------------------------
//		Font
//----------------------------------------------------------------------------

/**
**  Convert font into image.
*/
unsigned char *ConvertFnt(unsigned char *start, int *wp, int *hp) {
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

	//printf("Font: count %d max-width %2d max-height %2d\n",
	//	count, max_width, max_height);

	offsets = (unsigned *)malloc(count * sizeof(uint32_t));
	for (i = 0; i < count; ++i) {
		offsets[i] = FetchLE32(bp);
	}

	image = (unsigned char *)malloc(image_width * image_height);
	if (!image) {
		printf("Can't allocate image\n");
		//error("Memory error", "Could not allocate enough memory to read archive.");
	}
	memset(image, 255, image_width * image_height);

	for (i = 0; i < count; ++i) {
		if (!offsets[i]) {
			continue;
		}
		bp = start + offsets[i];
		width = FetchByte(bp); //crash!!!
		height = FetchByte(bp);
		xoff = FetchByte(bp);
		yoff = FetchByte(bp);
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
*/
int ConvertFont(const char* listfile, const char* file, int pale, int fnte __attribute__((unused))) {
	unsigned char* palp;
	unsigned char* fntp;
	unsigned char* image;
	int w;
	int h;
	char buf[8192] = {'\0'};

	palp = Palettes[pale];
	fntp = ExtractEntry(listfile);

	image = ConvertFnt(fntp, &w, &h);
	free(fntp);

	sprintf(buf, "%s/%s/%s.png", Dir, FONT_PATH, file);
	CheckPath(buf);
	SavePNG(buf, image, w, h, palp, 255);

	free(image);

	return 0;
}

//----------------------------------------------------------------------------
//		Wav
//----------------------------------------------------------------------------

/**
**  Convert pud to my format.
*/
int ConvertWav(const char *listfile, const char *file, int wave __attribute__((unused)))
{
	unsigned char* wavp;
	char buf[8192] = {'\0'};
	gzFile gf;

	wavp = ExtractEntry(listfile);

	sprintf(buf, "%s/%s/%s.wav.gz", Dir, SOUND_PATH, file);
	CheckPath(buf);
	gf = gzopen(buf, "wb9");
	if (!gf) {
		perror("");
		printf("Can't open %s\n", buf);
		exit(-1);
	}
	if (EntrySize != gzwrite(gf, wavp, EntrySize)) {
		printf("Can't write %d bytes\n", EntrySize);
	}

	free(wavp);

	gzclose(gf);
	return 0;
}

/**
**  Raw extraction
*/
int RawExtract(const char *listfile, const char *file)
{
	FILE *fd;
	unsigned char *p;
	char buf[1024];

	sprintf(buf, "%s/%s", Dir, file);
	CheckPath(buf);
	p = ExtractEntry(listfile);
	fd = fopen(buf, "wb");
	if (!fd) {
		free(p);
		return -1;
	}
	fwrite(p, EntrySize, 1, fd);
	fclose(fd);
	free(p);
	return 0;
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
//		Main loop
//----------------------------------------------------------------------------

/**
**		Display the usage.
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
int main(int argc, char **argv)
{
	unsigned u;
	char buf[1024];
	int i;
	FILE * f;

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
		strcpy(listfile, argv[3]);
	} else {
		sprintf(listfile, "%s/mpqlist.txt", Dir);
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

	Mpq = new CMpq;

#if 0
	{
		FILE *fd;
		unsigned char* p;
		char buf[PATH_MAX];
		sprintf(buf, "%s/%s", archivedir, "stardat.mpq");
		OpenArchive(buf);
		p = ExtractEntry("rez\\minimap.bin");
		fd = fopen("minimap.bin", "wb");
		fwrite(p, EntrySize, 1, fd);
		fclose(fd);
		free(p);
		CloseArchive();
		exit(0);
	}
#endif

	printf("Extract from \"%s\" to \"%s\"\n", ArchiveDir, Dir);
	printf("Using mpq list file \"%s\"\n", listfile);
	printf("Please be patient, the data may take a couple of minutes to extract...\n\n");
	fflush(stdout);

	//for (i = 0; i <= 1; ++i) {
		Control *c;
		//printf("loop: %d\n", i);
		unsigned len;
		bool extracted = false;

		i = 1;
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

		for (u = 0; u < len; ++u) {
#ifdef DEBUG
			printf("%s:\n", c[u].File);
#endif
			switch (c[u].Type) {
				case F:
					if( !MpqFD )
					{	
						if( c[u].File )
						{
							if( !strncmp(c[u].ListFile,"remove-",7) ) {
								sprintf(buf, "%s/%s", Dir, c[u].ListFile);
							} else {
								sprintf(buf, "%s/%s", ArchiveDir, c[u].ListFile);
							}

							printf("Archive \"%s\"\n", buf);
							if (OpenArchive(buf) == -1) {
								printf("Could not open archive \"%s\", skipping\n\n", buf);

							} else {
								puts("");
								if (i == 0)
								{
		#ifdef DEBUG
									printf("%s:\n", "remove-stardat.mpq");
		#endif
									RawExtract("files\\stardat.mpq", "remove-stardat.mpq");
									Todo[0].ListFile = "remove-stardat.mpq";
								}
							}
						}
						else
						{
							fprintf(stderr, "Fatal error: Cannot extract data\n");
							return 1;
						}
					}
					break;
				case M:
					ConvertMap(c[u].ListFile, c[u].File, extracted);
					break;
				case R:
					ConvertRgb(c[u].ListFile, c[u].File);
					break;
				case T:
					ConvertTileset(c[u].ListFile, c[u].File);
					break;
				case G:
					ConvertGfx(c[u].ListFile, c[u].File, c[u].Arg1);
					break;
				case U:
					ConvertGfu(c[u].ListFile, c[u].File, c[u].Arg1);
					break;
				case I:
					ConvertWidgets(c[u].ListFile, c[u].File, c[u].Arg1);
					break;
				case N:
					ConvertFont(c[u].ListFile, c[u].File, 2, c[u].Arg1);
					break;
				case W:
					ConvertWav(c[u].ListFile, c[u].File, c[u].Arg1);
					break;
				case H:
					ConvertPcx(c[u].ListFile, c[u].File);
					break;
				case E:
					RawExtract(c[u].ListFile, c[u].File);
					break;
				default:
					break;
			}
		}

		if( MpqFD ) {
			CloseArchive();
		}

		if( !strncmp(c[0].ListFile,"remove-",7) ) {
			sprintf(buf,"%s/%s",Dir,c[0].ListFile);
			printf("removing \"%s\"\n",buf);
			unlink(buf);
		}
	//}
	
	delete Mpq;

	CreatePanels();

	sprintf(buf, "%s/extracted", Dir);
	f = fopen(buf, "w");
	fprintf(f, VERSION "\n");
	fclose(f);

	printf("DONE!\n");

	return 0;
}

//@}
