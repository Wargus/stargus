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
    m_flags = new std::vector<minitile_flags_types_t*>();
    m_flags->reserve(l_flags);
    for (int i = 0; i < l_flags; i++) {
        m_flags->push_back(new minitile_flags_types_t(m__io, this, m__root));
    }
}

tileset_vf4_t::minitile_t::~minitile_t() {
    _clean_up();
}

void tileset_vf4_t::minitile_t::_clean_up() {
    if (m_flags) {
        for (std::vector<minitile_flags_types_t*>::iterator it = m_flags->begin(); it != m_flags->end(); ++it) {
            delete *it;
        }
        delete m_flags; m_flags = 0;
    }
}

tileset_vf4_t::minitile_flags_types_t::minitile_flags_types_t(kaitai::kstream* p__io, tileset_vf4_t::minitile_t* p__parent, tileset_vf4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_walkable = false;
    f_blocks_view = false;
    f_mid_elevation = false;
    f_ramp = false;
    f_high_elevation = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_vf4_t::minitile_flags_types_t::_read() {
    m_flags_raw = m__io->read_u2le();
}

tileset_vf4_t::minitile_flags_types_t::~minitile_flags_types_t() {
    _clean_up();
}

void tileset_vf4_t::minitile_flags_types_t::_clean_up() {
}

int32_t tileset_vf4_t::minitile_flags_types_t::walkable() {
    if (f_walkable)
        return m_walkable;
    m_walkable = (flags_raw() & 1);
    f_walkable = true;
    return m_walkable;
}

int32_t tileset_vf4_t::minitile_flags_types_t::blocks_view() {
    if (f_blocks_view)
        return m_blocks_view;
    m_blocks_view = (flags_raw() & 8);
    f_blocks_view = true;
    return m_blocks_view;
}

int32_t tileset_vf4_t::minitile_flags_types_t::mid_elevation() {
    if (f_mid_elevation)
        return m_mid_elevation;
    m_mid_elevation = (flags_raw() & 2);
    f_mid_elevation = true;
    return m_mid_elevation;
}

int32_t tileset_vf4_t::minitile_flags_types_t::ramp() {
    if (f_ramp)
        return m_ramp;
    m_ramp = (flags_raw() & 16);
    f_ramp = true;
    return m_ramp;
}

int32_t tileset_vf4_t::minitile_flags_types_t::high_elevation() {
    if (f_high_elevation)
        return m_high_elevation;
    m_high_elevation = (flags_raw() & 4);
    f_high_elevation = true;
    return m_high_elevation;
}
