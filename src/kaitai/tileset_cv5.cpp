// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "tileset_cv5.h"

tileset_cv5_t::tileset_cv5_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, tileset_cv5_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_element = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_cv5_t::_read() {
    m_element = new std::vector<group_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_element->push_back(new group_t(m__io, this, m__root));
            i++;
        }
    }
}

tileset_cv5_t::~tileset_cv5_t() {
    _clean_up();
}

void tileset_cv5_t::_clean_up() {
    if (m_element) {
        for (std::vector<group_t*>::iterator it = m_element->begin(); it != m_element->end(); ++it) {
            delete *it;
        }
        delete m_element; m_element = 0;
    }
}

tileset_cv5_t::group_t::group_t(kaitai::kstream* p__io, tileset_cv5_t* p__parent, tileset_cv5_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_ground = 0;
    m_megatile_references = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_cv5_t::group_t::_read() {
    m_doodad = m__io->read_u2le();
    m_ground = new ground_nibbles_t(m__io, this, m__root);
    m_unknown1 = m__io->read_u2le();
    m_unknown2 = m__io->read_u2le();
    m_unknown3 = m__io->read_u2le();
    m_unknown4 = m__io->read_u2le();
    m_unknown5 = m__io->read_u2le();
    m_unknown6 = m__io->read_u2le();
    m_unknown7 = m__io->read_u2le();
    m_unknown8 = m__io->read_u2le();
    int l_megatile_references = 16;
    m_megatile_references = new std::vector<uint16_t>();
    m_megatile_references->reserve(l_megatile_references);
    for (int i = 0; i < l_megatile_references; i++) {
        m_megatile_references->push_back(m__io->read_u2le());
    }
}

tileset_cv5_t::group_t::~group_t() {
    _clean_up();
}

void tileset_cv5_t::group_t::_clean_up() {
    if (m_ground) {
        delete m_ground; m_ground = 0;
    }
    if (m_megatile_references) {
        delete m_megatile_references; m_megatile_references = 0;
    }
}

tileset_cv5_t::ground_nibbles_t::ground_nibbles_t(kaitai::kstream* p__io, tileset_cv5_t::group_t* p__parent, tileset_cv5_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_cv5_t::ground_nibbles_t::_read() {
    m_one = m__io->read_bits_int_le(4);
    m_two = m__io->read_bits_int_le(4);
    m_tree = m__io->read_bits_int_le(4);
    m_four = m__io->read_bits_int_le(4);
}

tileset_cv5_t::ground_nibbles_t::~ground_nibbles_t() {
    _clean_up();
}

void tileset_cv5_t::ground_nibbles_t::_clean_up() {
}
