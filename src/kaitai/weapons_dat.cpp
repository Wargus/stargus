// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "weapons_dat.h"

weapons_dat_t::weapons_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, weapons_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_label = 0;
    m_graphics = 0;
    m_explosion = 0;
    m_target_flags = 0;
    m_minimum_range = 0;
    m_maximum_range = 0;
    m_damage_upgrade = 0;
    m_weapon_type = 0;
    m_weapon_behaviour = 0;
    m_remove_after = 0;
    m_explosive_type = 0;
    m_inner_splash_range = 0;
    m_medium_splash_range = 0;
    m_outer_splash_range = 0;
    m_damage_amount = 0;
    m_damage_bonus = 0;
    m_weapon_cooldown = 0;
    m_damage_factor = 0;
    m_attack_angle = 0;
    m_launch_spin = 0;
    m_x_offset = 0;
    m_y_offset = 0;
    m_error_message = 0;
    m_icon = 0;
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

void weapons_dat_t::_read() {
    m_label = new std::vector<uint16_t>();
    const int l_label = num_lines();
    for (int i = 0; i < l_label; i++) {
        m_label->push_back(m__io->read_u2le());
    }
    m_graphics = new std::vector<uint32_t>();
    const int l_graphics = num_lines();
    for (int i = 0; i < l_graphics; i++) {
        m_graphics->push_back(m__io->read_u4le());
    }
    m_explosion = new std::vector<uint8_t>();
    const int l_explosion = num_lines();
    for (int i = 0; i < l_explosion; i++) {
        m_explosion->push_back(m__io->read_u1());
    }
    m_target_flags = new std::vector<attack_type_enum_t>();
    const int l_target_flags = num_lines();
    for (int i = 0; i < l_target_flags; i++) {
        m_target_flags->push_back(static_cast<weapons_dat_t::attack_type_enum_t>(m__io->read_u2le()));
    }
    m_minimum_range = new std::vector<uint32_t>();
    const int l_minimum_range = num_lines();
    for (int i = 0; i < l_minimum_range; i++) {
        m_minimum_range->push_back(m__io->read_u4le());
    }
    m_maximum_range = new std::vector<uint32_t>();
    const int l_maximum_range = num_lines();
    for (int i = 0; i < l_maximum_range; i++) {
        m_maximum_range->push_back(m__io->read_u4le());
    }
    m_damage_upgrade = new std::vector<uint8_t>();
    const int l_damage_upgrade = num_lines();
    for (int i = 0; i < l_damage_upgrade; i++) {
        m_damage_upgrade->push_back(m__io->read_u1());
    }
    m_weapon_type = new std::vector<weapon_type_enum_t>();
    const int l_weapon_type = num_lines();
    for (int i = 0; i < l_weapon_type; i++) {
        m_weapon_type->push_back(static_cast<weapons_dat_t::weapon_type_enum_t>(m__io->read_u1()));
    }
    m_weapon_behaviour = new std::vector<uint8_t>();
    const int l_weapon_behaviour = num_lines();
    for (int i = 0; i < l_weapon_behaviour; i++) {
        m_weapon_behaviour->push_back(m__io->read_u1());
    }
    m_remove_after = new std::vector<uint8_t>();
    const int l_remove_after = num_lines();
    for (int i = 0; i < l_remove_after; i++) {
        m_remove_after->push_back(m__io->read_u1());
    }
    m_explosive_type = new std::vector<uint8_t>();
    const int l_explosive_type = num_lines();
    for (int i = 0; i < l_explosive_type; i++) {
        m_explosive_type->push_back(m__io->read_u1());
    }
    m_inner_splash_range = new std::vector<uint16_t>();
    const int l_inner_splash_range = num_lines();
    for (int i = 0; i < l_inner_splash_range; i++) {
        m_inner_splash_range->push_back(m__io->read_u2le());
    }
    m_medium_splash_range = new std::vector<uint16_t>();
    const int l_medium_splash_range = num_lines();
    for (int i = 0; i < l_medium_splash_range; i++) {
        m_medium_splash_range->push_back(m__io->read_u2le());
    }
    m_outer_splash_range = new std::vector<uint16_t>();
    const int l_outer_splash_range = num_lines();
    for (int i = 0; i < l_outer_splash_range; i++) {
        m_outer_splash_range->push_back(m__io->read_u2le());
    }
    m_damage_amount = new std::vector<uint16_t>();
    const int l_damage_amount = num_lines();
    for (int i = 0; i < l_damage_amount; i++) {
        m_damage_amount->push_back(m__io->read_u2le());
    }
    m_damage_bonus = new std::vector<uint16_t>();
    const int l_damage_bonus = num_lines();
    for (int i = 0; i < l_damage_bonus; i++) {
        m_damage_bonus->push_back(m__io->read_u2le());
    }
    m_weapon_cooldown = new std::vector<uint8_t>();
    const int l_weapon_cooldown = num_lines();
    for (int i = 0; i < l_weapon_cooldown; i++) {
        m_weapon_cooldown->push_back(m__io->read_u1());
    }
    m_damage_factor = new std::vector<uint8_t>();
    const int l_damage_factor = num_lines();
    for (int i = 0; i < l_damage_factor; i++) {
        m_damage_factor->push_back(m__io->read_u1());
    }
    m_attack_angle = new std::vector<uint8_t>();
    const int l_attack_angle = num_lines();
    for (int i = 0; i < l_attack_angle; i++) {
        m_attack_angle->push_back(m__io->read_u1());
    }
    m_launch_spin = new std::vector<uint8_t>();
    const int l_launch_spin = num_lines();
    for (int i = 0; i < l_launch_spin; i++) {
        m_launch_spin->push_back(m__io->read_u1());
    }
    m_x_offset = new std::vector<uint8_t>();
    const int l_x_offset = num_lines();
    for (int i = 0; i < l_x_offset; i++) {
        m_x_offset->push_back(m__io->read_u1());
    }
    m_y_offset = new std::vector<uint8_t>();
    const int l_y_offset = num_lines();
    for (int i = 0; i < l_y_offset; i++) {
        m_y_offset->push_back(m__io->read_u1());
    }
    m_error_message = new std::vector<uint16_t>();
    const int l_error_message = num_lines();
    for (int i = 0; i < l_error_message; i++) {
        m_error_message->push_back(m__io->read_u2le());
    }
    m_icon = new std::vector<uint16_t>();
    const int l_icon = num_lines();
    for (int i = 0; i < l_icon; i++) {
        m_icon->push_back(m__io->read_u2le());
    }
}

weapons_dat_t::~weapons_dat_t() {
    _clean_up();
}

void weapons_dat_t::_clean_up() {
    if (m_label) {
        delete m_label; m_label = 0;
    }
    if (m_graphics) {
        delete m_graphics; m_graphics = 0;
    }
    if (m_explosion) {
        delete m_explosion; m_explosion = 0;
    }
    if (m_target_flags) {
        delete m_target_flags; m_target_flags = 0;
    }
    if (m_minimum_range) {
        delete m_minimum_range; m_minimum_range = 0;
    }
    if (m_maximum_range) {
        delete m_maximum_range; m_maximum_range = 0;
    }
    if (m_damage_upgrade) {
        delete m_damage_upgrade; m_damage_upgrade = 0;
    }
    if (m_weapon_type) {
        delete m_weapon_type; m_weapon_type = 0;
    }
    if (m_weapon_behaviour) {
        delete m_weapon_behaviour; m_weapon_behaviour = 0;
    }
    if (m_remove_after) {
        delete m_remove_after; m_remove_after = 0;
    }
    if (m_explosive_type) {
        delete m_explosive_type; m_explosive_type = 0;
    }
    if (m_inner_splash_range) {
        delete m_inner_splash_range; m_inner_splash_range = 0;
    }
    if (m_medium_splash_range) {
        delete m_medium_splash_range; m_medium_splash_range = 0;
    }
    if (m_outer_splash_range) {
        delete m_outer_splash_range; m_outer_splash_range = 0;
    }
    if (m_damage_amount) {
        delete m_damage_amount; m_damage_amount = 0;
    }
    if (m_damage_bonus) {
        delete m_damage_bonus; m_damage_bonus = 0;
    }
    if (m_weapon_cooldown) {
        delete m_weapon_cooldown; m_weapon_cooldown = 0;
    }
    if (m_damage_factor) {
        delete m_damage_factor; m_damage_factor = 0;
    }
    if (m_attack_angle) {
        delete m_attack_angle; m_attack_angle = 0;
    }
    if (m_launch_spin) {
        delete m_launch_spin; m_launch_spin = 0;
    }
    if (m_x_offset) {
        delete m_x_offset; m_x_offset = 0;
    }
    if (m_y_offset) {
        delete m_y_offset; m_y_offset = 0;
    }
    if (m_error_message) {
        delete m_error_message; m_error_message = 0;
    }
    if (m_icon) {
        delete m_icon; m_icon = 0;
    }
}

int32_t weapons_dat_t::num_lines() {
    if (f_num_lines)
        return m_num_lines;
    m_num_lines = (file_size() / record_size());
    f_num_lines = true;
    return m_num_lines;
}

int8_t weapons_dat_t::record_size() {
    if (f_record_size)
        return m_record_size;
    m_record_size = 42;
    f_record_size = true;
    return m_record_size;
}

int32_t weapons_dat_t::file_size() {
    if (f_file_size)
        return m_file_size;
    m_file_size = _io()->size();
    f_file_size = true;
    return m_file_size;
}
