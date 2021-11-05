//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//         Stratagus - A free fantasy real time strategy game engine
//
/**@name scm.cpp - The scm. */
//
//      (c) Copyright 2002-2007 by Jimmy Salmon
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

#ifdef _MSC_VER
#pragma warning(disable:4786)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <string>
#include <libgen.h>

#include "scm.h"
#include "Chk.h"
#include "Storm.h"
#include "endian.h"
#include "FileUtil.h"

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

using namespace std;

/*----------------------------------------------------------------------------
--  Variables
----------------------------------------------------------------------------*/

#define VERSION "1.0"

static const char *UnitNames[] = {
	"unit-terran-marine",
	"unit-terran-ghost",
	"unit-terran-vulture",
	"unit-terran-goliath",
	"Goliath-Turret",
	"unit-terran-siege-tank-(Tank-Mode)",
	"Tank-Turret(Tank-Mode)",
	"unit-terran-scv",
	"unit-terran-wraith",
	"unit-terran-science-vessel",
	"Gui-Montang-(Firebat)",
	"unit-terran-dropship",
	"unit-terran-battlecruiser",
	"Vulture-Spider-Mine",
	"Nuclear-Missile",
	"unit-terran-civilian",
	"Sarah-Kerrigan-(Ghost)",
	"Alan-Schezar-(Goliath)",
	"Alan-Schezar-Turret",
	"Jim-Raynor-(Vulture)",
	"Jim-Raynor-(Marine)",
	"Tom-Kazansky-(Wraith)",
	"Magellan-(Science-Vessel)",
	"Edmund-Duke-(Siege-Tank)",
	"Edmund-Duke-Turret",
	"Edmund-Duke-(Siege-Mode)",
	"Edmund-Duke-Turret",
	"Arcturus-Mengsk-(Battlecruiser)",
	"Hyperion-(Battlecruiser)",
	"Norad-II-(Battlecruiser)",
	"unit-terran-siege-tank-(Siege-Mode)",
	"Tank-Turret-(Siege-Mode)",
	"Firebat",
	"Scanner-Sweep",
	"unit-terran-medic",
	"unit-zerg-larva",
	"unit-zerg-egg",
	"unit-zerg-zergling",
	"unit-zerg-hydralisk",
	"unit-zerg-ultralisk",
	"unit-zerg-broodling",
	"unit-zerg-drone",
	"unit-zerg-overlord",
	"unit-zerg-mutalisk",
	"unit-zerg-guardian",
	"unit-zerg-queen",
	"unit-zerg-defiler",
	"unit-zerg-scourge",
	"Torrarsque-(Ultralisk)",
	"Matriarch-(Queen)",
	"Infested-Terran",
	"Infested-Kerrigan",
	"Unclean-One-(Defiler)",
	"Hunter-Killer-(Hydralisk)",
	"Devouring-One-(Zergling)",
	"Kukulza-(Mutalisk)",
	"Kukulza-(Guardian)",
	"Yggdrasill-(Overlord)",
	"unit-terran-valkyrie-frigate",
	"Mutalisk/Guardian-Cocoon",
	"unit-protoss-corsair",
	"unit-protoss-dark-templar(Unit)",
	"unit-zerg-devourer",
	"unit-protoss-dark-archon",
	"unit-protoss-probe",
	"unit-protoss-zealot",
	"unit-protoss-dragoon",
	"unit-protoss-high-templar",
	"unit-protoss-archon",
	"unit-protoss-shuttle",
	"unit-protoss-scout",
	"unit-protoss-arbiter",
	"unit-protoss-carrier",
	"unit-protoss-interceptor",
	"Dark-Templar(Hero)",
	"Zeratul-(Dark-Templar)",
	"Tassadar/Zeratul-(Archon)",
	"Fenix-(Zealot)",
	"Fenix-(Dragoon)",
	"Tassadar-(Templar)",
	"Mojo-(Scout)",
	"Warbringer-(Reaver)",
	"Gantrithor-(Carrier)",
	"unit-protoss-reaver",
	"unit-protoss-observer",
	"unit-protoss-scarab",
	"Danimoth-(Arbiter)",
	"Aldaris-(Templar)",
	"Artanis-(Scout)",
	"Rhynadon-(Badlands-Critter)",
	"Bengalaas-(Jungle-Critter)",
	"Unused---Was-Cargo-Ship",
	"Unused---Was-Mercenary-Gunship",
	"Scantid-(Desert-Critter)",
	"Kakaru-(Twilight-Critter)",
	"Ragnasaur-(Ashworld-Critter)",
	"Ursadon-(Ice-World-Critter)",
	"Lurker-Egg",
	"Raszagal",
	"Samir-Duran-(Ghost)",
	"Alexei-Stukov-(Ghost)",
	"Map-Revealer",
	"Gerard-DuGalle",
	"unit-zerg-Lurker",
	"Infested-Duran",
	"Disruption-Web",
	"unit-terran-command-center",
	"unit-terran-comsat-station",
	"unit-terran-nuclear-silo",
	"unit-terran-supply-depot",
	"unit-terran-refinery",
	"unit-terran-barracks",
	"unit-terran-academy",
	"unit-terran-factory",
	"unit-terran-starport",
	"unit-terran-control-tower",
	"unit-terran-science-facility",
	"unit-terran-covert-ops",
	"unit-terran-physics-lab",
	"Unused---Was-Starbase?",
	"unit-terran-machine-shop",
	"Unused---Was-Repair-Bay?",
	"unit-terran-engineering-bay",
	"unit-terran-armory",
	"unit-terran-missile-turret",
	"unit-terran-bunker",
	"Norad-II",
	"Ion-Cannon",
	"Uraj-Crystal",
	"Khalis-Crystal",
	"Infested-Command-Center",
	"unit-zerg-hatchery",
	"unit-zerg-lair",
	"unit-zerg-hive",
	"unit-zerg-nydus-canal",
	"unit-zerg-hydralisk-den",
	"unit-zerg-defiler-mound",
	"unit-zerg-greater-spire",
	"unit-zerg-queens-nest",
	"unit-zerg-evolution-chamber",
	"unit-zerg-ultralisk-cavern",
	"unit-zerg-spire",
	"unit-zerg-spawning-pool",
	"unit-zerg-creep-colony",
	"unit-zerg-spore-colony",
	"Unused-Zerg-Building",
	"unit-zerg-sunken-colony",
	"unit-zerg-overmind-(With-Shell)",
	"unit-zerg-overmind",
	"unit-zerg-extractor",
	"Mature-Chrysalis",
	"unit-zerg-cerebrate",
	"unit-zerg-cerebrate-daggoth",
	"Unused-Zerg-Building-5",
	"unit-protoss-nexus",
	"unit-protoss-robotics-facility",
	"unit-protoss-pylon",
	"unit-protoss-assimilator",
	"Unused-Protoss-Building",
	"unit-protoss-observatory",
	"unit-protoss-gateway",
	"Unused-Protoss-Building",
	"unit-protoss-photon-cannon",
	"unit-protoss-citadel-of-adun",
	"unit-protoss-cybernetics-core",
	"unit-protoss-templar-archives",
	"unit-protoss-forge",
	"unit-protoss-stargate",
	"Stasis-Cell/Prison",
	"unit-protoss-fleet-beacon",
	"unit-protoss-arbiter-tribunal",
	"unit-protoss-robotics-support-bay",
	"unit-protoss-shield-battery",
	"Khaydarin-Crystal-Formation",
	"unit-protoss-temple",
	"Xel'Naga-Temple",
	"unit-minerals1",
	"unit-minerals2",
	"unit-minerals3",
	"Cave",
	"Cave-in",
	"Cantina",
	"Mining-Platform",
	"Independant-Command-Center",
	"Independant-Starport",
	"Independant-Jump-Gate",
	"Ruins",
	"Kyadarin-Crystal-Formation",
	"unit-vespene-geyser",
	"Warp-Gate",
	"PSI-Disruptor",
	"unit-zerg-marker",
	"unit-terran-marker",
	"unit-protoss-marker",
	"unit-zerg-beacon",
	"unit-terran-beacon",
	"unit-protoss-beacon",
	"unit-zerg-flag-beacon",
	"unit-terran-flag-beacon",
	"unit-protoss-flag-beacon",
	"Power-Generator",
	"Overmind-Cocoon",
	"Dark-Swarm",
	"Floor-Missile-Trap",
	"Floor-Hatch",
	"Left-Upper-Level-Door",
	"Right-Upper-Level-Door",
	"Left-Pit-Door",
	"Right-Pit-Door",
	"Floor-Gun-Trap",
	"Left-Wall-Missile-Trap",
	"Left-Wall-Flame-Trap",
	"Right-Wall-Missile-Trap",
	"Right-Wall-Flame-Trap",
	"Start-Location",
	"Flag",
	"Young-Chrysalis",
	"Psi-Emitter",
	"Data-Disc",
	"Khaydarin-Crystal",
	"Mineral-Cluster-Type-1",
	"Mineral-Cluster-Type-2",
	"unit-protoss-vespene-gas-orb-type-1",
	"unit-protoss-vespene-gas-orb-type-2",
	"unit-zerg-vespene-gas-sac-type-1",
	"unit-zerg-vespene-gas-sac-type-2",
	"unit-terran-vespene-gas-tank-type-1",
	"unit-terran-vespene-gas-tank-type-2",
};

/*----------------------------------------------------------------------------
--  Functions
----------------------------------------------------------------------------*/

/**
**  Load scm
**
**  @param scm  Name of the scm file
**  @param map  The map
*/
void LoadScm(const char *mpqfile, const char *dir, WorldMap *map)
{
	unsigned char *chkdata = NULL;
	size_t chklen = 0;

	Storm mpq(mpqfile);
	bool result = mpq.extractMemory("staredit\\scenario.chk", &chkdata, &chklen);
	if (result)
	{
		Chk::loadFromBuffer(chkdata, chklen, map);
	}

	free(chkdata);

}

static void SaveSMP(const char *name, WorldMap *map)
{
	FILE *fd;

	CheckPath(name);

	fd = fopen(name, "wb");

	fprintf(fd, "-- Stratagus Map Presentation\n");
	fprintf(fd, "-- File generated automatically from scmconvert V" VERSION "\n");
	fprintf(fd, "\n");

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
	fprintf(fd, "PresentMap(\"%s\", %d, %d, %d, %d)\n", map->Description, 2, map->MapWidth, map->MapHeight, 0);

	fclose(fd);
}

static void SaveTrigger(FILE *fd, WorldMap *map, Trigger *trigger)
{
	int i;
	TriggerCondition *c;
	TriggerAction *a;

	// Conditions
	for (i = 0; i < 16; ++i) {
		c = &trigger->TriggerConditions[i];
		if (c->Condition == 0) {
			break;
		}
		switch (c->Condition) {
			case 1:
				fprintf(fd, "-- CountdownTimer(%d)\n", c->QualifiedNumber);
				break;
			case 2:
				fprintf(fd, "-- Command(%d, %d, %d)\n", c->Group, c->UnitType, c->QualifiedNumber);
				break;
			case 3:
				fprintf(fd, "-- Bring(%d, %d, [%hu,%hu]-[%hu,%hu], %d)\n", c->Group, c->UnitType,
					map->Locations[c->Location].StartX, map->Locations[c->Location].StartY,
					map->Locations[c->Location].EndX, map->Locations[c->Location].EndY,
					c->QualifiedNumber);
				break;
			case 4:
				fprintf(fd, "-- Accumulate(%d, %d, %d)\n", c->Group, c->QualifiedNumber, c->ResType);
				break;
			case 5:
				fprintf(fd, "-- Kill(%d, %d, %d)\n", c->Group, c->UnitType, c->QualifiedNumber);
				break;
			case 6:
				fprintf(fd, "-- CommandMost(%d)\n", c->UnitType);
				break;
			case 7:
				fprintf(fd, "-- CommandMostAt(%d, [%hu,%hu]-[%hu,%hu])\n", c->UnitType,
					map->Locations[c->Location].StartX, map->Locations[c->Location].StartY,
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
				fprintf(fd, "-- Deaths(%d, %d, %d)\n", c->Group, c->UnitType, c->QualifiedNumber);
				break;
			case 16:
				fprintf(fd, "-- CommandLeast(%d)\n", c->UnitType);
				break;
			case 17:
				fprintf(fd, "-- CommandLeastAt(%d, [%hu,%hu]-[%hu,%hu])\n", c->UnitType,
					map->Locations[c->Location].StartX, map->Locations[c->Location].StartY,
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
				fprintf(fd, "-- Score(%d, %d, %d)\n", c->Group, c->ResType, c->QualifiedNumber);
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
	for (i = 0; i < 64; ++i) {
		a = &trigger->TriggerActions[i];
		if (a->Action == 0) {
			break;
		}
		switch (a->Action) {
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
				fprintf(fd, "--  Transmission(%s, %d, [%hu,%hu]-[%hu,%hu], %d, %d, %d, %d)\n",
					map->Strings[a->TriggerNumber - 1].c_str(), a->Status,
					map->Locations[a->Source].StartX, map->Locations[a->Source].StartY,
					map->Locations[a->Source].EndX, map->Locations[a->Source].EndY,
					a->Time, a->NumUnits, a->WavNumber, a->Time);
				break;
			case 8:
				fprintf(fd, "--  PlayWav(%d, %d)\n", a->WavNumber, a->Time);
				break;
			case 9:
				fprintf(fd, "--  TextMessage(%s)\n", map->Strings[a->TriggerNumber - 1].c_str());
				break;
			case 10:
				fprintf(fd, "--  CenterMap(%hu, %hu)\n",
					(map->Locations[a->Source].StartX + map->Locations[a->Source].EndX) / 2 / 32,
					(map->Locations[a->Source].StartY + map->Locations[a->Source].EndY) / 2 / 32);
				break;
			case 12:
				fprintf(fd, "--  SetObjectives(%s)\n", map->Strings[a->TriggerNumber - 1].c_str());
				break;
			case 26:
				fprintf(fd, "--  SetResources(%d, %d, %d, %d)\n", a->FirstGroup, a->SecondGroup, a->NumUnits, a->Status);
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

static void SaveSMS(const char *name, WorldMap *map)
{
	FILE *fd;
	int i;

	CheckPath(name);

	fd = fopen(name, "wb");

	fprintf(fd, "-- Stratagus Map Setup\n");
	fprintf(fd, "-- File generated automatically from scmconvert V" VERSION "\n");
	fprintf(fd, "\n");

	for (i = 0; i < PlayerMax; ++i) {
		if (map->PlayerType[i] == 0) { // inactive
			continue;
		}
		fprintf(fd, "SetStartView(%d, %d, %d)\n", i, map->PlayerStart[i].X, map->PlayerStart[i].Y);
		fprintf(fd, "SetPlayerData(%d, \"Resources\", \"minerals\", %d)\n", i, 0);
		fprintf(fd, "SetPlayerData(%d, \"Resources\", \"gas\", %d)\n", i, 0);
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
	for (i = 0; i < (int)map->Units.size(); ++i) {
		fprintf(fd, "unit= CreateUnit(\"%s\", %d, {%d, %d})\n", UnitNames[map->Units[i].Type],
			(map->Units[i]).Player, map->Units[i].X, map->Units[i].Y);
		if (map->Units[i].ResourceAmount) {
			fprintf(fd, "SetResourcesHeld(unit, %d)\n", map->Units[i].ResourceAmount);
		}
	}

	fprintf(fd, "\n\n");

	for (i = 0; i < (int)map->Triggers.size(); ++i) {
		SaveTrigger(fd, map, (Trigger*) &map->Triggers[i]);
	}

	fprintf(fd, "\n\n");

	fclose(fd);
}

static void SaveMap(const char *name, WorldMap *map)
{
	char *fullmapname;

	fullmapname = strdup(name);
	strcpy(strrchr(fullmapname, '.') + 1, "smp");
	SaveSMP(fullmapname, map);

	strcpy(strrchr(fullmapname, '.') + 1, "sms");
	SaveSMS(fullmapname, map);

	free(fullmapname);
}

void FreeMap(WorldMap *map)
{
	free(map->Description);
	free(map->MapTerrainName);
	free(map->Tiles);
}

void ConvertScm(const char *mpqfile)
{
	WorldMap map;


	char *basename_path = basename(strdup(mpqfile));
	char *dirname_path = dirname(strdup(mpqfile));

	LoadScm(mpqfile, dirname_path, &map);
	SaveMap(mpqfile, &map);
	FreeMap(&map);
}

void ConvertChk(const char *newname, unsigned char *chkdata, int chklen)
{
	WorldMap map;
	Chk::loadFromBuffer(chkdata, chklen, &map);
	SaveMap(newname, &map);
	FreeMap(&map);
}


#ifdef STAND_ALONE
void usage()
{
	fprintf(stderr, "%s\n%s\n",
		"scmconvert V" VERSION,
		"usage: scmconvert inputfile [ outputdir ]\n");
	exit(-1);
}

int main(int argc, char **argv)
{
	char *infile;
	char *outdir;

	if (argc < 2 || argc > 3) {
		usage();
	}

	infile = argv[1];
	if (argc == 3) {
		outdir = argv[2];
	} else {
		outdir = strdup(".");
	}

	if (strstr(infile, ".scm\0")) {
		char *tmp;
		char newname[1024];

		sprintf(newname, "%s/", outdir);
		if ((tmp = strrchr(infile, '/'))) {
			strcat(newname, tmp + 1);
		} else if ((tmp = strrchr(infile, '\\'))) {
			strcat(newname, tmp + 1);
		} else {
			strcat(newname, infile);
		}

		// TODO: fix this standalone version
		ConvertScm(infile);

	} else if (strstr(infile, ".chk\0")) {
		FILE *f;
		struct stat sb;
		unsigned int len;
		unsigned char *buf;

		if (stat(infile, &sb) == -1) {
			fprintf(stderr, "error finding file: %s\n", infile);
			return -1;
		}
		len = sb.st_size;

		f = fopen(infile, "rb");
		if (f == NULL) {
			fprintf(stderr, "error opening file: %s\n", infile);
			return -1;
		}

		buf = (unsigned char *)malloc(len);
		if (fread(buf, 1, len, f) != len) {
			fprintf(stderr, "error reading from file: %s\n", infile);
			free(buf);
			return -1;
		}

		if (fclose(f)) {
			fprintf(stderr, "error closing file: %s\n", infile);
			free(buf);
			return -1;
		}

		char *tmp;
		char newname[1024];

		sprintf(newname, "%s/", outdir);
		if ((tmp = strrchr(infile, '/'))) {
			strcat(newname, tmp + 1);
		} else if ((tmp = strrchr(infile, '\\'))) {
			strcat(newname, tmp + 1);
		} else {
			strcat(newname, infile);
		}

		ConvertChk(newname, buf, len);

		free(buf);
	} else {
		fprintf(stderr, "Invalid input file: %s\n", infile);
		return -1;
	}

	return 0;
}
#endif

