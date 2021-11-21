// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "weapons_dat.h"

weapons_dat_t::weapons_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, weapons_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_weapon_label = 0;
    m_missile_sprite = 0;
    m_special_attack = 0;
    m_attack_type = 0;
    m_minimum_range = 0;
    m_maximum_range = 0;
    m_upgrade_group = 0;
    m_weapon_type = 0;
    m_weapon_behaviour = 0;
    m_missile_type = 0;
    m_explosive_type = 0;
    m_splash_minimum = 0;
    m_splash_medium = 0;
    m_splash_maximum = 0;
    m_damage = 0;
    m_bonus = 0;
    m_delay = 0;
    m_factor = 0;
    m_coordinate_group1 = 0;
    m_coordinate_group2 = 0;
    m_error_message = 0;
    m_weapon_icon = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void weapons_dat_t::_read() {
    int l_weapon_label = 100;
    m_weapon_label = new std::vector<uint16_t>();
    m_weapon_label->reserve(l_weapon_label);
    for (int i = 0; i < l_weapon_label; i++) {
        m_weapon_label->push_back(m__io->read_u2le());
    }
    int l_missile_sprite = 100;
    m_missile_sprite = new std::vector<uint32_t>();
    m_missile_sprite->reserve(l_missile_sprite);
    for (int i = 0; i < l_missile_sprite; i++) {
        m_missile_sprite->push_back(m__io->read_u4le());
    }
    int l_special_attack = 100;
    m_special_attack = new std::vector<uint8_t>();
    m_special_attack->reserve(l_special_attack);
    for (int i = 0; i < l_special_attack; i++) {
        m_special_attack->push_back(m__io->read_u1());
    }
    int l_attack_type = 100;
    m_attack_type = new std::vector<attack_type_value_t>();
    m_attack_type->reserve(l_attack_type);
    for (int i = 0; i < l_attack_type; i++) {
        m_attack_type->push_back(static_cast<weapons_dat_t::attack_type_value_t>(m__io->read_u2le()));
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
    int l_upgrade_group = 100;
    m_upgrade_group = new std::vector<uint8_t>();
    m_upgrade_group->reserve(l_upgrade_group);
    for (int i = 0; i < l_upgrade_group; i++) {
        m_upgrade_group->push_back(m__io->read_u1());
    }
    int l_weapon_type = 100;
    m_weapon_type = new std::vector<uint8_t>();
    m_weapon_type->reserve(l_weapon_type);
    for (int i = 0; i < l_weapon_type; i++) {
        m_weapon_type->push_back(m__io->read_u1());
    }
    int l_weapon_behaviour = 100;
    m_weapon_behaviour = new std::vector<uint8_t>();
    m_weapon_behaviour->reserve(l_weapon_behaviour);
    for (int i = 0; i < l_weapon_behaviour; i++) {
        m_weapon_behaviour->push_back(m__io->read_u1());
    }
    int l_missile_type = 100;
    m_missile_type = new std::vector<uint8_t>();
    m_missile_type->reserve(l_missile_type);
    for (int i = 0; i < l_missile_type; i++) {
        m_missile_type->push_back(m__io->read_u1());
    }
    int l_explosive_type = 100;
    m_explosive_type = new std::vector<uint8_t>();
    m_explosive_type->reserve(l_explosive_type);
    for (int i = 0; i < l_explosive_type; i++) {
        m_explosive_type->push_back(m__io->read_u1());
    }
    int l_splash_minimum = 100;
    m_splash_minimum = new std::vector<uint16_t>();
    m_splash_minimum->reserve(l_splash_minimum);
    for (int i = 0; i < l_splash_minimum; i++) {
        m_splash_minimum->push_back(m__io->read_u2le());
    }
    int l_splash_medium = 100;
    m_splash_medium = new std::vector<uint16_t>();
    m_splash_medium->reserve(l_splash_medium);
    for (int i = 0; i < l_splash_medium; i++) {
        m_splash_medium->push_back(m__io->read_u2le());
    }
    int l_splash_maximum = 100;
    m_splash_maximum = new std::vector<uint16_t>();
    m_splash_maximum->reserve(l_splash_maximum);
    for (int i = 0; i < l_splash_maximum; i++) {
        m_splash_maximum->push_back(m__io->read_u2le());
    }
    int l_damage = 100;
    m_damage = new std::vector<uint16_t>();
    m_damage->reserve(l_damage);
    for (int i = 0; i < l_damage; i++) {
        m_damage->push_back(m__io->read_u2le());
    }
    int l_bonus = 100;
    m_bonus = new std::vector<uint16_t>();
    m_bonus->reserve(l_bonus);
    for (int i = 0; i < l_bonus; i++) {
        m_bonus->push_back(m__io->read_u2le());
    }
    int l_delay = 100;
    m_delay = new std::vector<uint8_t>();
    m_delay->reserve(l_delay);
    for (int i = 0; i < l_delay; i++) {
        m_delay->push_back(m__io->read_u1());
    }
    int l_factor = 100;
    m_factor = new std::vector<uint8_t>();
    m_factor->reserve(l_factor);
    for (int i = 0; i < l_factor; i++) {
        m_factor->push_back(m__io->read_u1());
    }
    int l_coordinate_group1 = 100;
    m_coordinate_group1 = new std::vector<coordinate_group_type_t*>();
    m_coordinate_group1->reserve(l_coordinate_group1);
    for (int i = 0; i < l_coordinate_group1; i++) {
        m_coordinate_group1->push_back(new coordinate_group_type_t(m__io, this, m__root));
    }
    int l_coordinate_group2 = 100;
    m_coordinate_group2 = new std::vector<coordinate_group_type_t*>();
    m_coordinate_group2->reserve(l_coordinate_group2);
    for (int i = 0; i < l_coordinate_group2; i++) {
        m_coordinate_group2->push_back(new coordinate_group_type_t(m__io, this, m__root));
    }
    int l_error_message = 100;
    m_error_message = new std::vector<uint16_t>();
    m_error_message->reserve(l_error_message);
    for (int i = 0; i < l_error_message; i++) {
        m_error_message->push_back(m__io->read_u2le());
    }
    int l_weapon_icon = 100;
    m_weapon_icon = new std::vector<uint16_t>();
    m_weapon_icon->reserve(l_weapon_icon);
    for (int i = 0; i < l_weapon_icon; i++) {
        m_weapon_icon->push_back(m__io->read_u2le());
    }
}

weapons_dat_t::~weapons_dat_t() {
    _clean_up();
}

void weapons_dat_t::_clean_up() {
    if (m_weapon_label) {
        delete m_weapon_label; m_weapon_label = 0;
    }
    if (m_missile_sprite) {
        delete m_missile_sprite; m_missile_sprite = 0;
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
    if (m_upgrade_group) {
        delete m_upgrade_group; m_upgrade_group = 0;
    }
    if (m_weapon_type) {
        delete m_weapon_type; m_weapon_type = 0;
    }
    if (m_weapon_behaviour) {
        delete m_weapon_behaviour; m_weapon_behaviour = 0;
    }
    if (m_missile_type) {
        delete m_missile_type; m_missile_type = 0;
    }
    if (m_explosive_type) {
        delete m_explosive_type; m_explosive_type = 0;
    }
    if (m_splash_minimum) {
        delete m_splash_minimum; m_splash_minimum = 0;
    }
    if (m_splash_medium) {
        delete m_splash_medium; m_splash_medium = 0;
    }
    if (m_splash_maximum) {
        delete m_splash_maximum; m_splash_maximum = 0;
    }
    if (m_damage) {
        delete m_damage; m_damage = 0;
    }
    if (m_bonus) {
        delete m_bonus; m_bonus = 0;
    }
    if (m_delay) {
        delete m_delay; m_delay = 0;
    }
    if (m_factor) {
        delete m_factor; m_factor = 0;
    }
    if (m_coordinate_group1) {
        for (std::vector<coordinate_group_type_t*>::iterator it = m_coordinate_group1->begin(); it != m_coordinate_group1->end(); ++it) {
            delete *it;
        }
        delete m_coordinate_group1; m_coordinate_group1 = 0;
    }
    if (m_coordinate_group2) {
        for (std::vector<coordinate_group_type_t*>::iterator it = m_coordinate_group2->begin(); it != m_coordinate_group2->end(); ++it) {
            delete *it;
        }
        delete m_coordinate_group2; m_coordinate_group2 = 0;
    }
    if (m_error_message) {
        delete m_error_message; m_error_message = 0;
    }
    if (m_weapon_icon) {
        delete m_weapon_icon; m_weapon_icon = 0;
    }
}

weapons_dat_t::coordinate_group_type_t::coordinate_group_type_t(kaitai::kstream* p__io, weapons_dat_t* p__parent, weapons_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void weapons_dat_t::coordinate_group_type_t::_read() {
    m_x = m__io->read_u1();
    m_y = m__io->read_u1();
}

weapons_dat_t::coordinate_group_type_t::~coordinate_group_type_t() {
    _clean_up();
}

void weapons_dat_t::coordinate_group_type_t::_clean_up() {
}
