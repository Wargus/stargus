// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "portdata_dat.h"

portdata_dat_t::portdata_dat_t(uint8_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent, portdata_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_num_lines = p_num_lines;
    m_portrait_file = 0;
    m_smk_change = 0;
    m_unknown1 = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void portdata_dat_t::_read() {
    int l_portrait_file = num_lines();
    m_portrait_file = new std::vector<uint32_t>();
    m_portrait_file->reserve(l_portrait_file);
    for (int i = 0; i < l_portrait_file; i++) {
        m_portrait_file->push_back(m__io->read_u4le());
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
    if (m_portrait_file) {
        delete m_portrait_file; m_portrait_file = 0;
    }
    if (m_smk_change) {
        delete m_smk_change; m_smk_change = 0;
    }
    if (m_unknown1) {
        delete m_unknown1; m_unknown1 = 0;
    }
}
