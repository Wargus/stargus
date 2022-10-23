// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "sprites_dat.h"

sprites_dat_t::sprites_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, sprites_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_image = 0;
    m_health_bar = 0;
    m_unknown2 = 0;
    m_is_visible = 0;
    m_select_circle_image_size = 0;
    m_select_circle_vertical_pos = 0;
    f_file_size_rest = false;
    f_file_size_first_130 = false;
    f_num_lines = false;
    f_file_size = false;
    f_record_size = false;
    f_record_size_first_130 = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void sprites_dat_t::_read() {
    m_image = new std::vector<uint16_t>();
    const int l_image = num_lines();
    for (int i = 0; i < l_image; i++) {
        m_image->push_back(m__io->read_u2le());
    }
    m_health_bar = new std::vector<uint8_t>();
    const int l_health_bar = (num_lines() - 130);
    for (int i = 0; i < l_health_bar; i++) {
        m_health_bar->push_back(m__io->read_u1());
    }
    m_unknown2 = new std::vector<uint8_t>();
    const int l_unknown2 = num_lines();
    for (int i = 0; i < l_unknown2; i++) {
        m_unknown2->push_back(m__io->read_u1());
    }
    m_is_visible = new std::vector<uint8_t>();
    const int l_is_visible = num_lines();
    for (int i = 0; i < l_is_visible; i++) {
        m_is_visible->push_back(m__io->read_u1());
    }
    m_select_circle_image_size = new std::vector<uint8_t>();
    const int l_select_circle_image_size = (num_lines() - 130);
    for (int i = 0; i < l_select_circle_image_size; i++) {
        m_select_circle_image_size->push_back(m__io->read_u1());
    }
    m_select_circle_vertical_pos = new std::vector<uint8_t>();
    const int l_select_circle_vertical_pos = (num_lines() - 130);
    for (int i = 0; i < l_select_circle_vertical_pos; i++) {
        m_select_circle_vertical_pos->push_back(m__io->read_u1());
    }
}

sprites_dat_t::~sprites_dat_t() {
    _clean_up();
}

void sprites_dat_t::_clean_up() {
    if (m_image) {
        delete m_image; m_image = 0;
    }
    if (m_health_bar) {
        delete m_health_bar; m_health_bar = 0;
    }
    if (m_unknown2) {
        delete m_unknown2; m_unknown2 = 0;
    }
    if (m_is_visible) {
        delete m_is_visible; m_is_visible = 0;
    }
    if (m_select_circle_image_size) {
        delete m_select_circle_image_size; m_select_circle_image_size = 0;
    }
    if (m_select_circle_vertical_pos) {
        delete m_select_circle_vertical_pos; m_select_circle_vertical_pos = 0;
    }
}

int32_t sprites_dat_t::file_size_rest() {
    if (f_file_size_rest)
        return m_file_size_rest;
    m_file_size_rest = (file_size() - file_size_first_130());
    f_file_size_rest = true;
    return m_file_size_rest;
}

int32_t sprites_dat_t::file_size_first_130() {
    if (f_file_size_first_130)
        return m_file_size_first_130;
    m_file_size_first_130 = (record_size_first_130() * 130);
    f_file_size_first_130 = true;
    return m_file_size_first_130;
}

int32_t sprites_dat_t::num_lines() {
    if (f_num_lines)
        return m_num_lines;
    m_num_lines = ((file_size_rest() / record_size()) + 130);
    f_num_lines = true;
    return m_num_lines;
}

int32_t sprites_dat_t::file_size() {
    if (f_file_size)
        return m_file_size;
    m_file_size = _io()->size();
    f_file_size = true;
    return m_file_size;
}

int8_t sprites_dat_t::record_size() {
    if (f_record_size)
        return m_record_size;
    m_record_size = 7;
    f_record_size = true;
    return m_record_size;
}

int8_t sprites_dat_t::record_size_first_130() {
    if (f_record_size_first_130)
        return m_record_size_first_130;
    m_record_size_first_130 = 4;
    f_record_size_first_130 = true;
    return m_record_size_first_130;
}
