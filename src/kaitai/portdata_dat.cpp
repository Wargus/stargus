// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "portdata_dat.h"

portdata_dat_t::portdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, portdata_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_video_idle = 0;
    m_video_talking = 0;
    m_change_idle = 0;
    m_change_talking = 0;
    m_unknown1_idle = 0;
    m_unknown1_talking = 0;
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

void portdata_dat_t::_read() {
    m_video_idle = new std::vector<uint32_t>();
    const int l_video_idle = (num_lines() / 2);
    for (int i = 0; i < l_video_idle; i++) {
        m_video_idle->push_back(m__io->read_u4le());
    }
    m_video_talking = new std::vector<uint32_t>();
    const int l_video_talking = (num_lines() / 2);
    for (int i = 0; i < l_video_talking; i++) {
        m_video_talking->push_back(m__io->read_u4le());
    }
    m_change_idle = new std::vector<uint8_t>();
    const int l_change_idle = (num_lines() / 2);
    for (int i = 0; i < l_change_idle; i++) {
        m_change_idle->push_back(m__io->read_u1());
    }
    m_change_talking = new std::vector<uint8_t>();
    const int l_change_talking = (num_lines() / 2);
    for (int i = 0; i < l_change_talking; i++) {
        m_change_talking->push_back(m__io->read_u1());
    }
    m_unknown1_idle = new std::vector<uint8_t>();
    const int l_unknown1_idle = (num_lines() / 2);
    for (int i = 0; i < l_unknown1_idle; i++) {
        m_unknown1_idle->push_back(m__io->read_u1());
    }
    m_unknown1_talking = new std::vector<uint8_t>();
    const int l_unknown1_talking = (num_lines() / 2);
    for (int i = 0; i < l_unknown1_talking; i++) {
        m_unknown1_talking->push_back(m__io->read_u1());
    }
}

portdata_dat_t::~portdata_dat_t() {
    _clean_up();
}

void portdata_dat_t::_clean_up() {
    if (m_video_idle) {
        delete m_video_idle; m_video_idle = 0;
    }
    if (m_video_talking) {
        delete m_video_talking; m_video_talking = 0;
    }
    if (m_change_idle) {
        delete m_change_idle; m_change_idle = 0;
    }
    if (m_change_talking) {
        delete m_change_talking; m_change_talking = 0;
    }
    if (m_unknown1_idle) {
        delete m_unknown1_idle; m_unknown1_idle = 0;
    }
    if (m_unknown1_talking) {
        delete m_unknown1_talking; m_unknown1_talking = 0;
    }
}

int32_t portdata_dat_t::num_lines() {
    if (f_num_lines)
        return m_num_lines;
    m_num_lines = (file_size() / record_size());
    f_num_lines = true;
    return m_num_lines;
}

int8_t portdata_dat_t::record_size() {
    if (f_record_size)
        return m_record_size;
    m_record_size = 6;
    f_record_size = true;
    return m_record_size;
}

int32_t portdata_dat_t::file_size() {
    if (f_file_size)
        return m_file_size;
    m_file_size = _io()->size();
    f_file_size = true;
    return m_file_size;
}
