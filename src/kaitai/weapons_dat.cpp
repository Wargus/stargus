// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "weapons_dat.h"

weapons_dat_t::weapons_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, weapons_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_label = 0;
    m_graphics = 0;
    m_special_attack = 0;
    m_attack_type = 0;
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

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void weapons_dat_t::_read() {
    int l_label = 100;
    m_label = new std::vector<uint16_t>();
    m_label->reserve(l_label);
    for (int i = 0; i < l_label; i++) {
        m_label->push_back(m__io->read_u2le());
    }
    int l_graphics = 100;
    m_graphics = new std::vector<uint32_t>();
    m_graphics->reserve(l_graphics);
    for (int i = 0; i < l_graphics; i++) {
        m_graphics->push_back(m__io->read_u4le());
    }
    int l_special_attack = 100;
    m_special_attack = new std::vector<uint8_t>();
    m_special_attack->reserve(l_special_attack);
    for (int i = 0; i < l_special_attack; i++) {
        m_special_attack->push_back(m__io->read_u1());
    }
    int l_attack_type = 100;
    m_attack_type = new std::vector<attack_type_enum_t>();
    m_attack_type->reserve(l_attack_type);
    for (int i = 0; i < l_attack_type; i++) {
        m_attack_type->push_back(static_cast<weapons_dat_t::attack_type_enum_t>(m__io->read_u2le()));
    }
    int l_minimum_range = 100;
    m_minimum_range = new std::vector<uint32_t>();
    m_minimum_range->reserve(l_minimum_range);
    for (int i = 0; i < l_minimum_range; i++) {
        m_minimum_range->push_back(m__io->read_u4le());
    }
    int l_maximum_range = 100;
    m_maximum_range = new std::vector<uint32_t>();
    m_maximum_range->reserve(l_maximum_range);
    for (int i = 0; i < l_maximum_range; i++) {
        m_maximum_range->push_back(m__io->read_u4le());
    }
    int l_damage_upgrade = 100;
    m_damage_upgrade = new std::vector<uint8_t>();
    m_damage_upgrade->reserve(l_damage_upgrade);
    for (int i = 0; i < l_damage_upgrade; i++) {
        m_damage_upgrade->push_back(m__io->read_u1());
    }
    int l_weapon_type = 100;
    m_weapon_type = new std::vector<weapon_type_enum_t>();
    m_weapon_type->reserve(l_weapon_type);
    for (int i = 0; i < l_weapon_type; i++) {
        m_weapon_type->push_back(static_cast<weapons_dat_t::weapon_type_enum_t>(m__io->read_u1()));
    }
    int l_weapon_behaviour = 100;
    m_weapon_behaviour = new std::vector<uint8_t>();
    m_weapon_behaviour->reserve(l_weapon_behaviour);
    for (int i = 0; i < l_weapon_behaviour; i++) {
        m_weapon_behaviour->push_back(m__io->read_u1());
    }
    int l_remove_after = 100;
    m_remove_after = new std::vector<uint8_t>();
    m_remove_after->reserve(l_remove_after);
    for (int i = 0; i < l_remove_after; i++) {
        m_remove_after->push_back(m__io->read_u1());
    }
    int l_explosive_type = 100;
    m_explosive_type = new std::vector<uint8_t>();
    m_explosive_type->reserve(l_explosive_type);
    for (int i = 0; i < l_explosive_type; i++) {
        m_explosive_type->push_back(m__io->read_u1());
    }
    int l_inner_splash_range = 100;
    m_inner_splash_range = new std::vector<uint16_t>();
    m_inner_splash_range->reserve(l_inner_splash_range);
    for (int i = 0; i < l_inner_splash_range; i++) {
        m_inner_splash_range->push_back(m__io->read_u2le());
    }
    int l_medium_splash_range = 100;
    m_medium_splash_range = new std::vector<uint16_t>();
    m_medium_splash_range->reserve(l_medium_splash_range);
    for (int i = 0; i < l_medium_splash_range; i++) {
        m_medium_splash_range->push_back(m__io->read_u2le());
    }
    int l_outer_splash_range = 100;
    m_outer_splash_range = new std::vector<uint16_t>();
    m_outer_splash_range->reserve(l_outer_splash_range);
    for (int i = 0; i < l_outer_splash_range; i++) {
        m_outer_splash_range->push_back(m__io->read_u2le());
    }
    int l_damage_amount = 100;
    m_damage_amount = new std::vector<uint16_t>();
    m_damage_amount->reserve(l_damage_amount);
    for (int i = 0; i < l_damage_amount; i++) {
        m_damage_amount->push_back(m__io->read_u2le());
    }
    int l_damage_bonus = 100;
    m_damage_bonus = new std::vector<uint16_t>();
    m_damage_bonus->reserve(l_damage_bonus);
    for (int i = 0; i < l_damage_bonus; i++) {
        m_damage_bonus->push_back(m__io->read_u2le());
    }
    int l_weapon_cooldown = 100;
    m_weapon_cooldown = new std::vector<uint8_t>();
    m_weapon_cooldown->reserve(l_weapon_cooldown);
    for (int i = 0; i < l_weapon_cooldown; i++) {
        m_weapon_cooldown->push_back(m__io->read_u1());
    }
    int l_damage_factor = 100;
    m_damage_factor = new std::vector<uint8_t>();
    m_damage_factor->reserve(l_damage_factor);
    for (int i = 0; i < l_damage_factor; i++) {
        m_damage_factor->push_back(m__io->read_u1());
    }
    int l_attack_angle = 100;
    m_attack_angle = new std::vector<uint8_t>();
    m_attack_angle->reserve(l_attack_angle);
    for (int i = 0; i < l_attack_angle; i++) {
        m_attack_angle->push_back(m__io->read_u1());
    }
    int l_launch_spin = 100;
    m_launch_spin = new std::vector<uint8_t>();
    m_launch_spin->reserve(l_launch_spin);
    for (int i = 0; i < l_launch_spin; i++) {
        m_launch_spin->push_back(m__io->read_u1());
    }
    int l_x_offset = 100;
    m_x_offset = new std::vector<uint8_t>();
    m_x_offset->reserve(l_x_offset);
    for (int i = 0; i < l_x_offset; i++) {
        m_x_offset->push_back(m__io->read_u1());
    }
    int l_y_offset = 100;
    m_y_offset = new std::vector<uint8_t>();
    m_y_offset->reserve(l_y_offset);
    for (int i = 0; i < l_y_offset; i++) {
        m_y_offset->push_back(m__io->read_u1());
    }
    int l_error_message = 100;
    m_error_message = new std::vector<uint16_t>();
    m_error_message->reserve(l_error_message);
    for (int i = 0; i < l_error_message; i++) {
        m_error_message->push_back(m__io->read_u2le());
    }
    int l_icon = 100;
    m_icon = new std::vector<uint16_t>();
    m_icon->reserve(l_icon);
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
    if (m_special_attack) {
        delete m_special_attack; m_special_attack = 0;
    }
    if (m_attack_type) {
        delete m_attack_type; m_attack_type = 0;
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
