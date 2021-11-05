/*
 * Chk.cpp
 *
 *      Author: Andreas Volz
 */

#include "scm.h"
#include "Chk.h"
#include "WorldMap.h"
#include "endian.h"

// C++
#include <cstring>
#include <cstdint>
#include <stdlib.h>

Chk::Chk()
{

}

Chk::~Chk()
{

}

static char *chk_ptr;			/// FIXME: docu
static char *chk_endptr;			/// FIXME: docu

static int ChkReadHeader(char *header, int32_t *length)
{
	int32_t len;

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
**	Load chk from buffer
**
**	@param chkdata	Buffer containing chk data
**	@param len	Length of chk buffer
**	@param map	The map
*/
void Chk::loadFromBuffer(unsigned char *chkdata, int len, WorldMap *map)
{
	char header[5];
	int32_t length;

	chk_ptr = (char *)chkdata;
	chk_endptr = chk_ptr + len;
	header[4] = '\0';

	while (ChkReadHeader(header, &length)) {

		//
		//	SCM version
		//
		if (!memcmp(header, "VER ", 4)) {
			if (length == 2) {
				ChkReadWord();
				continue;
			}
			DebugLevel1("Wrong VER  length\n");
		}

		//
		//	SCM version additional information
		//
		if (!memcmp(header, "IVER", 4)) {
			if (length == 2) {
				ChkReadWord();
				continue;
			}
			DebugLevel1("Wrong IVER length\n");
		}

		//
		//	SCM version additional information
		//
		if (!memcmp(header, "IVE2", 4)) {
			if (length == 2) {
				ChkReadWord();
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
				const char *tilesets[] = { "badlands", "platform", "install",
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
					if (v > 2 && v != 4 && v != 7) {
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
						/*if (v > 10000) {
							v = v;
						}*/
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
			if (length % 36 == 0) {
				while (length > 0) {
					Unit unit;

					chk_ptr += 4;	// unknown
					unit.X = ChkReadWord();	// x coordinate
					unit.Y = ChkReadWord();	// y coordinate
					unit.Type = ChkReadWord();	// unit type
					chk_ptr += 2;	// unknown
					unit.Properties = ChkReadWord();	// special properties flag
					unit.ValidElements = ChkReadWord();	// valid elements
					unit.Player = ChkReadByte();	// owner
					unit.HitPointsPercent = ChkReadByte();// hit point %
					unit.ShieldPointsPercent = ChkReadByte();// shield point %
					unit.EnergyPointsPercent = ChkReadByte();	// energy point %
					unit.ResourceAmount = ChkReadDWord(); // resource amount
					unit.NumUnitsIn = ChkReadWord();	// num units in hanger
					unit.StateFlags = ChkReadWord();	// state flags
					chk_ptr += 8;	// unknown

					length -= 36;

					if (unit.Player == 11) { // neutral player
						unit.Player = PlayerMax - 1;
					}

					unit.X /= 32;
					unit.Y /= 32;

//				    type = UnitTypeByWcNum(t);
//				    x = (x - 32 * type->TileWidth / 2) / 32;
//				    y = (y - 32 * type->TileHeight / 2) / 32;

					if (unit.Type == SC_StartLocation) {
						map->PlayerStart[unit.Player].X = unit.X;
						map->PlayerStart[unit.Player].Y = unit.Y;
					} else {
						map->Units.push_back(unit);
					}
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
					char buf[30];
//				    char **unit;
//				    UnitType *type;

					n = ChkReadWord();    // unit number of the thingy
					ChkReadWord();    // x coordinate
					ChkReadWord();    // y coordinate
					ChkReadByte();   // player number of owner
					ChkReadByte();	// unknown
					ChkReadWord();   // flags
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
			int i;
			unsigned short num;
			unsigned short s;
			char *cptr = chk_ptr;

			num = ChkReadWord();
			for (i = 0; i < num; ++i) {
				s = ChkReadWord();
				map->Strings.push_back(cptr + s);
			}
			map->Description = strdup("none");
			chk_ptr += length - 2050;
			continue;
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
			if ((length / 20) * 20 == length) {
				while (length > 0) {
					Location location;
					location.StartX = ChkReadDWord();
					location.StartY = ChkReadDWord();
					location.EndX = ChkReadDWord();
					location.EndY = ChkReadDWord();
					location.StringNumber = ChkReadWord();
					location.Flags = ChkReadWord();
					map->Locations.push_back(location);
					length -= 20;
				}
				continue;
			}
			DebugLevel1("Wrong MRGN length\n");
		}

		//
		//	Triggers
		//
		if (!memcmp(header, "TRIG", 4)) {
			if ((length / 2400) * 2400 == length) {
				int i;

				while (length > 0) {
					Trigger trigger;
					for (i = 0; i < 16; ++i) {
						trigger.TriggerConditions[i].Location = ChkReadDWord();
						trigger.TriggerConditions[i].Group = ChkReadDWord();
						trigger.TriggerConditions[i].QualifiedNumber = ChkReadDWord();
						trigger.TriggerConditions[i].UnitType = ChkReadWord();
						trigger.TriggerConditions[i].CompType = ChkReadByte();
						trigger.TriggerConditions[i].Condition = ChkReadByte();
						trigger.TriggerConditions[i].ResType = ChkReadByte();
						trigger.TriggerConditions[i].Flags = ChkReadByte();
						chk_ptr += 2;
					}
					for (i = 0; i < 64; ++i) {
						trigger.TriggerActions[i].Source = ChkReadDWord();
						trigger.TriggerActions[i].TriggerNumber = ChkReadDWord();
						trigger.TriggerActions[i].WavNumber = ChkReadDWord();
						trigger.TriggerActions[i].Time = ChkReadDWord();
						trigger.TriggerActions[i].FirstGroup = ChkReadDWord();
						trigger.TriggerActions[i].SecondGroup = ChkReadDWord();
						trigger.TriggerActions[i].Status = ChkReadWord();
						trigger.TriggerActions[i].Action = ChkReadByte();
						trigger.TriggerActions[i].NumUnits = ChkReadByte();
						trigger.TriggerActions[i].ActionFlags = ChkReadByte();
						chk_ptr += 3;
					}
					chk_ptr += 32;
					map->Triggers.push_back(trigger);
					length -= 2400;
				}
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
