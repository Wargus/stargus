// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "sfxdata_dat.h"

sfxdata_dat_t::sfxdata_dat_t(uint16_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent, sfxdata_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_num_lines = p_num_lines;
    m_sound_file = 0;
    m_unknown1 = 0;
    m_unknown2 = 0;
    m_unknown3 = 0;
    m_unknown4 = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void sfxdata_dat_t::_read() {
    int l_sound_file = num_lines();
    m_sound_file = new std::vector<uint32_t>();
    m_sound_file->reserve(l_sound_file);
    for (int i = 0; i < l_sound_file; i++) {
        m_sound_file->push_back(m__io->read_u4le());
    }
    int l_unknown1 = num_lines();
    m_unknown1 = new std::vector<uint8_t>();
    m_unknown1->reserve(l_unknown1);
    for (int i = 0; i < l_unknown1; i++) {
        m_unknown1->push_back(m__io->read_u1());
    }
    int l_unknown2 = num_lines();
    m_unknown2 = new std::vector<uint8_t>();
    m_unknown2->reserve(l_unknown2);
    for (int i = 0; i < l_unknown2; i++) {
        m_unknown2->push_back(m__io->read_u1());
    }
    int l_unknown3 = num_lines();
    m_unknown3 = new std::vector<uint16_t>();
    m_unknown3->reserve(l_unknown3);
    for (int i = 0; i < l_unknown3; i++) {
        m_unknown3->push_back(m__io->read_u2le());
    }
    int l_unknown4 = num_lines();
    m_unknown4 = new std::vector<uint8_t>();
    m_unknown4->reserve(l_unknown4);
    for (int i = 0; i < l_unknown4; i++) {
        m_unknown4->push_back(m__io->read_u1());
    }
}

sfxdata_dat_t::~sfxdata_dat_t() {
    _clean_up();
}

void sfxdata_dat_t::_clean_up() {
    if (m_sound_file) {
        delete m_sound_file; m_sound_file = 0;
    }
    if (m_unknown1) {
        delete m_unknown1; m_unknown1 = 0;
    }
    if (m_unknown2) {
        delete m_unknown2; m_unknown2 = 0;
    }
    if (m_unknown3) {
        delete m_unknown3; m_unknown3 = 0;
    }
    if (m_unknown4) {
        delete m_unknown4; m_unknown4 = 0;
    }
}
