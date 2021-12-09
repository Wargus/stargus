// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "sprites_dat.h"

sprites_dat_t::sprites_dat_t(uint16_t p_num_lines, uint16_t p_num_decorations, kaitai::kstream* p__io, kaitai::kstruct* p__parent, sprites_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_num_lines = p_num_lines;
    m_num_decorations = p_num_decorations;
    m_image_file = 0;
    m_heath_bar = 0;
    m_unknown2 = 0;
    m_is_visible = 0;
    m_select_circle_image_size = 0;
    m_select_circle_vertical_pos = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void sprites_dat_t::_read() {
    int l_image_file = num_lines();
    m_image_file = new std::vector<uint16_t>();
    m_image_file->reserve(l_image_file);
    for (int i = 0; i < l_image_file; i++) {
        m_image_file->push_back(m__io->read_u2le());
    }
    int l_heath_bar = (num_lines() - num_decorations());
    m_heath_bar = new std::vector<uint8_t>();
    m_heath_bar->reserve(l_heath_bar);
    for (int i = 0; i < l_heath_bar; i++) {
        m_heath_bar->push_back(m__io->read_u1());
    }
    int l_unknown2 = num_lines();
    m_unknown2 = new std::vector<uint8_t>();
    m_unknown2->reserve(l_unknown2);
    for (int i = 0; i < l_unknown2; i++) {
        m_unknown2->push_back(m__io->read_u1());
    }
    int l_is_visible = num_lines();
    m_is_visible = new std::vector<uint8_t>();
    m_is_visible->reserve(l_is_visible);
    for (int i = 0; i < l_is_visible; i++) {
        m_is_visible->push_back(m__io->read_u1());
    }
    int l_select_circle_image_size = (num_lines() - num_decorations());
    m_select_circle_image_size = new std::vector<uint8_t>();
    m_select_circle_image_size->reserve(l_select_circle_image_size);
    for (int i = 0; i < l_select_circle_image_size; i++) {
        m_select_circle_image_size->push_back(m__io->read_u1());
    }
    int l_select_circle_vertical_pos = (num_lines() - num_decorations());
    m_select_circle_vertical_pos = new std::vector<uint8_t>();
    m_select_circle_vertical_pos->reserve(l_select_circle_vertical_pos);
    for (int i = 0; i < l_select_circle_vertical_pos; i++) {
        m_select_circle_vertical_pos->push_back(m__io->read_u1());
    }
}

sprites_dat_t::~sprites_dat_t() {
    _clean_up();
}

void sprites_dat_t::_clean_up() {
    if (m_image_file) {
        delete m_image_file; m_image_file = 0;
    }
    if (m_heath_bar) {
        delete m_heath_bar; m_heath_bar = 0;
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
