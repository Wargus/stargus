// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "tileset_vx4.h"

tileset_vx4_t::tileset_vx4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, tileset_vx4_t* p__root) : kaitai::kstruct(p__io) {
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

void tileset_vx4_t::_read() {
    m_elements = new std::vector<megatile_type_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_elements->push_back(new megatile_type_t(m__io, this, m__root));
            i++;
        }
    }
}

tileset_vx4_t::~tileset_vx4_t() {
    _clean_up();
}

void tileset_vx4_t::_clean_up() {
    if (m_elements) {
        for (std::vector<megatile_type_t*>::iterator it = m_elements->begin(); it != m_elements->end(); ++it) {
            delete *it;
        }
        delete m_elements; m_elements = 0;
    }
}

tileset_vx4_t::megatile_type_t::megatile_type_t(kaitai::kstream* p__io, tileset_vx4_t* p__parent, tileset_vx4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_graphic_ref = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_vx4_t::megatile_type_t::_read() {
    int l_graphic_ref = 16;
    m_graphic_ref = new std::vector<graphic_ref_type_t*>();
    m_graphic_ref->reserve(l_graphic_ref);
    for (int i = 0; i < l_graphic_ref; i++) {
        m_graphic_ref->push_back(new graphic_ref_type_t(m__io, this, m__root));
    }
}

tileset_vx4_t::megatile_type_t::~megatile_type_t() {
    _clean_up();
}

void tileset_vx4_t::megatile_type_t::_clean_up() {
    if (m_graphic_ref) {
        for (std::vector<graphic_ref_type_t*>::iterator it = m_graphic_ref->begin(); it != m_graphic_ref->end(); ++it) {
            delete *it;
        }
        delete m_graphic_ref; m_graphic_ref = 0;
    }
}

tileset_vx4_t::graphic_ref_type_t::graphic_ref_type_t(kaitai::kstream* p__io, tileset_vx4_t::megatile_type_t* p__parent, tileset_vx4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    f_vr4_ref = false;
    f_horizontal_flip = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_vx4_t::graphic_ref_type_t::_read() {
    m_vr4_ref_flip_raw = m__io->read_u2le();
}

tileset_vx4_t::graphic_ref_type_t::~graphic_ref_type_t() {
    _clean_up();
}

void tileset_vx4_t::graphic_ref_type_t::_clean_up() {
}

int32_t tileset_vx4_t::graphic_ref_type_t::vr4_ref() {
    if (f_vr4_ref)
        return m_vr4_ref;
    m_vr4_ref = (vr4_ref_flip_raw() >> 1);
    f_vr4_ref = true;
    return m_vr4_ref;
}

int32_t tileset_vx4_t::graphic_ref_type_t::horizontal_flip() {
    if (f_horizontal_flip)
        return m_horizontal_flip;
    m_horizontal_flip = (vr4_ref_flip_raw() & 1);
    f_horizontal_flip = true;
    return m_horizontal_flip;
}
