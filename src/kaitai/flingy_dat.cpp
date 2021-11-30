// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "flingy_dat.h"

flingy_dat_t::flingy_dat_t(bool p_has_unused, bool p_has_movement_control, kaitai::kstream* p__io, kaitai::kstruct* p__parent, flingy_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_has_unused = p_has_unused;
    m_has_movement_control = p_has_movement_control;
    m_sprite = 0;
    m_speed = 0;
    m_acceleration = 0;
    m_halt_distance = 0;
    m_turn_radius = 0;
    m_unused = 0;
    m_movement_control = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void flingy_dat_t::_read() {
    int l_sprite = 209;
    m_sprite = new std::vector<uint16_t>();
    m_sprite->reserve(l_sprite);
    for (int i = 0; i < l_sprite; i++) {
        m_sprite->push_back(m__io->read_u2le());
    }
    int l_speed = 209;
    m_speed = new std::vector<uint32_t>();
    m_speed->reserve(l_speed);
    for (int i = 0; i < l_speed; i++) {
        m_speed->push_back(m__io->read_u4le());
    }
    int l_acceleration = 209;
    m_acceleration = new std::vector<uint16_t>();
    m_acceleration->reserve(l_acceleration);
    for (int i = 0; i < l_acceleration; i++) {
        m_acceleration->push_back(m__io->read_u2le());
    }
    int l_halt_distance = 209;
    m_halt_distance = new std::vector<uint32_t>();
    m_halt_distance->reserve(l_halt_distance);
    for (int i = 0; i < l_halt_distance; i++) {
        m_halt_distance->push_back(m__io->read_u4le());
    }
    int l_turn_radius = 209;
    m_turn_radius = new std::vector<uint8_t>();
    m_turn_radius->reserve(l_turn_radius);
    for (int i = 0; i < l_turn_radius; i++) {
        m_turn_radius->push_back(m__io->read_u1());
    }
    n_unused = true;
    if (has_unused() == true) {
        n_unused = false;
        int l_unused = 209;
        m_unused = new std::vector<uint8_t>();
        m_unused->reserve(l_unused);
        for (int i = 0; i < l_unused; i++) {
            m_unused->push_back(m__io->read_u1());
        }
    }
    n_movement_control = true;
    if (has_movement_control() == true) {
        n_movement_control = false;
        int l_movement_control = 209;
        m_movement_control = new std::vector<uint8_t>();
        m_movement_control->reserve(l_movement_control);
        for (int i = 0; i < l_movement_control; i++) {
            m_movement_control->push_back(m__io->read_u1());
        }
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
    if (!n_unused) {
        if (m_unused) {
            delete m_unused; m_unused = 0;
        }
    }
    if (!n_movement_control) {
        if (m_movement_control) {
            delete m_movement_control; m_movement_control = 0;
        }
    }
}
