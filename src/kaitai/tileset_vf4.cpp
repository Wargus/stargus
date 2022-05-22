// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "tileset_vf4.h"

tileset_vf4_t::tileset_vf4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, tileset_vf4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_elements = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_vf4_t::_read() {
    m_elements = new std::vector<minitile_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_elements->push_back(new minitile_t(m__io, this, m__root));
            i++;
        }
    }
}

tileset_vf4_t::~tileset_vf4_t() {
    _clean_up();
}

void tileset_vf4_t::_clean_up() {
    if (m_elements) {
        for (std::vector<minitile_t*>::iterator it = m_elements->begin(); it != m_elements->end(); ++it) {
            delete *it;
        }
        delete m_elements; m_elements = 0;
    }
}

tileset_vf4_t::minitile_t::minitile_t(kaitai::kstream* p__io, tileset_vf4_t* p__parent, tileset_vf4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_flags = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_vf4_t::minitile_t::_read() {
    int l_flags = 16;
    m_flags = new std::vector<minitile_flags_t*>();
    m_flags->reserve(l_flags);
    for (int i = 0; i < l_flags; i++) {
        m_flags->push_back(new minitile_flags_t(m__io, this, m__root));
    }
}

tileset_vf4_t::minitile_t::~minitile_t() {
    _clean_up();
}

void tileset_vf4_t::minitile_t::_clean_up() {
    if (m_flags) {
        for (std::vector<minitile_flags_t*>::iterator it = m_flags->begin(); it != m_flags->end(); ++it) {
            delete *it;
        }
        delete m_flags; m_flags = 0;
    }
}

tileset_vf4_t::minitile_flags_t::minitile_flags_t(kaitai::kstream* p__io, tileset_vf4_t::minitile_t* p__parent, tileset_vf4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_vf4_t::minitile_flags_t::_read() {
    m_walkable = m__io->read_bits_int_le(1);
    m_mid_elevation = m__io->read_bits_int_le(1);
    m_high_elevation = m__io->read_bits_int_le(1);
    m_blocks_view = m__io->read_bits_int_le(1);
    m_ramp = m__io->read_bits_int_le(1);
    m__unnamed5 = m__io->read_bits_int_le(3);
}

tileset_vf4_t::minitile_flags_t::~minitile_flags_t() {
    _clean_up();
}

void tileset_vf4_t::minitile_flags_t::_clean_up() {
}
