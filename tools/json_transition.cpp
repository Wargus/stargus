/*
 * json_transition.cpp
 *
 *  This is just a temporary tool for transition of the old array style data to json
 *
 *      Author: Andreas Volz
 */


#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <iomanip>

#include "../src/startool_mpq.h"

using namespace std;

using json = nlohmann::json;

extern const char *UnitNames[];

/*typedef struct _control_
{
  int Type;          /// Entry type
  int Version;       /// Only in this version
  const char *File;    /// Save file
  const char *ArcFile;    /// File name in list file
  int Arg1;          /// Extra argument 1
  int Arg2;          /// Extra argument 2
  int Arg3;          /// Extra argument 3
  int Arg4;          /// Extra argument 4
} Control;*/

string getTypeName(int type)
{
  string str;

  switch (type)
  {
  case S:    // Setup
    str = "S";
    break;
  case F:    // File                          (name)
    str = "F";
    break;
  case M:    // Map                           (name)
    str = "M";
    break;
  case T:    // Tileset                       (name,pal,mega,mini,map)
    str = "T";
    break;
  case R:    // RGB -> gimp                   (name,rgb)
    str = "R";
    break;
  case G:    // Graphics                      (name,pal,gfx)
    str = "G";
    break;
  case U:    // Uncompressed Graphics         (name,pal,gfu)
    str = "U";
    break;
  case I:    // Widgets                       (name,pal,gfu)
    str = "I";
    break;
  case N:    // Font                          (name,idx)
    str = "N";
    break;
  case W:    // Wav                           (name,wav)
    str = "W";
    break;
  case H:    // Pcx                           (name)
    str = "W";
    break;
  case E:    // Raw extract                   (name)
    str = "E";
    break;
  case V:    // SMK Video                     (name,video)
    str = "V";
    break;
  case L:    // Campaign Levels
    str = "L";
    break;
  case Q:    // MPQ archive
    str = "Q";
    break;
  case D:    // Graphics in DDS format
    str = "D";
    break;
  case P:    // SMK Portraits
    str = "P";
    break;
  case PAL:  // Palette from pcx file
    str = "PAL";
    break;
  case WPE:   // Palette from wpe file
    str = "WPE";
    break;
  default:
    break;
  }

  return str;
}

void to_json(json &j, const Control &c)
{
  j = json{ {"type", getTypeName(c.Type)}, {"file", c.File}, {"arcfile", c.ArcFile} };
}


int main(int argc, char **argv)
{
  Control *c = nullptr;
  unsigned int len = 0;

  for(unsigned int un = 0; un < 228; un++)
  {
    printf("unit: %s\n", UnitNames[un]);
  }

  c = Todo_bootstrap;
  len = sizeof(Todo_bootstrap) / sizeof(*Todo_bootstrap);
  for (unsigned int u = 0; u < len; ++u)
  {
    switch (c[u].Type)
    {
    case F:
    {

    }
    break;
    default:
      break;
    }
  }

  c = Todo_bootstrap;
  len = sizeof(Todo_bootstrap) / sizeof(*Todo_bootstrap);
  for (unsigned int u = 0; u < len; ++u)
  {
    switch (c[u].Type)
    {
    case F:
    {

    }
    break;
    default:
      break;
    }
  }

  json j;

  for (unsigned int i = 0; i <= 1; ++i)
  {
    switch (i)
    {
    case 0:
      // StarDat.mpq or stardat.mpq from inside files\\stardat.mpq
      c = Todo;
      len = sizeof(Todo) / sizeof(*Todo);

      break;
    case 1:
      // CD install.exe renamed to StarCraft.mpq or other main mpq file
      c = CDTodo;
      len = sizeof(CDTodo) / sizeof(*CDTodo);

      break;
    }

    for (unsigned int u = 0; u < len; ++u)
    {

      j["object" + to_string(u)] = c[u];

      /*   j["type"] = c[u].Type;
         j["file"] = c[u].File;
         j["arcfile"] = c[u].ArcFile;
         j["Arg1"] = c[u].Arg1;
         j["Arg2"] = c[u].Arg2;
         j["Arg3"] = c[u].Arg3;
         j["Arg4"] = c[u].Arg4;
      */

      switch (c[u].Type)
      {
      case PAL:
      {
        break;
      }
      }
    }
  }


  /*
    j["pi"] = 3.141; //Then initialize by name / value pair. At this time, the value corresponding to the name "pi" is 3.141
    j["happy"] = true;//Assign the name "happy" to true
    j["name"] = "Niels";//Store the string "Niels" to "name"
    j["nothing"] = nullptr;//"nothing" corresponds to a null pointer
    j["answer"]["everything"] = 42;//Initializes the objects in the object
    j["list"] = { 1, 0, 2 };//Use the list initialization method to initialize the "list" array*/


  //cout << std::setw(4) << j << endl;

}

const char *UnitNames[] =
{
  "unit-terran-marine", "unit-terran-ghost", "unit-terran-vulture",
  "unit-terran-goliath", "Goliath-Turret",
  "unit-terran-siege-tank-(Tank-Mode)", "Tank-Turret(Tank-Mode)",
  "unit-terran-scv", "unit-terran-wraith", "unit-terran-science-vessel",
  "Gui-Montang-(Firebat)", "unit-terran-dropship",
  "unit-terran-battlecruiser", "Vulture-Spider-Mine", "Nuclear-Missile",
  "unit-terran-civilian", "Sarah-Kerrigan-(Ghost)", "Alan-Schezar-(Goliath)",
  "Alan-Schezar-Turret", "Jim-Raynor-(Vulture)", "Jim-Raynor-(Marine)",
  "Tom-Kazansky-(Wraith)", "Magellan-(Science-Vessel)",
  "Edmund-Duke-(Siege-Tank)", "Edmund-Duke-Turret",
  "Edmund-Duke-(Siege-Mode)", "Edmund-Duke-Turret",
  "Arcturus-Mengsk-(Battlecruiser)", "Hyperion-(Battlecruiser)",
  "Norad-II-(Battlecruiser)", "unit-terran-siege-tank-(Siege-Mode)",
  "Tank-Turret-(Siege-Mode)", "Firebat", "Scanner-Sweep", "unit-terran-medic",
  "unit-zerg-larva", "unit-zerg-egg", "unit-zerg-zergling",
  "unit-zerg-hydralisk", "unit-zerg-ultralisk", "unit-zerg-broodling",
  "unit-zerg-drone", "unit-zerg-overlord", "unit-zerg-mutalisk",
  "unit-zerg-guardian", "unit-zerg-queen", "unit-zerg-defiler",
  "unit-zerg-scourge", "Torrarsque-(Ultralisk)", "Matriarch-(Queen)",
  "Infested-Terran", "Infested-Kerrigan", "Unclean-One-(Defiler)",
  "Hunter-Killer-(Hydralisk)", "Devouring-One-(Zergling)",
  "Kukulza-(Mutalisk)", "Kukulza-(Guardian)", "Yggdrasill-(Overlord)",
  "unit-terran-valkyrie-frigate", "Mutalisk/Guardian-Cocoon",
  "unit-protoss-corsair", "unit-protoss-dark-templar(Unit)",
  "unit-zerg-devourer", "unit-protoss-dark-archon", "unit-protoss-probe",
  "unit-protoss-zealot", "unit-protoss-dragoon", "unit-protoss-high-templar",
  "unit-protoss-archon", "unit-protoss-shuttle", "unit-protoss-scout",
  "unit-protoss-arbiter", "unit-protoss-carrier", "unit-protoss-interceptor",
  "Dark-Templar(Hero)", "Zeratul-(Dark-Templar)", "Tassadar/Zeratul-(Archon)",
  "Fenix-(Zealot)", "Fenix-(Dragoon)", "Tassadar-(Templar)", "Mojo-(Scout)",
  "Warbringer-(Reaver)", "Gantrithor-(Carrier)", "unit-protoss-reaver",
  "unit-protoss-observer", "unit-protoss-scarab", "Danimoth-(Arbiter)",
  "Aldaris-(Templar)", "Artanis-(Scout)", "Rhynadon-(Badlands-Critter)",
  "Bengalaas-(Jungle-Critter)", "Unused---Was-Cargo-Ship",
  "Unused---Was-Mercenary-Gunship", "Scantid-(Desert-Critter)",
  "Kakaru-(Twilight-Critter)", "Ragnasaur-(Ashworld-Critter)",
  "Ursadon-(Ice-World-Critter)", "Lurker-Egg", "Raszagal",
  "Samir-Duran-(Ghost)", "Alexei-Stukov-(Ghost)", "Map-Revealer",
  "Gerard-DuGalle", "unit-zerg-Lurker", "Infested-Duran", "Disruption-Web",
  "unit-terran-command-center", "unit-terran-comsat-station",
  "unit-terran-nuclear-silo", "unit-terran-supply-depot",
  "unit-terran-refinery", "unit-terran-barracks", "unit-terran-academy",
  "unit-terran-factory", "unit-terran-starport", "unit-terran-control-tower",
  "unit-terran-science-facility", "unit-terran-covert-ops",
  "unit-terran-physics-lab", "Unused---Was-Starbase?",
  "unit-terran-machine-shop", "Unused---Was-Repair-Bay?",
  "unit-terran-engineering-bay", "unit-terran-armory",
  "unit-terran-missile-turret", "unit-terran-bunker", "Norad-II",
  "Ion-Cannon", "Uraj-Crystal", "Khalis-Crystal", "Infested-Command-Center",
  "unit-zerg-hatchery", "unit-zerg-lair", "unit-zerg-hive",
  "unit-zerg-nydus-canal", "unit-zerg-hydralisk-den",
  "unit-zerg-defiler-mound", "unit-zerg-greater-spire",
  "unit-zerg-queens-nest", "unit-zerg-evolution-chamber",
  "unit-zerg-ultralisk-cavern", "unit-zerg-spire", "unit-zerg-spawning-pool",
  "unit-zerg-creep-colony", "unit-zerg-spore-colony", "Unused-Zerg-Building",
  "unit-zerg-sunken-colony", "unit-zerg-overmind-(With-Shell)",
  "unit-zerg-overmind", "unit-zerg-extractor", "Mature-Chrysalis",
  "unit-zerg-cerebrate", "unit-zerg-cerebrate-daggoth",
  "Unused-Zerg-Building-5", "unit-protoss-nexus",
  "unit-protoss-robotics-facility", "unit-protoss-pylon",
  "unit-protoss-assimilator", "Unused-Protoss-Building",
  "unit-protoss-observatory", "unit-protoss-gateway",
  "Unused-Protoss-Building", "unit-protoss-photon-cannon",
  "unit-protoss-citadel-of-adun", "unit-protoss-cybernetics-core",
  "unit-protoss-templar-archives", "unit-protoss-forge",
  "unit-protoss-stargate", "Stasis-Cell/Prison", "unit-protoss-fleet-beacon",
  "unit-protoss-arbiter-tribunal", "unit-protoss-robotics-support-bay",
  "unit-protoss-shield-battery", "Khaydarin-Crystal-Formation",
  "unit-protoss-temple", "Xel'Naga-Temple", "unit-minerals1",
  "unit-minerals2", "unit-minerals3", "Cave", "Cave-in", "Cantina",
  "Mining-Platform", "Independant-Command-Center", "Independant-Starport",
  "Independant-Jump-Gate", "Ruins", "Kyadarin-Crystal-Formation",
  "unit-vespene-geyser", "Warp-Gate", "PSI-Disruptor", "unit-zerg-marker",
  "unit-terran-marker", "unit-protoss-marker", "unit-zerg-beacon",
  "unit-terran-beacon", "unit-protoss-beacon", "unit-zerg-flag-beacon",
  "unit-terran-flag-beacon", "unit-protoss-flag-beacon", "Power-Generator",
  "Overmind-Cocoon", "Dark-Swarm", "Floor-Missile-Trap", "Floor-Hatch",
  "Left-Upper-Level-Door", "Right-Upper-Level-Door", "Left-Pit-Door",
  "Right-Pit-Door", "Floor-Gun-Trap", "Left-Wall-Missile-Trap",
  "Left-Wall-Flame-Trap", "Right-Wall-Missile-Trap", "Right-Wall-Flame-Trap",
  "Start-Location", "Flag", "Young-Chrysalis", "Psi-Emitter", "Data-Disc",
  "Khaydarin-Crystal", "Mineral-Cluster-Type-1", "Mineral-Cluster-Type-2",
  "unit-protoss-vespene-gas-orb-type-1",
  "unit-protoss-vespene-gas-orb-type-2", "unit-zerg-vespene-gas-sac-type-1",
  "unit-zerg-vespene-gas-sac-type-2", "unit-terran-vespene-gas-tank-type-1",
  "unit-terran-vespene-gas-tank-type-2",
};
