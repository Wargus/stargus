// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "orders_dat.h"

orders_dat_t::orders_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, orders_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_label = 0;
    m_use_weapon_targeting = 0;
    m_unknown2 = 0;
    m_unknown3 = 0;
    m_unknown4 = 0;
    m_unknown5 = 0;
    m_interruptible = 0;
    m_unknown7 = 0;
    m_queueable = 0;
    m_unknown9 = 0;
    m_unknown10 = 0;
    m_unknown11 = 0;
    m_unknown12 = 0;
    m_targeting = 0;
    m_energy = 0;
    m_animation = 0;
    m_highlight = 0;
    m_unknown17 = 0;
    m_obscured_order = 0;
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

void orders_dat_t::_read() {
    m_label = new std::vector<uint16_t>();
    const int l_label = num_lines();
    for (int i = 0; i < l_label; i++) {
        m_label->push_back(m__io->read_u2le());
    }
    m_use_weapon_targeting = new std::vector<uint8_t>();
    const int l_use_weapon_targeting = num_lines();
    for (int i = 0; i < l_use_weapon_targeting; i++) {
        m_use_weapon_targeting->push_back(m__io->read_u1());
    }
    m_unknown2 = new std::vector<uint8_t>();
    const int l_unknown2 = num_lines();
    for (int i = 0; i < l_unknown2; i++) {
        m_unknown2->push_back(m__io->read_u1());
    }
    m_unknown3 = new std::vector<uint8_t>();
    const int l_unknown3 = num_lines();
    for (int i = 0; i < l_unknown3; i++) {
        m_unknown3->push_back(m__io->read_u1());
    }
    m_unknown4 = new std::vector<uint8_t>();
    const int l_unknown4 = num_lines();
    for (int i = 0; i < l_unknown4; i++) {
        m_unknown4->push_back(m__io->read_u1());
    }
    m_unknown5 = new std::vector<uint8_t>();
    const int l_unknown5 = num_lines();
    for (int i = 0; i < l_unknown5; i++) {
        m_unknown5->push_back(m__io->read_u1());
    }
    m_interruptible = new std::vector<uint8_t>();
    const int l_interruptible = num_lines();
    for (int i = 0; i < l_interruptible; i++) {
        m_interruptible->push_back(m__io->read_u1());
    }
    m_unknown7 = new std::vector<uint8_t>();
    const int l_unknown7 = num_lines();
    for (int i = 0; i < l_unknown7; i++) {
        m_unknown7->push_back(m__io->read_u1());
    }
    m_queueable = new std::vector<uint8_t>();
    const int l_queueable = num_lines();
    for (int i = 0; i < l_queueable; i++) {
        m_queueable->push_back(m__io->read_u1());
    }
    m_unknown9 = new std::vector<uint8_t>();
    const int l_unknown9 = num_lines();
    for (int i = 0; i < l_unknown9; i++) {
        m_unknown9->push_back(m__io->read_u1());
    }
    m_unknown10 = new std::vector<uint8_t>();
    const int l_unknown10 = num_lines();
    for (int i = 0; i < l_unknown10; i++) {
        m_unknown10->push_back(m__io->read_u1());
    }
    m_unknown11 = new std::vector<uint8_t>();
    const int l_unknown11 = num_lines();
    for (int i = 0; i < l_unknown11; i++) {
        m_unknown11->push_back(m__io->read_u1());
    }
    m_unknown12 = new std::vector<uint8_t>();
    const int l_unknown12 = num_lines();
    for (int i = 0; i < l_unknown12; i++) {
        m_unknown12->push_back(m__io->read_u1());
    }
    m_targeting = new std::vector<uint8_t>();
    const int l_targeting = num_lines();
    for (int i = 0; i < l_targeting; i++) {
        m_targeting->push_back(m__io->read_u1());
    }
    m_energy = new std::vector<uint8_t>();
    const int l_energy = num_lines();
    for (int i = 0; i < l_energy; i++) {
        m_energy->push_back(m__io->read_u1());
    }
    m_animation = new std::vector<uint8_t>();
    const int l_animation = num_lines();
    for (int i = 0; i < l_animation; i++) {
        m_animation->push_back(m__io->read_u1());
    }
    m_highlight = new std::vector<uint16_t>();
    const int l_highlight = num_lines();
    for (int i = 0; i < l_highlight; i++) {
        m_highlight->push_back(m__io->read_u2le());
    }
    m_unknown17 = new std::vector<uint16_t>();
    const int l_unknown17 = num_lines();
    for (int i = 0; i < l_unknown17; i++) {
        m_unknown17->push_back(m__io->read_u2le());
    }
    m_obscured_order = new std::vector<uint8_t>();
    const int l_obscured_order = num_lines();
    for (int i = 0; i < l_obscured_order; i++) {
        m_obscured_order->push_back(m__io->read_u1());
    }
}

orders_dat_t::~orders_dat_t() {
    _clean_up();
}

void orders_dat_t::_clean_up() {
    if (m_label) {
        delete m_label; m_label = 0;
    }
    if (m_use_weapon_targeting) {
        delete m_use_weapon_targeting; m_use_weapon_targeting = 0;
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
    if (m_unknown5) {
        delete m_unknown5; m_unknown5 = 0;
    }
    if (m_interruptible) {
        delete m_interruptible; m_interruptible = 0;
    }
    if (m_unknown7) {
        delete m_unknown7; m_unknown7 = 0;
    }
    if (m_queueable) {
        delete m_queueable; m_queueable = 0;
    }
    if (m_unknown9) {
        delete m_unknown9; m_unknown9 = 0;
    }
    if (m_unknown10) {
        delete m_unknown10; m_unknown10 = 0;
    }
    if (m_unknown11) {
        delete m_unknown11; m_unknown11 = 0;
    }
    if (m_unknown12) {
        delete m_unknown12; m_unknown12 = 0;
    }
    if (m_targeting) {
        delete m_targeting; m_targeting = 0;
    }
    if (m_energy) {
        delete m_energy; m_energy = 0;
    }
    if (m_animation) {
        delete m_animation; m_animation = 0;
    }
    if (m_highlight) {
        delete m_highlight; m_highlight = 0;
    }
    if (m_unknown17) {
        delete m_unknown17; m_unknown17 = 0;
    }
    if (m_obscured_order) {
        delete m_obscured_order; m_obscured_order = 0;
    }
}

int32_t orders_dat_t::num_lines() {
    if (f_num_lines)
        return m_num_lines;
    m_num_lines = (file_size() / record_size());
    f_num_lines = true;
    return m_num_lines;
}

int8_t orders_dat_t::record_size() {
    if (f_record_size)
        return m_record_size;
    m_record_size = 22;
    f_record_size = true;
    return m_record_size;
}

int32_t orders_dat_t::file_size() {
    if (f_file_size)
        return m_file_size;
    m_file_size = _io()->size();
    f_file_size = true;
    return m_file_size;
}
