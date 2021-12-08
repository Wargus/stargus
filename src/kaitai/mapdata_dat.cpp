// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "mapdata_dat.h"

mapdata_dat_t::mapdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, mapdata_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_mission_dir = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void mapdata_dat_t::_read() {
    m_mission_dir = new std::vector<uint32_t>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_mission_dir->push_back(m__io->read_u4le());
            i++;
        }
    }
}

mapdata_dat_t::~mapdata_dat_t() {
    _clean_up();
}

void mapdata_dat_t::_clean_up() {
    if (m_mission_dir) {
        delete m_mission_dir; m_mission_dir = 0;
    }
}
