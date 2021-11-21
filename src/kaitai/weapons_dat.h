#ifndef WEAPONS_DAT_H_
#define WEAPONS_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class weapons_dat_t : public kaitai::kstruct {

public:
    class coordinate_group_type_t;

    enum attack_type_value_t {
        ATTACK_TYPE_VALUE_AIR_ONLY = 1,
        ATTACK_TYPE_VALUE_GROUND_ONLY = 2,
        ATTACK_TYPE_VALUE_GROUND_AND_AIR = 3,
        ATTACK_TYPE_VALUE_UNITS_ONLY = 4,
        ATTACK_TYPE_VALUE_GROUND_UNITS_ONLY = 18
    };

    weapons_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, weapons_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~weapons_dat_t();

    class coordinate_group_type_t : public kaitai::kstruct {

    public:

        coordinate_group_type_t(kaitai::kstream* p__io, weapons_dat_t* p__parent = 0, weapons_dat_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~coordinate_group_type_t();

    private:
        uint8_t m_x;
        uint8_t m_y;
        weapons_dat_t* m__root;
        weapons_dat_t* m__parent;

    public:
        uint8_t x() const { return m_x; }
        uint8_t y() const { return m_y; }
        weapons_dat_t* _root() const { return m__root; }
        weapons_dat_t* _parent() const { return m__parent; }
    };

private:
    std::vector<uint16_t>* m_weapon_label;
    std::vector<uint32_t>* m_missile_sprite;
    std::vector<uint8_t>* m_special_attack;
    std::vector<attack_type_value_t>* m_attack_type;
    std::vector<uint32_t>* m_minimum_range;
    std::vector<uint32_t>* m_maximum_range;
    std::vector<uint8_t>* m_upgrade_group;
    std::vector<uint8_t>* m_weapon_type;
    std::vector<uint8_t>* m_weapon_behaviour;
    std::vector<uint8_t>* m_missile_type;
    std::vector<uint8_t>* m_explosive_type;
    std::vector<uint16_t>* m_splash_minimum;
    std::vector<uint16_t>* m_splash_medium;
    std::vector<uint16_t>* m_splash_maximum;
    std::vector<uint16_t>* m_damage;
    std::vector<uint16_t>* m_bonus;
    std::vector<uint8_t>* m_delay;
    std::vector<uint8_t>* m_factor;
    std::vector<coordinate_group_type_t*>* m_coordinate_group1;
    std::vector<coordinate_group_type_t*>* m_coordinate_group2;
    std::vector<uint16_t>* m_error_message;
    std::vector<uint16_t>* m_weapon_icon;
    weapons_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<uint16_t>* weapon_label() const { return m_weapon_label; }
    std::vector<uint32_t>* missile_sprite() const { return m_missile_sprite; }
    std::vector<uint8_t>* special_attack() const { return m_special_attack; }
    std::vector<attack_type_value_t>* attack_type() const { return m_attack_type; }
    std::vector<uint32_t>* minimum_range() const { return m_minimum_range; }
    std::vector<uint32_t>* maximum_range() const { return m_maximum_range; }
    std::vector<uint8_t>* upgrade_group() const { return m_upgrade_group; }
    std::vector<uint8_t>* weapon_type() const { return m_weapon_type; }
    std::vector<uint8_t>* weapon_behaviour() const { return m_weapon_behaviour; }
    std::vector<uint8_t>* missile_type() const { return m_missile_type; }
    std::vector<uint8_t>* explosive_type() const { return m_explosive_type; }
    std::vector<uint16_t>* splash_minimum() const { return m_splash_minimum; }
    std::vector<uint16_t>* splash_medium() const { return m_splash_medium; }
    std::vector<uint16_t>* splash_maximum() const { return m_splash_maximum; }
    std::vector<uint16_t>* damage() const { return m_damage; }
    std::vector<uint16_t>* bonus() const { return m_bonus; }
    std::vector<uint8_t>* delay() const { return m_delay; }
    std::vector<uint8_t>* factor() const { return m_factor; }
    std::vector<coordinate_group_type_t*>* coordinate_group1() const { return m_coordinate_group1; }
    std::vector<coordinate_group_type_t*>* coordinate_group2() const { return m_coordinate_group2; }
    std::vector<uint16_t>* error_message() const { return m_error_message; }
    std::vector<uint16_t>* weapon_icon() const { return m_weapon_icon; }
    weapons_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // WEAPONS_DAT_H_
