// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "tileset_vf4.h"

tileset_vf4_t::tileset_vf4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, tileset_vf4_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_id = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void tileset_vf4_t::_read() {
    m_id = new std::vector<minitile_flags_t*>();
    {
        int i = 0;
        while (!m__io->is_eof()) {
            m_id->push_back(new minitile_flags_t(m__io, this, m__root));
            i++;
        }
    }
}

tileset_vf4_t::~tileset_vf4_t() {
    _clean_up();
}

void tileset_vf4_t::_clean_up() {
    if (m_id) {
        for (std::vector<minitile_flags_t*>::iterator it = m_id->begin(); it != m_id->end(); ++it) {
            delete *it;
        }
        delete m_id; m_id = 0;
    }
}

tileset_vf4_t::minitile_flags_t::minitile_flags_t(kaitai::kstream* p__io, tileset_vf4_t* p__parent, tileset_vf4_t* p__root) : kaitai::kstruct(p__io) {
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

void tileset_vf4_t::minitile_flags_t::_read() {
    int l_flags = 16;
    m_flags = new std::vector<uint16_t>();
    m_flags->reserve(l_flags);
    for (int i = 0; i < l_flags; i++) {
        m_flags->push_back(m__io->read_u2le());
    }
}

tileset_vf4_t::minitile_flags_t::~minitile_flags_t() {
    _clean_up();
}

void tileset_vf4_t::minitile_flags_t::_clean_up() {
    if (m_flags) {
        delete m_flags; m_flags = 0;
    }
}
