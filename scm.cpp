//       _________ __                 __                               
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/ 
//  ______________________                           ______________________
//			  T H E   W A R   B E G I N S
//	   Stratagus - A free fantasy real time strategy game engine
//
/**@name scm.c - The scm. */
//
//      (c) Copyright 2002-2006 by Jimmy Salmon
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
//	$Id$

//@{

/*----------------------------------------------------------------------------
--	Includes
----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mpq.h"

#ifdef _MSC_VER
#define strdup _strdup
#define DEBUG _DEBUG
#define PATH_MAX _MAX_PATH
#include <direct.h>
#include <io.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

/*----------------------------------------------------------------------------
--	Definitions
----------------------------------------------------------------------------*/

#if  defined(__i386__) || defined(__ia64__) || defined(WIN32) || \
    (defined(__alpha__) || defined(__alpha)) || \
     defined(__arm__) || \
    (defined(__mips__) && defined(__MIPSEL__)) || \
     defined(__SYMBIAN32__) || \
     defined(__x86_64__) || \
     defined(__LITTLE_ENDIAN__)
#ifdef __cplusplus
static inline unsigned short FetchLE16(unsigned char*& p) {
	unsigned short s = *(unsigned short*)p;
	p += 2;
	return s;
}
static inline unsigned int FetchLE32(unsigned char*& p) {
	unsigned int s = *(unsigned int*)p;
	p += 4;
	return s;
}
#else
#define FetchLE16(p) (*((unsigned short*)(p))); p += 2
#define FetchLE32(p) (*((unsigned int*)(p))); p += 4
#endif
#define AccessLE16(p) (*((unsigned short*)(p)))
#define AccessLE32(p) (*((unsigned int*)(p)))
#define ConvertLE16(v) (v)
#define ConvertLE32(v) (v)
#else
static inline unsigned short Swap16(unsigned short D) {
	return ((D << 8) | (D >> 8));
}
static inline unsigned int Swap32(unsigned int D) {
	return ((D << 24) | ((D << 8) & 0x00FF0000) | ((D >> 8) & 0x0000FF00) | (D >> 24));
}
#define FetchLE16(p) Swap16(*((unsigned short*)(p))); p += 2
#define FetchLE32(p) Swap32(*((unsigned int*)(p))); p += 4
#define AccessLE16(p) Swap16((*((unsigned short*)(p))))
#define AccessLE32(p) Swap32(*((unsigned int*)(p)))
#define ConvertLE16(v) Swap16(v)
#define ConvertLE32(v) Swap32(v)
#endif

#define FetchByte(p) (*((unsigned char*)(p))); ++p


#define SC_IsUnitMineral(x) ((x) == 176 || (x) == 177 || (x) == 178)  /// sc unit mineral
#define SC_UnitGeyser	    188	    /// sc unit geyser
#define SC_TerranSCV	    7	    /// terran scv
#define SC_ZergDrone	    41	    /// zerg drone
#define SC_ProtossProbe	    64	    /// protoss probe
#define SC_TerranCommandCenter	106 /// terran command center
#define SC_ZergHatchery	    131	    /// zerg hatchery
#define SC_ProtossNexus	    154	    /// protoss nexus
#define SC_StartLocation	214	    /// sc start location

#define PlayerMax 16

#define SettingsPresetMapDefault  -1  /// Special: Use map supplied
#define SettingsNumUnitsMapDefault  SettingsPresetMapDefault
#define SettingsNumUnits1    0


#ifdef DEBUG
#define DebugLevel1(x) printf(x)
#define DebugLevel2(x) printf(x)
#define _C_ ,
#else
#define DebugLevel1(x)
#define _C_
#endif


/*----------------------------------------------------------------------------
--  Variables
----------------------------------------------------------------------------*/

static char *chk_ptr;			/// FIXME: docu
static char *chk_endptr;			/// FIXME: docu

static char *TypeNames[] = { "nobody", NULL, NULL, "rescue-passive", NULL, "computer", "person", "neutral" };
static char *RaceNames[] = { "zerg", "terran", "protoss", NULL, "neutral" };

typedef struct WorldMap
{
	int MapWidth;
	int MapHeight;
	char *MapTerrainName;
	char *Description;
	int PlayerRace[PlayerMax];
	int PlayerType[PlayerMax];
	int *Tiles;
	struct { int X; int Y; } PlayerStart[PlayerMax];
} WorldMap;

char **TilesetWcNames;

/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

static void ExitFatal(int err)
{
	exit(-1);
}

/**
**  Read header
*/
static int ChkReadHeader(char *header, long *length)
{
	long len;

	if (chk_ptr >= chk_endptr) {
		return 0;
	}
	memcpy(header, chk_ptr, 4);
	chk_ptr += 4;
	memcpy(&len, chk_ptr, 4);
	chk_ptr += 4;
	*length = ConvertLE32(len);
	return 1;
}

/**
**  Read dword
*/
static int ChkReadDWord(void)
{
    unsigned int temp_int;

    memcpy(&temp_int, chk_ptr, 4);
    chk_ptr += 4;
    return ConvertLE32(temp_int);
}

/**
**  Read word
*/
static int ChkReadWord(void)
{
    unsigned short temp_short;

    memcpy(&temp_short, chk_ptr, 2);
    chk_ptr += 2;
    return ConvertLE16(temp_short);
}

/**
**  Read a byte from #chk_ptr.
**
**  @return  Next byte from #chk_ptr.
*/
static inline int ChkReadByte(void)
{
	int c = *((unsigned char *)chk_ptr);
	++chk_ptr;
    return c;
}

/**
**  Extract/uncompress entry.
**
**  @param mpqfd  The mpq file
**  @param entry  Returns the entry, NULL if not found
**  @param size   Returns the size of the entry
*/
static void ExtractMap(FILE *mpqfd, unsigned char **entry, int *size)
{
	int i;
	unsigned long max;
	int maxi;

	*entry = NULL;
	*size = 0;
	max = 0;
	maxi = 0;

	for (i = 0; i < MpqFileCount; ++i) {
		if (!strcmp("staredit\\scenario.chk", MpqFilenameTable + i * PATH_MAX)) {
			*size = MpqBlockTable[i * 4 + 2];
			*entry = (unsigned char *)malloc(*size + 1);
			MpqExtractTo(*entry, i, mpqfd);
			return;
		}
	}
	fprintf(stderr, "Could not find staredit\\scenario.chk");
}

/**
**	Load chk from buffer
**
**	@param chkdata	Buffer containing chk data
**	@param len	Length of chk buffer
**	@param map	The map
*/
void LoadChkFromBuffer(unsigned char *chkdata, int len, WorldMap *map)
{
	char header[5];
	long length;

	chk_ptr = (char *)chkdata;
	chk_endptr = chk_ptr + len;
	header[4] = '\0';

	while (ChkReadHeader(header, &length)) {

		//
		//	SCM version
		//
		if (!memcmp(header, "VER ", 4)) {
			if (length == 2) {
				int v;
				v = ChkReadWord();
				continue;
			}
			DebugLevel1("Wrong VER  length\n");
		}

		//
		//	SCM version additional information
		//
		if (!memcmp(header, "IVER", 4)) {
			if (length == 2) {
				int v;
				v = ChkReadWord();
				continue;
			}
			DebugLevel1("Wrong IVER length\n");
		}

		//
		//	SCM version additional information
		//
		if (!memcmp(header, "IVE2", 4)) {
			if (length == 2) {
				int v;
				v = ChkReadWord();
				continue;
			}
			DebugLevel1("Wrong IVE2 length\n");
		}

		//
		//	Verification code
		//
		if (!memcmp(header, "VCOD", 4)) {
			if (length == 1040) {
				chk_ptr += 1040;
				continue;
			}
			DebugLevel1("Wrong VCOD length\n");
		}

		//
		//	Specifies the owner of the player
		//
		if (!memcmp(header, "IOWN", 4)) {
			if (length == 12) {
				chk_ptr += 12;
				continue;
			}
			DebugLevel1("Wrong IOWN length\n");
		}

		//
		//	Specifies the owner of the player, same as IOWN but with 0 added
		//
		if (!memcmp(header, "OWNR", 4)) {
			if (length == 12) {
				for (int i = 0; i < 12; ++i) {
					int p = ChkReadByte();
					map->PlayerType[i] = p;
					if (p != 0 && p != 3 && p != 5 && p != 6 && p != 7) {
						DebugLevel1("Wrong OWNR type: %d\n" _C_ p);
						map->PlayerType[i] = 0;
					}
				}
				continue;
			}
			DebugLevel1("Wrong OWNR length\n");
		}

		//
		//	Terrain type
		//
		if (!memcmp(header, "ERA ", 4)) {
			if (length == 2) {
				int t;
				char *tilesets[] = { "badlands", "platform", "install",
					"ashworld", "jungle", "desert", "arctic", "twilight" };

				t = ChkReadWord();
				map->MapTerrainName = strdup(tilesets[t]);
				continue;
			}
			DebugLevel1("Wrong ERA  length\n");
		}

		//
		//	Dimensions
		//
		if (!memcmp(header, "DIM ", 4)) {
			if (length == 4) {
				map->MapWidth = ChkReadWord();
				map->MapHeight = ChkReadWord();
				continue;
			}
			DebugLevel1("Wrong DIM  length\n");
		}

		//
		//	Identifies race of each player
		//
		if (!memcmp(header, "SIDE", 4)) {
			if (length == 12) {
				int i;
				int v;

				for (i = 0; i < 12; ++i) {
					v = ChkReadByte();
					if (v == 5) { // user selected race
						v = 1;
					}
					if (v > 2 && v != 4) {
						DebugLevel1("Unknown race %d\n" _C_ v);
						v = 0;
					}
					map->PlayerRace[i] = v;
				}
				continue;
			}
			DebugLevel1("Wrong SIDE length\n");
		}

		//
		//	Graphical tile map
		//
		if (!memcmp(header, "MTXM", 4)) {
			if (length == map->MapWidth * map->MapHeight * 2) {
				map->Tiles = (int *)malloc(map->MapWidth * map->MapHeight * sizeof(int));
				for (int h = 0; h < map->MapHeight; ++h) {
					for (int w = 0; w < map->MapWidth; ++w) {
						int v = ConvertLE16(((unsigned short *)chk_ptr)[h * map->MapWidth + w]);
						if (v > 10000) {
							v = v;
						}
						map->Tiles[h * map->MapWidth + w] = v;
					}
				}
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong MTXM length\n");
		}

		//
		//	Player unit restrictions
		//
		if (!memcmp(header, "PUNI", 4)) {
			if (length == 228*12 + 228 + 228*12) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong PUNI length\n");
		}

		//
		//	Player upgrade restrictions
		//
		if (!memcmp(header, "UPGR", 4)) {
			if (length == 46*12 + 46*12 + 46 + 46 + 46*12) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong UPGR length\n");
		}

		//
		//	Extended upgrades
		//
		if (!memcmp(header, "PUPx", 4)) {
			if (length == 61*12 + 61*12 + 61 + 61 + 61*12) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong PUPx length\n");
		}

		//
		//	Player technology restrictions
		//
		if (!memcmp(header, "PTEC", 4)) {
			if (length == 24*12 + 24*12 + 24 + 24 + 24*12) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong PTEC length\n");
		}

		//
		//	Extended player technology restrictions
		//
		if (!memcmp(header, "PTEx", 4)) {
			if (length == 44*12 + 44*12 + 44 + 44 + 44*12) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong PTEx length\n");
		}

		//
		//	Units
		//
		if (!memcmp(header, "UNIT", 4)) {
			int i;

//		    if (length==) {
			if (length % 36 == 0) {
				int x, y;
				int t;
				int f1, f2;
				int o;
				int hpp, shp;
				int ep;
				int res;
				int nh;
				int st;
//				int s;
//				int v;
//				Unit *unit;
//				UnitType *type;

				while (length > 0) {
					chk_ptr += 4;	// unknown
					x = ChkReadWord();	// x coordinate
					y = ChkReadWord();	// y coordinate
					t = ChkReadWord();	// unit type
					chk_ptr += 2;	// unknown
					f1 = ChkReadWord();	// special properties flag
					f2 = ChkReadWord();	// valid elements
					o = ChkReadByte();	// owner
					hpp = ChkReadByte();// hit point %
					shp = ChkReadByte();// shield point %
					ep = ChkReadByte();	// energy point %
					res = ChkReadDWord(); // resource amount
					nh = ChkReadWord();	// num units in hanger
					st = ChkReadWord();	// state flags
					chk_ptr += 8;	// unknown

					length -= 36;

					// FIXME: remove
//				    type = UnitTypeByWcNum(t);
//				    x = (x - 32 * type->TileWidth / 2) / 32;
//				    y = (y - 32 * type->TileHeight / 2) / 32;

					if (t == SC_StartLocation) {
						map->PlayerStart[o].X = x;
						map->PlayerStart[o].Y = y;
#if 0
						Players[o].StartX = MapOffsetX + x;
						Players[o].StartY = MapOffsetY + y;
						if (GameSettings.NumUnits == SettingsNumUnits1 && Players[o].Type != PlayerNobody) {
							if (t == SC_StartLocation) {
								if (Players[o].Race == 0) {
									t = SC_ZergDrone;
								} else if (Players[o].Race == 1) {
									t = SC_TerranSCV;
								} else {
									t = SC_ProtossProbe;
								}
							}
							v = 1;
							goto pawn;
						}
#endif
					} else {
#if 0
						if (GameSettings.NumUnits == SettingsNumUnitsMapDefault ||
								SC_IsUnitMineral(t) || t == SC_UnitGeyser) {
pawn:
							if (!SC_IsUnitMineral(t) && t != SC_UnitGeyser) {
								if ((s = GameSettings.Presets[o].Race) != SettingsPresetMapDefault) {
									// FIXME: change races
								}
							}
							if (Players[o].Type != PlayerNobody) {
								unit = MakeUnitAndPlace(MapOffsetX + x, MapOffsetY + y, UnitTypeByWcNum(t), &Players[o]);
								if (unit->Type->GivesResource) {
									DebugCheck(!v);
									unit->Value = v;
								} else {
									// active/inactive AI units!!
									// Johns: it is better to have active buildings
									if (!unit->Type->Building) {
#if 0
										unit->Active = !v;
#endif
									}
								}
								UpdateForNewUnit(unit,0);
							}
						}
#endif
					}
				}

				// If the player has no units use 4 peasants and a town
				// hall as default
				for (i = 0; i < 12; ++i) {
#if 0
					if (Players[i].Type == PlayerPerson || Players[i].Type == PlayerComputer) {
						if (Players[i].TotalUnits == 0) {
							int j;
							int t1;
							Unit *unit;
							UnitType *type;

							if (Players[i].Race == 0) {
								t1 = SC_ZergDrone;
								type = UnitTypeByWcNum(SC_ZergHatchery);
							} else if (Players[i].Race == 1) {
								t1 = SC_TerranSCV;
								type = UnitTypeByWcNum(SC_TerranCommandCenter);
							} else {
								t1 = SC_ProtossProbe;
								type = UnitTypeByWcNum(SC_ProtossNexus);
							}
							unit = MakeUnitAndPlace(Players[i].StartX, Players[i].StartY,
								type, &Players[i]);
							UpdateForNewUnit(unit, 0);
							for (j = 0; j < 4; ++j) {
								unit = MakeUnit(UnitTypeByWcNum(t1), &Players[i]);
								unit->X = Players[i].StartX;
								unit->Y = Players[i].StartY;
								DropOutOnSide(unit, LookingS, type->TileWidth, type->TileHeight);
								UpdateForNewUnit(unit, 0);
							}
						}
					}
#endif
				}

				continue;
			}
			DebugLevel1("Wrong UNIT length\n");
		}

		//
		//	Extended units
		//
		if (!memcmp(header, "UNIx", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong UNIx length\n");
		}

		//
		//	Isometric tile mapping
		//
		if (!memcmp(header, "ISOM", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong ISOM length\n");
		}

		//
		//
		//
		if (!memcmp(header, "TILE", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong TILE length\n");
		}

		//
		//	Doodad map used by the editor
		//
		if (!memcmp(header, "DD2 ", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong DD2  length\n");
		}

		//
		//	Thingys
		//
		if (!memcmp(header, "THG2", 4)) {
			if (length % 10 == 0) {
				while (length > 0) {
					int n;
					int x;
					int y;
					int pl;
					int fl;
					char buf[30];
//				    char **unit;
//				    UnitType *type;

					n = ChkReadWord();    // unit number of the thingy
					x = ChkReadWord();    // x coordinate
					y = ChkReadWord();    // y coordinate
					pl = ChkReadByte();   // player number of owner
					ChkReadByte();	// unknown
					fl = ChkReadWord();   // flags
					length -= 10;

					sprintf(buf, "%d", n);
//				    unit = (char **)hash_find(TheMap.Tileset->ItemsHash, buf);
#ifdef DEBUG
//				    if (!unit) {
//						fprintf(stderr,"THG2 n=%d (%d,%d)\n",n,x,y);
//						continue;
//				    }
#endif

					// FIXME: remove
//				    type = UnitTypeByIdent(*unit);
//				    x = (x - 32 * type->TileWidth / 2) / 32;
//				    y = (y - 32 * type->TileHeight / 2) / 32;

//				    MakeUnitAndPlace(MapOffsetX + x, MapOffsetY + y, type, &Players[15]);
				}
				continue;
			}
			DebugLevel1("Wrong THG2 length\n");
		}

		//
		//
		//
		if (!memcmp(header, "MASK", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong MASK length\n");
		}

		//
		//	Strings
		//
		if (!memcmp(header, "STR ", 4)) {
//		    if (length==) {
			if (1) {
#if 1
				int i;
				short s;

				for (i = 0; i < 1024; ++i) {
					s = ((short*)chk_ptr)[i + 1];
					if (s != 2050) {
						printf("STR %d - %s\n", i, chk_ptr + s);
					}
				}
#endif
//				strcpy(map->Description, chk_ptr+2051);
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong STR  length\n");
		}

		//
		//
		//
		if (!memcmp(header, "UPRP", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong UPRP length\n");
		}

		//
		//
		//
		if (!memcmp(header, "UPUS", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong UPUS length\n");
		}

		//
		//
		//
		if (!memcmp(header, "MRGN", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong MRGN length\n");
		}

		//
		//	Triggers
		//
		if (!memcmp(header, "TRIG", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong TRIG length\n");
		}

		//
		//	Mission briefing
		//
		if (!memcmp(header, "MBRF", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong MBRF length\n");
		}

		//
		//
		//
		if (!memcmp(header, "SPRP", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong SPRP length\n");
		}

		//
		//
		//
		if (!memcmp(header, "FORC", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong FORC length\n");
		}

		//
		//
		//
		if (!memcmp(header, "WAV ", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong WAV  length\n");
		}

		//
		//
		//
		if (!memcmp(header, "UNIS", 4)) {
//		    if (length==) {
			if (1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong UNIS length\n");
		}

		//
		//
		//
		if (!memcmp(header, "UPGS", 4)) {
			if (length == 46*1 + 46*2 + 46*2 + 46*2 + 46*2 + 46*2 + 46*2) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong UPGS length\n");
		}

		//
		//
		//
		if (!memcmp(header, "UPGx", 4)) {
			if (length == 61*1 + 61*2 + 61*2 + 61*2 + 61*2 + 61*2 + 61*2 + 1) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong UPGx length\n");
		}

		//
		//
		//
		if (!memcmp(header, "TECS", 4)) {
			if (length == 24*1 + 24*2 + 24*2 + 24*2 + 24*2) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong TECS length\n");
		}

		//
		//
		//
		if (!memcmp(header, "TECx", 4)) {
			if (length == 44*1 + 44*2 + 44*2 + 44*2 + 44*2) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong TECx length\n");
		}

		//
		//
		//
		if (!memcmp(header, "SWNM", 4)) {
			if (length == 256 * 4) {
				chk_ptr += length;
				continue;
			}
			DebugLevel1("Wrong SWNM length\n");
		}

		DebugLevel2("Unsupported Section: %4.4s\n" _C_ header);
		chk_ptr += length;
	}
}

/**
**  Load scm
**
**  @param scm  Name of the scm file
**  @param map  The map
*/
void LoadScm(const char *scm, WorldMap *map)
{
	unsigned char *chkdata;
	char buf[1024];
	FILE *fpMpq;
	int chklen;

	if (!(fpMpq = fopen(scm, "rb"))) {
		fprintf(stderr, "Try ./path/name\n");
		sprintf(buf, "scm: fopen(%s)", scm);
		perror(buf);
		ExitFatal(-1);
	}

	if (MpqReadInfo(fpMpq)) {
		fprintf(stderr, "MpqReadInfo failed\n");
		ExitFatal(-1);
	}

	ExtractMap(fpMpq, &chkdata, &chklen);

	fclose(fpMpq);
	if (!chkdata) {
		fprintf(stderr, "Could not extract map in %s\n", scm);
		ExitFatal(-1);
	}

	LoadChkFromBuffer(chkdata, chklen, map);

	CleanMpq();
}

/**
**	Clean scm module.
*/
void CleanScm(void)
{
}

/**
**	Clean chk module.
*/
void CleanChk(void)
{
}


static void SaveSMP(const char *name, WorldMap *map)
{
	FILE *fd;

	fd = fopen(name, "wb");

	fprintf(fd, "DefinePlayerTypes(");
	bool first = true;
	for (int i = 0; i < PlayerMax; ++i) {
		if (TypeNames[map->PlayerType[i]]) {
			if (first) {
				first = false;
			} else {
				fprintf(fd, ",");
			}
			fprintf(fd, "\"%s\"", TypeNames[map->PlayerType[i]]);
		}
	}
	fprintf(fd, ")\n");
	fprintf(fd, "PresentMap(\"%s\", %d, %d, %d, %d)\n", "none", 2, map->MapWidth, map->MapHeight, 0);
	strcpy(strrchr(name, '.') + 1, "sms");
	fprintf(fd, "DefineMapSetup(\"%s\")\n", name);

	fclose(fd);
}

static void SaveSMS(const char *name, WorldMap *map)
{
	FILE *fd;
	int i;

	fd = fopen(name, "wb");

	for (i = 0; i < PlayerMax; ++i) {
		fprintf(fd, "SetStartView(%d, %d, %d)\n", i, map->PlayerStart[i].X, map->PlayerStart[i].Y);
		fprintf(fd, "SetPlayerData(%d, \"Resources\", \"gold\", %d)\n", i, 0);
		fprintf(fd, "SetPlayerData(%d, \"Resources\", \"wood\", %d)\n", i, 0);
		fprintf(fd, "SetPlayerData(%d, \"Resources\", \"oil\", %d)\n", i, 0);
		fprintf(fd, "SetPlayerData(%d, \"RaceName\", \"%s\")\n", i, RaceNames[map->PlayerRace[i]]);
	}

	fprintf(fd, "\n\n");

	fprintf(fd, "LoadTileModels(\"scripts/tilesets/%s.lua\")\n", map->MapTerrainName);

	fprintf(fd, "\n\n");

	// SetTile(t, x, y);
	for (int h = 0; h < map->MapHeight; ++h) {
		for (int w = 0; w < map->MapWidth; ++w) {
			fprintf(fd, "SetTile(%d, %d, %d)\n", map->Tiles[h * map->MapWidth + w], w, h);
		}
	}

	fprintf(fd, "\n\n");

	// units
	fprintf(fd,
		"unit= CreateUnit(\"unit-terran-scv\", 0, {270, 263})\n"
		"unit= CreateUnit(\"unit-terran-scv\", 1, {470, 463})\n"
		"unit= CreateUnit(\"unit-terran-scv\", 2, {60, 358})\n"
		"unit= CreateUnit(\"unit-terran-scv\", 3, {160, 58})\n"
	);

	fclose(fd);
}

static void SaveMap(const char *name, WorldMap *map)
{
	char *mapname;
	
	mapname = strdup(name);
	strcpy(strrchr(mapname, '.') + 1, "smp");
	SaveSMP(mapname, map);

	strcpy(strrchr(mapname, '.') + 1, "sms");
	SaveSMS(mapname, map);

	free(mapname);
}

void ConvertScm(const char *name)
{
    WorldMap map;
    memset(&map, 0, sizeof(map));
    LoadScm(name, &map);
	SaveMap(name, &map);
}
