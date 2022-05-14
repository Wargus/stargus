// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "tileset_dddata_bin.h"

tileset_dddata_bin_t::tileset_dddata_bin_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, tileset_dddata_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_doodad = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_dddata_bin_t::_read() {
    m_doodad = new std::vector<doodad_type_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_doodad->push_back(new doodad_type_t(m__io, this, m__root));
            i++;
        }
    }
}

tileset_dddata_bin_t::~tileset_dddata_bin_t() {
    _clean_up();
}

void tileset_dddata_bin_t::_clean_up() {
    if (m_doodad) {
        for (std::vector<doodad_type_t*>::iterator it = m_doodad->begin(); it != m_doodad->end(); ++it) {
            delete *it;
        }
        delete m_doodad; m_doodad = 0;
    }
}

tileset_dddata_bin_t::doodad_type_t::doodad_type_t(kaitai::kstream* p__io, tileset_dddata_bin_t* p__parent, tileset_dddata_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_placing = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_dddata_bin_t::doodad_type_t::_read() {
    int l_placing = 512;
    m_placing = new std::vector<uint16_t>();
    m_placing->reserve(l_placing);
    for (int i = 0; i < l_placing; i++) {
        m_placing->push_back(m__io->read_u2le());
    }
}

tileset_dddata_bin_t::doodad_type_t::~doodad_type_t() {
    _clean_up();
}

void tileset_dddata_bin_t::doodad_type_t::_clean_up() {
    if (m_placing) {
        delete m_placing; m_placing = 0;
    }
}
