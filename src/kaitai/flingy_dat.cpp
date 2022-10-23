// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "flingy_dat.h"

flingy_dat_t::flingy_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, flingy_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_sprite = 0;
    m_speed = 0;
    m_acceleration = 0;
    m_halt_distance = 0;
    m_turn_radius = 0;
    m_unused = 0;
    m_movement_control = 0;
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

void flingy_dat_t::_read() {
    m_sprite = new std::vector<uint16_t>();
    const int l_sprite = num_lines();
    for (int i = 0; i < l_sprite; i++) {
        m_sprite->push_back(m__io->read_u2le());
    }
    m_speed = new std::vector<uint32_t>();
    const int l_speed = num_lines();
    for (int i = 0; i < l_speed; i++) {
        m_speed->push_back(m__io->read_u4le());
    }
    m_acceleration = new std::vector<uint16_t>();
    const int l_acceleration = num_lines();
    for (int i = 0; i < l_acceleration; i++) {
        m_acceleration->push_back(m__io->read_u2le());
    }
    m_halt_distance = new std::vector<uint32_t>();
    const int l_halt_distance = num_lines();
    for (int i = 0; i < l_halt_distance; i++) {
        m_halt_distance->push_back(m__io->read_u4le());
    }
    m_turn_radius = new std::vector<uint8_t>();
    const int l_turn_radius = num_lines();
    for (int i = 0; i < l_turn_radius; i++) {
        m_turn_radius->push_back(m__io->read_u1());
    }
    m_unused = new std::vector<uint8_t>();
    const int l_unused = num_lines();
    for (int i = 0; i < l_unused; i++) {
        m_unused->push_back(m__io->read_u1());
    }
    m_movement_control = new std::vector<uint8_t>();
    const int l_movement_control = num_lines();
    for (int i = 0; i < l_movement_control; i++) {
        m_movement_control->push_back(m__io->read_u1());
    }
}

flingy_dat_t::~flingy_dat_t() {
    _clean_up();
}

void flingy_dat_t::_clean_up() {
    if (m_sprite) {
        delete m_sprite; m_sprite = 0;
    }
    if (m_speed) {
        delete m_speed; m_speed = 0;
    }
    if (m_acceleration) {
        delete m_acceleration; m_acceleration = 0;
    }
    if (m_halt_distance) {
        delete m_halt_distance; m_halt_distance = 0;
    }
    if (m_turn_radius) {
        delete m_turn_radius; m_turn_radius = 0;
    }
    if (m_unused) {
        delete m_unused; m_unused = 0;
    }
    if (m_movement_control) {
        delete m_movement_control; m_movement_control = 0;
    }
}

int32_t flingy_dat_t::num_lines() {
    if (f_num_lines)
        return m_num_lines;
    m_num_lines = (file_size() / record_size());
    f_num_lines = true;
    return m_num_lines;
}

int8_t flingy_dat_t::record_size() {
    if (f_record_size)
        return m_record_size;
    m_record_size = 15;
    f_record_size = true;
    return m_record_size;
}

int32_t flingy_dat_t::file_size() {
    if (f_file_size)
        return m_file_size;
    m_file_size = _io()->size();
    f_file_size = true;
    return m_file_size;
}
