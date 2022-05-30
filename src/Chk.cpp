/*
 * Chk.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include <luagen.h>
#include "Chk.h"
#include "WorldMap.h"
#include "endian.h"
#include "Hurricane.h"
#include "FileUtil.h"
#include "Logger.h"

// system
#include <cstring>
#include <cstdint>
#include <stdlib.h>
#include <algorithm>
#include <iostream>


#ifdef DEBUG
#define DebugLevel1(x) printf(x)
#define DebugLevel2(x) printf(x)
#define _C_ ,
#else
#define DebugLevel1(x)
#define DebugLevel2(x)
#define _C_
#endif

using namespace std;

static Logger logger = Logger("startool.Chk");

static const char *TypeNames[] =
{
  "nobody", NULL, NULL, "rescue-passive", NULL, "computer", "person",
  "neutral"
};
static const char *RaceNames[] =
{ "zerg", "terran", "protoss", NULL, "neutral" };

Chk::Chk(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane),
  map(new WorldMap())
{

}

Chk::~Chk()
{
  FreeMap();
}

static char *chk_ptr;			/// FIXME: docu
static char *chk_endptr;			/// FIXME: docu

static int ChkReadHeader(char *header, int32_t *length)
{
  int32_t len;

  if (chk_ptr >= chk_endptr)
  {
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
  int c = *((unsigned char *) chk_ptr);
  ++chk_ptr;
  return c;
}

void Chk::setUnitNames(const std::vector<std::string> &unitNames)
{
  mUnitNames = unitNames;
}

void Chk::loadFromBuffer(unsigned char *chkdata, int len)
{
  char header[5];
  int32_t length;

  chk_ptr = (char *) chkdata;
  chk_endptr = chk_ptr + len;
  header[4] = '\0';

  while (ChkReadHeader(header, &length))
  {

    //
    //	SCM version
    //
    if (!memcmp(header, "VER ", 4))
    {
      if (length == 2)
      {
        ChkReadWord();
        continue;
      }
      DebugLevel1("Wrong VER  length\n");
    }

    //
    //	SCM version additional information
    //
    if (!memcmp(header, "IVER", 4))
    {
      if (length == 2)
      {
        ChkReadWord();
        continue;
      }
      DebugLevel1("Wrong IVER length\n");
    }

    //
    //	SCM version additional information
    //
    if (!memcmp(header, "IVE2", 4))
    {
      if (length == 2)
      {
        ChkReadWord();
        continue;
      }
      DebugLevel1("Wrong IVE2 length\n");
    }

    //
    //	Verification code
    //
    if (!memcmp(header, "VCOD", 4))
    {
      if (length == 1040)
      {
        chk_ptr += 1040;
        continue;
      }
      DebugLevel1("Wrong VCOD length\n");
    }

    //
    //	Specifies the owner of the player
    //
    if (!memcmp(header, "IOWN", 4))
    {
      if (length == 12)
      {
        chk_ptr += 12;
        continue;
      }
      DebugLevel1("Wrong IOWN length\n");
    }

    //
    //	Specifies the owner of the player, same as IOWN but with 0 added
    //
    if (!memcmp(header, "OWNR", 4))
    {
      if (length == 12)
      {
        for (int i = 0; i < 12; ++i)
        {
          int p = ChkReadByte();
          map->PlayerType[i] = p;
          if (p != 0 && p != 3 && p != 5 && p != 6 && p != 7)
          {
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
    if (!memcmp(header, "ERA ", 4))
    {
      if (length == 2)
      {
        int t;
        const char *tilesets[] =
        {
          "badlands", "platform", "install", "ashworld", "jungle", "desert",
          "arctic", "twilight"
        };

        t = ChkReadWord();
        map->MapTerrainName = strdup(tilesets[t]);
        continue;
      }
      DebugLevel1("Wrong ERA  length\n");
    }

    //
    //	Dimensions
    //
    if (!memcmp(header, "DIM ", 4))
    {
      if (length == 4)
      {
        map->MapWidth = ChkReadWord();
        map->MapHeight = ChkReadWord();
        continue;
      }
      DebugLevel1("Wrong DIM  length\n");
    }

    //
    //	Identifies race of each player
    //
    if (!memcmp(header, "SIDE", 4))
    {
      if (length == 12)
      {
        int i;
        int v;

        for (i = 0; i < 12; ++i)
        {
          v = ChkReadByte();
          if (v == 5)
          {
            // user selected race
            v = 1;
          }
          if (v > 2 && v != 4 && v != 7)
          {
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
    if (!memcmp(header, "MTXM", 4))
    {
      if (length == map->MapWidth * map->MapHeight * 2)
      {
        map->Tiles = (int *) malloc(
                       map->MapWidth * map->MapHeight * sizeof(int));
        for (int h = 0; h < map->MapHeight; ++h)
        {
          for (int w = 0; w < map->MapWidth; ++w)
          {
            int v = ConvertLE16(
                      ((unsigned short *)chk_ptr)[h * map->MapWidth + w]);
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
    if (!memcmp(header, "PUNI", 4))
    {
      if (length == 228 * 12 + 228 + 228 * 12)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong PUNI length\n");
    }

    //
    //	Player upgrade restrictions
    //
    if (!memcmp(header, "UPGR", 4))
    {
      if (length == 46 * 12 + 46 * 12 + 46 + 46 + 46 * 12)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong UPGR length\n");
    }

    //
    //	Extended upgrades
    //
    if (!memcmp(header, "PUPx", 4))
    {
      if (length == 61 * 12 + 61 * 12 + 61 + 61 + 61 * 12)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong PUPx length\n");
    }

    //
    //	Player technology restrictions
    //
    if (!memcmp(header, "PTEC", 4))
    {
      if (length == 24 * 12 + 24 * 12 + 24 + 24 + 24 * 12)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong PTEC length\n");
    }

    //
    //	Extended player technology restrictions
    //
    if (!memcmp(header, "PTEx", 4))
    {
      if (length == 44 * 12 + 44 * 12 + 44 + 44 + 44 * 12)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong PTEx length\n");
    }

    //
    //	Units
    //
    if (!memcmp(header, "UNIT", 4))
    {
      if (length % 36 == 0)
      {
        while (length > 0)
        {
          Unit unit;

          chk_ptr += 4;	// unknown
          unit.X = ChkReadWord();	// x coordinate
          unit.Y = ChkReadWord();	// y coordinate
          unit.Type = ChkReadWord();	// unit type
          chk_ptr += 2;	// unknown
          unit.Properties = ChkReadWord();	// special properties flag
          unit.ValidElements = ChkReadWord();	// valid elements
          unit.Player = ChkReadByte();	// owner
          unit.HitPointsPercent = ChkReadByte();	// hit point %
          unit.ShieldPointsPercent = ChkReadByte();	// shield point %
          unit.EnergyPointsPercent = ChkReadByte();	// energy point %
          unit.ResourceAmount = ChkReadDWord(); // resource amount
          unit.NumUnitsIn = ChkReadWord();	// num units in hanger
          unit.StateFlags = ChkReadWord();	// state flags
          chk_ptr += 8;	// unknown

          length -= 36;

          if (unit.Player == 11)
          {
            // neutral player
            unit.Player = PlayerMax - 1;
          }

          unit.X /= 32;
          unit.Y /= 32;

//				    type = UnitTypeByWcNum(t);
//				    x = (x - 32 * type->TileWidth / 2) / 32;
//				    y = (y - 32 * type->TileHeight / 2) / 32;

          if (unit.Type == SC_StartLocation)
          {
            map->PlayerStart[unit.Player].X = unit.X;
            map->PlayerStart[unit.Player].Y = unit.Y;
          }
          else
          {
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
    if (!memcmp(header, "UNIx", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong UNIx length\n");
    }

    //
    //	Isometric tile mapping
    //
    if (!memcmp(header, "ISOM", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong ISOM length\n");
    }

    //
    //
    //
    if (!memcmp(header, "TILE", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong TILE length\n");
    }

    //
    //	Doodad map used by the editor
    //
    if (!memcmp(header, "DD2 ", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong DD2  length\n");
    }

    //
    //	Thingys
    //
    if (!memcmp(header, "THG2", 4))
    {
      if (length % 10 == 0)
      {
        while (length > 0)
        {
          int n;

          n = ChkReadWord();    // unit number of the thingy
          ChkReadWord();    // x coordinate
          ChkReadWord();    // y coordinate
          ChkReadByte();   // player number of owner
          ChkReadByte();	// unknown
          ChkReadWord();   // flags
          length -= 10;

          string thingyName = mUnitNames[n];

          //cout << "Thingy: "  << thingyName << endl;

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
    if (!memcmp(header, "MASK", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong MASK length\n");
    }

    //
    //	Strings
    //
    if (!memcmp(header, "STR ", 4))
    {
      int i;
      unsigned short num;
      unsigned short s;
      char *cptr = chk_ptr;

      num = ChkReadWord();
      for (i = 0; i < num; ++i)
      {
        s = ChkReadWord();

        string str(cptr + s);

        // replace incompatible line endings of multiline strings
        // TODO: this might look ugle, but doesn't crash the LUA function at least
        // TODO: need to find a good way when the GUI supports that... maybe remove all multible spaces...
        str.erase(remove(str.begin(), str.end(), '\r'), str.end());
        str.erase(remove(str.begin(), str.end(), '\n'), str.end());

        map->Strings.push_back(str);
      }
      map->Description = strdup("none");
      chk_ptr += length - 2050;
      continue;
    }

    //
    //
    //
    if (!memcmp(header, "UPRP", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong UPRP length\n");
    }

    //
    //
    //
    if (!memcmp(header, "UPUS", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong UPUS length\n");
    }

    //
    //
    //
    if (!memcmp(header, "MRGN", 4))
    {
      if ((length / 20) * 20 == length)
      {
        while (length > 0)
        {
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
    if (!memcmp(header, "TRIG", 4))
    {
      if ((length / 2400) * 2400 == length)
      {
        int i;

        while (length > 0)
        {
          Trigger trigger;
          for (i = 0; i < 16; ++i)
          {
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
          for (i = 0; i < 64; ++i)
          {
            trigger.TriggerActions[i].Source = ChkReadDWord() - 1;
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
    if (!memcmp(header, "MBRF", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong MBRF length\n");
    }

    //
    //
    //
    if (!memcmp(header, "SPRP", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong SPRP length\n");
    }

    //
    //
    //
    if (!memcmp(header, "FORC", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong FORC length\n");
    }

    //
    //
    //
    if (!memcmp(header, "WAV ", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong WAV  length\n");
    }

    //
    //
    //
    if (!memcmp(header, "UNIS", 4))
    {
//		    if (length==) {
      if (1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong UNIS length\n");
    }

    //
    //
    //
    if (!memcmp(header, "UPGS", 4))
    {
      if (length
          == 46 * 1 + 46 * 2 + 46 * 2 + 46 * 2 + 46 * 2 + 46 * 2 + 46 * 2)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong UPGS length\n");
    }

    //
    //
    //
    if (!memcmp(header, "UPGx", 4))
    {
      if (length
          == 61 * 1 + 61 * 2 + 61 * 2 + 61 * 2 + 61 * 2 + 61 * 2 + 61 * 2 + 1)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong UPGx length\n");
    }

    //
    //
    //
    if (!memcmp(header, "TECS", 4))
    {
      if (length == 24 * 1 + 24 * 2 + 24 * 2 + 24 * 2 + 24 * 2)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong TECS length\n");
    }

    //
    //
    //
    if (!memcmp(header, "TECx", 4))
    {
      if (length == 44 * 1 + 44 * 2 + 44 * 2 + 44 * 2 + 44 * 2)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong TECx length\n");
    }

    //
    //
    //
    if (!memcmp(header, "SWNM", 4))
    {
      if (length == 256 * 4)
      {
        chk_ptr += length;
        continue;
      }
      DebugLevel1("Wrong SWNM length\n");
    }

    DebugLevel2("Unsupported Section: %4.4s\n" _C_ header);
    chk_ptr += length;
  }
}

/*----------------------------------------------------------------------------
 --  Variables
 ----------------------------------------------------------------------------*/

#define VERSION "1.0"

/*----------------------------------------------------------------------------
 --  Functions
 ----------------------------------------------------------------------------*/

void Chk::SaveSMP(Storage storage)
{
  FILE *fd;

  storage.setFilename(storage.getFilename() + "smp");

  CheckPath(storage.getFullPath());

  fd = fopen(storage.getFullPath().c_str(), "wb");

  fprintf(fd, "-- Stratagus Map Presentation\n");
  fprintf(fd, "-- File generated automatically from scmconvert V" VERSION "\n");
  fprintf(fd, "\n");

  fprintf(fd, "DefinePlayerTypes(");
  bool first = true;
  for (int i = 0; i < PlayerMax; ++i)
  {
    if (TypeNames[map->PlayerType[i]])
    {
      if (first)
      {
        first = false;
      }
      else
      {
        fprintf(fd, ",");
      }
      fprintf(fd, "\"%s\"", TypeNames[map->PlayerType[i]]);
    }
  }
  fprintf(fd, ")\n");
  fprintf(fd, "PresentMap(\"%s\", %d, %d, %d, %d)\n", map->Description, 2,
          map->MapWidth, map->MapHeight, 0);

  fclose(fd);
}

void Chk::SaveTrigger(FILE *fd, Trigger *trigger)
{
  int i;
  TriggerCondition *c;
  TriggerAction *a;

  // Conditions
  for (i = 0; i < 16; ++i)
  {
    c = &trigger->TriggerConditions[i];
    if (c->Condition == 0)
    {
      break;
    }
    switch (c->Condition)
    {
    case 1:
      fprintf(fd, "-- CountdownTimer(%d)\n", c->QualifiedNumber);
      break;
    case 2:
      fprintf(fd, "-- Command(%d, %d, %d)\n", c->Group, c->UnitType,
              c->QualifiedNumber);
      break;
    case 3:
      fprintf(fd, "-- Bring(%d, %d, [%hu,%hu]-[%hu,%hu], %d)\n", c->Group,
              c->UnitType, map->Locations[c->Location].StartX,
              map->Locations[c->Location].StartY,
              map->Locations[c->Location].EndX, map->Locations[c->Location].EndY,
              c->QualifiedNumber);
      break;
    case 4:
      fprintf(fd, "-- Accumulate(%d, %d, %d)\n", c->Group, c->QualifiedNumber,
              c->ResType);
      break;
    case 5:
      fprintf(fd, "-- Kill(%d, %d, %d)\n", c->Group, c->UnitType,
              c->QualifiedNumber);
      break;
    case 6:
      fprintf(fd, "-- CommandMost(%d)\n", c->UnitType);
      break;
    case 7:
      fprintf(fd, "-- CommandMostAt(%d, [%hu,%hu]-[%hu,%hu])\n", c->UnitType,
              map->Locations[c->Location].StartX,
              map->Locations[c->Location].StartY,
              map->Locations[c->Location].EndX, map->Locations[c->Location].EndY);
      break;
    case 8:
      fprintf(fd, "-- MostKills(%d)\n", c->UnitType);
      break;
    case 9:
      fprintf(fd, "-- HighestScore(%d)\n", c->ResType);
      break;
    case 10:
      fprintf(fd, "-- MostResources(%d)\n", c->ResType);
      break;
    case 11:
      fprintf(fd, "-- Switch(%d)\n", c->ResType);
      break;
    case 12:
      fprintf(fd, "-- ElapsedTime(%d)\n", c->QualifiedNumber);
      break;
    case 13:
      fprintf(fd, "-- MissionBriefing()\n");
      break;
    case 14:
      fprintf(fd, "-- Opponents(%d, %d)\n", c->Group, c->QualifiedNumber);
      break;
    case 15:
      fprintf(fd, "-- Deaths(%d, %d, %d)\n", c->Group, c->UnitType,
              c->QualifiedNumber);
      break;
    case 16:
      fprintf(fd, "-- CommandLeast(%d)\n", c->UnitType);
      break;
    case 17:
      fprintf(fd, "-- CommandLeastAt(%d, [%hu,%hu]-[%hu,%hu])\n", c->UnitType,
              map->Locations[c->Location].StartX,
              map->Locations[c->Location].StartY,
              map->Locations[c->Location].EndX, map->Locations[c->Location].EndY);
      break;
    case 18:
      fprintf(fd, "-- LeastKills(%d)\n", c->UnitType);
      break;
    case 19:
      fprintf(fd, "-- LowestScore(%d)\n", c->ResType);
      break;
    case 20:
      fprintf(fd, "-- LeastResources(%d)\n", c->ResType);
      break;
    case 21:
      fprintf(fd, "-- Score(%d, %d, %d)\n", c->Group, c->ResType,
              c->QualifiedNumber);
      break;
    case 22:
      fprintf(fd, "-- Always()\n");
      break;
    case 23:
      fprintf(fd, "-- Never()\n");
      break;
    default:
      fprintf(fd, "-- Unhandled condition: %d\n", c->Condition);
      break;
    }
  }

  // Actions
  for (i = 0; i < 64; ++i)
  {
    a = &trigger->TriggerActions[i];
    if (a->Action == 0)
    {
      break;
    }
    switch (a->Action)
    {
    case 1:
      fprintf(fd, "--  ActionVictory()\n");
      break;
    case 2:
      fprintf(fd, "--  ActionDefeat()\n");
      break;
    case 3:
      fprintf(fd, "--  Preserve trigger\n");
      break;
    case 4:
      fprintf(fd, "--  Wait(%d)\n", a->Time);
      break;
    case 5:
      fprintf(fd, "--  Pause\n");
      break;
    case 6:
      fprintf(fd, "--  Unpause\n");
      break;
    case 7:
      fprintf(fd,
              "--  Transmission(%s, %d, [%hu,%hu]-[%hu,%hu], %d, %d, %d, %d)\n",
              map->Strings[a->TriggerNumber - 1].c_str(), a->Status,
              map->Locations[a->Source].StartX, map->Locations[a->Source].StartY,
              map->Locations[a->Source].EndX, map->Locations[a->Source].EndY,
              a->Time, a->NumUnits, a->WavNumber, a->Time);
      break;
    case 8:
      fprintf(fd, "--  PlayWav(%d, %d)\n", a->WavNumber, a->Time);
      break;
    case 9:
      fprintf(fd, "--  TextMessage(%s)\n",
              map->Strings[a->TriggerNumber - 1].c_str());
      break;
    case 10:
      fprintf(fd, "--  CenterMap(%hu, %hu)\n",
              (map->Locations[a->Source].StartX + map->Locations[a->Source].EndX)
              / 2 / 32,
              (map->Locations[a->Source].StartY + map->Locations[a->Source].EndY)
              / 2 / 32);
      break;
    case 12:
      fprintf(fd, "--  SetObjectives(%s)\n",
              map->Strings[a->TriggerNumber - 1].c_str());
      break;
    case 26:
      fprintf(fd, "--  SetResources(%d, %d, %d, %d)\n", a->FirstGroup,
              a->SecondGroup, a->NumUnits, a->Status);
      break;
    case 30:
      fprintf(fd, "--  Mute unit speech\n");
      break;
    case 31:
      fprintf(fd, "--  Unmute unit speech\n");
      break;
    default:
      fprintf(fd, "--  Unhandled action: %d\n", a->Action);
      break;
    }
  }
}

void Chk::SaveSMS(Storage storage)
{
  FILE *fd;
  int i;

  storage.setFilename(storage.getFilename() + "sms");

  CheckPath(storage.getFullPath());

  fd = fopen(storage.getFullPath().c_str(), "wb");

  fprintf(fd, "-- Stratagus Map Setup\n");
  fprintf(fd, "-- File generated automatically from scmconvert V" VERSION "\n");
  fprintf(fd, "\n");

  for (i = 0; i < PlayerMax; ++i)
  {
    if (map->PlayerType[i] == 0)
    {
      // inactive
      continue;
    }
    fprintf(fd, "SetStartView(%d, %d, %d)\n", i, map->PlayerStart[i].X,
            map->PlayerStart[i].Y);
    fprintf(fd, "SetPlayerData(%d, \"Resources\", \"minerals\", %d)\n", i, 0);
    fprintf(fd, "SetPlayerData(%d, \"Resources\", \"gas\", %d)\n", i, 0);
    fprintf(fd, "SetPlayerData(%d, \"RaceName\", \"%s\")\n", i,
            RaceNames[map->PlayerRace[i]]);
  }

  fprintf(fd, "\n\n");

  fprintf(fd, "LoadTileModels(\"luagen/tilesets/%s.lua\")\n",
          map->MapTerrainName);

  fprintf(fd, "\n\n");

  // SetTile(t, x, y);
  for (int h = 0; h < map->MapHeight; ++h)
  {
    for (int w = 0; w < map->MapWidth; ++w)
    {
      fprintf(fd, "SetTile(%d, %d, %d)\n", map->Tiles[h * map->MapWidth + w], w,
              h);
    }
  }

  fprintf(fd, "\n\n");

  // units
  for (i = 0; i < (int) map->Units.size(); ++i)
  {
    string unitName = mUnitNames[map->Units[i].Type];

    string lua_str = lg::line(
                       lg::assign(
                         "unit",
                         lg::CreateUnit(unitName, (map->Units[i]).Player, Pos(map->Units[i].X, map->Units[i].Y)))
                     );

    fprintf(fd, "%s", lua_str.c_str()); // TODO: c++ this

    if (map->Units[i].ResourceAmount)
    {
      fprintf(fd, "SetResourcesHeld(unit, %d)\n", map->Units[i].ResourceAmount);
    }
  }

  fprintf(fd, "\n\n");

  for (i = 0; i < (int) map->Triggers.size(); ++i)
  {
    SaveTrigger(fd, (Trigger *) &map->Triggers[i]);
  }

  fprintf(fd, "\n\n");

  fclose(fd);
}

void Chk::SaveMap(Storage storage)
{
  // if a map ends with a dot (.) then it adds .sms and .scp otherwise a dir with scenario.sms/scenario.smp
  // TODO: if you give something unexpected to savedir - bye bye => rework later
  if (storage.getFullPath().back() == '/')
  {
    storage.setFilename(storage.getFilename() + "scenario.");
  }

  SaveSMP(storage);

  SaveSMS(storage);
}

void Chk::FreeMap()
{
  free(map->Description);
  free(map->MapTerrainName);
  free(map->Tiles);
  delete map;
}

void Chk::ConvertChk(Storage storage, unsigned char *chkdata, int chklen)
{
  loadFromBuffer(chkdata, chklen);
  SaveMap(storage);
}

bool Chk::convert(const std::string &arcfile, Storage storage)
{
  //char buf[1024];
  bool result = false;

  //Preferences &preferences = Preferences::getInstance();
  //sprintf(buf, "%s/%s", preferences.getDestDir().c_str(), file.c_str());

  shared_ptr<DataChunk> data = mHurricane->extractDataChunk(arcfile);
  if (data)
  {
    ConvertChk(storage, data->getDataPointer(), data->getSize());

    result = true;
  }

  return result;
}

