// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "file_tbl.h"

file_tbl_t::file_tbl_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, file_tbl_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_ofs_files = 0;
    m_tbl_entries = 0;
    f_tbl_entries = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void file_tbl_t::_read() {
    m_num_offsets = m__io->read_s2le();
    int l_ofs_files = num_offsets();
    m_ofs_files = new std::vector<int16_t>();
    m_ofs_files->reserve(l_ofs_files);
    for (int i = 0; i < l_ofs_files; i++) {
        m_ofs_files->push_back(m__io->read_s2le());
    }
}

file_tbl_t::~file_tbl_t() {
    _clean_up();
}

void file_tbl_t::_clean_up() {
    if (m_ofs_files) {
        delete m_ofs_files; m_ofs_files = 0;
    }
    if (f_tbl_entries) {
        if (m_tbl_entries) {
            for (std::vector<tbl_entry_t*>::iterator it = m_tbl_entries->begin(); it != m_tbl_entries->end(); ++it) {
                delete *it;
            }
            delete m_tbl_entries; m_tbl_entries = 0;
        }
    }
}

file_tbl_t::tbl_entry_t::tbl_entry_t(int16_t p_i, kaitai::kstream* p__io, file_tbl_t* p__parent, file_tbl_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_i = p_i;
    f_entry = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void file_tbl_t::tbl_entry_t::_read() {
}

file_tbl_t::tbl_entry_t::~tbl_entry_t() {
    _clean_up();
}

void file_tbl_t::tbl_entry_t::_clean_up() {
    if (f_entry) {
    }
}

std::string file_tbl_t::tbl_entry_t::entry() {
    if (f_entry)
        return m_entry;
    std::streampos _pos = m__io->pos();
    m__io->seek(_parent()->ofs_files()->at(i()));
    m_entry = kaitai::kstream::bytes_to_str(m__io->read_bytes((_parent()->ofs_files()->at((i() + 1)) - _parent()->ofs_files()->at(i()))), std::string("ASCII"));
    m__io->seek(_pos);
    f_entry = true;
    return m_entry;
}

std::vector<file_tbl_t::tbl_entry_t*>* file_tbl_t::tbl_entries() {
    if (f_tbl_entries)
        return m_tbl_entries;
    int l_tbl_entries = (num_offsets() - 1);
    m_tbl_entries = new std::vector<tbl_entry_t*>();
    m_tbl_entries->reserve(l_tbl_entries);
    for (int i = 0; i < l_tbl_entries; i++) {
        m_tbl_entries->push_back(new tbl_entry_t(i, m__io, this, m__root));
    }
    f_tbl_entries = true;
    return m_tbl_entries;
}
