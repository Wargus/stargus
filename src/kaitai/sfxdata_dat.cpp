// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "sfxdata_dat.h"

sfxdata_dat_t::sfxdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, sfxdata_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_sound_file = 0;
    m_unknown1 = 0;
    m_unknown2 = 0;
    m_unknown3 = 0;
    m_unknown4 = 0;
    f_num_lines = false;
    f_record_size = false;
    f_file_size = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void sfxdata_dat_t::_read() {
    m_sound_file = new std::vector<uint32_t>();
    const int l_sound_file = num_lines();
    for (int i = 0; i < l_sound_file; i++) {
        m_sound_file->push_back(m__io->read_u4le());
    }
    m_unknown1 = new std::vector<uint8_t>();
    const int l_unknown1 = num_lines();
    for (int i = 0; i < l_unknown1; i++) {
        m_unknown1->push_back(m__io->read_u1());
    }
    m_unknown2 = new std::vector<uint8_t>();
    const int l_unknown2 = num_lines();
    for (int i = 0; i < l_unknown2; i++) {
        m_unknown2->push_back(m__io->read_u1());
    }
    m_unknown3 = new std::vector<uint16_t>();
    const int l_unknown3 = num_lines();
    for (int i = 0; i < l_unknown3; i++) {
        m_unknown3->push_back(m__io->read_u2le());
    }
    m_unknown4 = new std::vector<uint8_t>();
    const int l_unknown4 = num_lines();
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

int32_t sfxdata_dat_t::num_lines() {
    if (f_num_lines)
        return m_num_lines;
    m_num_lines = (file_size() / record_size());
    f_num_lines = true;
    return m_num_lines;
}

int8_t sfxdata_dat_t::record_size() {
    if (f_record_size)
        return m_record_size;
    m_record_size = 9;
    f_record_size = true;
    return m_record_size;
}

int32_t sfxdata_dat_t::file_size() {
    if (f_file_size)
        return m_file_size;
    m_file_size = _io()->size();
    f_file_size = true;
    return m_file_size;
}
