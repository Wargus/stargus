#ifndef MAPDATA_DAT_H_
#define MAPDATA_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class mapdata_dat_t : public kaitai::kstruct {

public:

    mapdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, mapdata_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~mapdata_dat_t();

private:
    std::vector<uint32_t>* m_mission_dir;
    mapdata_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * Path where the game will look for the original campaigns map file ("staredit/scenario.chk") and the WAV files ("staredit/wav/").
     */
    std::vector<uint32_t>* mission_dir() const { return m_mission_dir; }
    mapdata_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // MAPDATA_DAT_H_
