// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "portdata_dat.h"

portdata_dat_t::portdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, portdata_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_video = 0;
    m_smk_change = 0;
    m_unknown1 = 0;
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
    int l_video = num_lines();
    m_video = new std::vector<uint32_t>();
    m_video->reserve(l_video);
    for (int i = 0; i < l_video; i++) {
        m_video->push_back(m__io->read_u4le());
    }
    int l_smk_change = num_lines();
    m_smk_change = new std::vector<uint8_t>();
    m_smk_change->reserve(l_smk_change);
    for (int i = 0; i < l_smk_change; i++) {
        m_smk_change->push_back(m__io->read_u1());
    }
    int l_unknown1 = num_lines();
    m_unknown1 = new std::vector<uint8_t>();
    m_unknown1->reserve(l_unknown1);
    for (int i = 0; i < l_unknown1; i++) {
        m_unknown1->push_back(m__io->read_u1());
    }
}

portdata_dat_t::~portdata_dat_t() {
    _clean_up();
}

void portdata_dat_t::_clean_up() {
    if (m_video) {
        delete m_video; m_video = 0;
    }
    if (m_smk_change) {
        delete m_smk_change; m_smk_change = 0;
    }
    if (m_unknown1) {
        delete m_unknown1; m_unknown1 = 0;
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
