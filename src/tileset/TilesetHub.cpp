/*
 * TilesetHub.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "TilesetHub.h"
#include "PaletteImage.h"
#include "PngExporter.h"
#include "MegaTile.h"
#include "FileUtil.h"
#include "luagen.h"
#include "Preferences.h"
#include "Hurricane.h"

// system
#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

namespace tileset
{

TilesetHub::TilesetHub(std::shared_ptr<Hurricane> hurricane, const std::string &arcfile) :
  KaitaiConverter(hurricane)
{
  init(arcfile);
}

TilesetHub::~TilesetHub()
{

}

/*m_iscript_stream = mHurricane->extractStream(sc_iscript_bin);
m_iscript_ks = make_shared<kaitai::kstream>(&*m_iscript_stream);

iscript = make_shared<iscript_bin_t>(m_iscript_ks.get());
*/
void TilesetHub::init(const std::string &arcfile)
{
  m_cv5_stream = mHurricane->extractStream(arcfile + ".cv5");
  m_cv5_ks = make_shared<kaitai::kstream>(&*m_cv5_stream);
  cv5 = make_shared<tileset_cv5_t>(m_cv5_ks.get());

  m_vx4_stream = mHurricane->extractStream(arcfile + ".vx4");
  m_vx4_ks = make_shared<kaitai::kstream>(&*m_vx4_stream);
  vx4 = make_shared<tileset_vx4_t>(m_vx4_ks.get());

  m_vf4_stream = mHurricane->extractStream(arcfile + ".vf4");
  m_vf4_ks = make_shared<kaitai::kstream>(&*m_vf4_stream);
  vf4 = make_shared<tileset_vf4_t>(m_vf4_ks.get());

  m_vr4_stream = mHurricane->extractStream(arcfile + ".vr4");
  m_vr4_ks = make_shared<kaitai::kstream>(&*m_vr4_stream);
  vr4 = make_shared<tileset_vr4_t>(m_vr4_ks.get());
}

bool TilesetHub::convert(std::shared_ptr<AbstractPalette> palette, Storage storage)
{
  if(!vx4) // if it isn't available just return false
  {
    return false;
  }

  if(!palette) // if something wrong with palette just return false
  {
    return false;
  }

  unsigned int num_tiles = vx4->elements()->size();
  int tiles_width = 16;
  int tiles_height = static_cast<int>(ceil(static_cast<float>(num_tiles) / static_cast<float>(tiles_width)));

  TiledPaletteImage ultraTile(Size(tiles_width, tiles_height), Size(32,32));

  for(unsigned int i = 0; i < num_tiles; i++)
  {
    MegaTile mega(*this, i);

    ultraTile.copyTile(*mega.getImage(), i);
  }

  // FIXME: I don't like the path handling in this case. Needs to be changed!
  string save_png(storage.getFullPath() + "/" + storage.getFilename() + ".png");
  CheckPath(save_png);
  return PngExporter::save(save_png, ultraTile, palette, 0);
}

void TilesetHub::generateLua(const std::string &name, const std::string &image, Storage luafile)
{
  if(!cv5) // if it isn't available just return with no action
  {
    return;
  }

  unsigned int num_cv5 = cv5->elements()->size();

  int num_doodad = 0;
  int num_normal = 0;

  ofstream lua_tileset_stream;
  CheckPath(luafile.getFullPath());
  lua_tileset_stream.open (luafile.getFullPath());

  vector<string> tile_slots_vector;

  for(unsigned int i = 0; i < num_cv5; i++)
  {
    tileset_cv5_t::group_t* group = cv5->elements()->at(i);

    if(group->doodad() != 0)
    {
      num_doodad++;
      //cout << "doodad(" << i << "): ";
    }
    else
    {
      num_normal++;
      //cout << "normal(" << i << "): ";
    }

    std::vector<uint16_t>* vx4_vf4_ref = group->megatile_references();

    vector<string> tile_solids_vector;

    for(auto elem : *vx4_vf4_ref)
    {
      //cout << to_string(elem);


      tileset_vf4_t::minitile_t* minitile = vf4->elements()->at(elem);

      std::string subtilePassableFlags = "";
      for(auto flags : *minitile->flags())
      {
        if (flags->walkable()) {
          subtilePassableFlags += "p";
        } else {
          subtilePassableFlags += "u";
        }
      }

      tile_solids_vector.push_back(to_string(elem));
      tile_solids_vector.push_back(lg::table(lg::quote(subtilePassableFlags)));

      //cout << ", ";
    }
    //cout << endl;

    string tile_solids_str = lg::params(tile_solids_vector);
    string solid_str = lg::line(lg::tilesetSlotEntry("solid", {"light-grass", "land"}, {tile_solids_str}));

    tile_slots_vector.push_back(solid_str);
  }

  string tile_slots_str = lg::params(tile_slots_vector);
  string lua_tileset_str = lg::DefineTileset(name, image, {tile_slots_str});

  //cout << lua_tileset_str << endl;

  lua_tileset_stream << lua_tileset_str;
  lua_tileset_stream.close();

  //cout << "num_doodad: " << num_doodad << endl;
  //cout << "num_normal: " << num_normal << endl;
}

} /* namespace tileset */
