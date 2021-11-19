#ifndef UNITS_DAT_H_
#define UNITS_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class units_dat_t : public kaitai::kstruct {

public:

    units_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, units_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~units_dat_t();

private:
    std::vector<uint8_t>* m_graphic_id;
    std::vector<uint8_t>* m_subunit1;
    std::vector<uint8_t>* m_subunit2;
    std::vector<uint8_t>* m_subunit3;
    std::vector<uint32_t>* m_contruction_animation;
    std::vector<uint8_t>* m_unknown1;
    std::vector<uint8_t>* m_shield_enable;
    std::vector<uint16_t>* m_shields;
    std::vector<uint32_t>* m_hitpoints;
    std::vector<uint8_t>* m_animation_level;
    std::vector<uint8_t>* m_movement_type;
    std::vector<uint8_t>* m_rank;
    std::vector<uint8_t>* m_primary_special_ability;
    std::vector<uint8_t>* m_secondary_special_ability;
    std::vector<uint8_t>* m_type;
    std::vector<uint8_t>* m_unknown5;
    std::vector<uint8_t>* m_unknown6;
    std::vector<uint8_t>* m_groundweapon;
    std::vector<uint8_t>* m_airweapon;
    std::vector<uint8_t>* m_unknown7;
    std::vector<uint32_t>* m_special_ability_flags;
    std::vector<uint8_t>* m_unknown8;
    std::vector<uint8_t>* m_sightrange;
    std::vector<uint8_t>* m_armor_upgrade_group;
    std::vector<uint8_t>* m_size;
    std::vector<uint8_t>* m_armor;
    std::vector<uint8_t>* m_mineral_right_click;
    std::vector<uint16_t>* m_sounds;
    std::vector<uint16_t>* m_width;
    std::vector<uint16_t>* m_height;
    std::vector<uint16_t>* m_circle_width;
    std::vector<uint16_t>* m_circle_height;
    std::vector<uint16_t>* m_portrait;
    std::vector<uint16_t>* m_mineral_cost;
    std::vector<uint16_t>* m_gas_cost;
    std::vector<uint16_t>* m_build_time;
    std::vector<uint16_t>* m_restrictions;
    std::vector<uint8_t>* m_unit_group;
    std::vector<uint8_t>* m_food_produced;
    std::vector<uint8_t>* m_food_costs;
    std::vector<uint8_t>* m_transport_space;
    std::vector<uint16_t>* m_building_score;
    std::vector<uint16_t>* m_destroying_score;
    std::vector<uint8_t>* m_unknown14;
    std::vector<uint16_t>* m_unknown15;
    units_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<uint8_t>* graphic_id() const { return m_graphic_id; }
    std::vector<uint8_t>* subunit1() const { return m_subunit1; }
    std::vector<uint8_t>* subunit2() const { return m_subunit2; }
    std::vector<uint8_t>* subunit3() const { return m_subunit3; }
    std::vector<uint32_t>* contruction_animation() const { return m_contruction_animation; }
    std::vector<uint8_t>* unknown1() const { return m_unknown1; }
    std::vector<uint8_t>* shield_enable() const { return m_shield_enable; }
    std::vector<uint16_t>* shields() const { return m_shields; }
    std::vector<uint32_t>* hitpoints() const { return m_hitpoints; }
    std::vector<uint8_t>* animation_level() const { return m_animation_level; }
    std::vector<uint8_t>* movement_type() const { return m_movement_type; }
    std::vector<uint8_t>* rank() const { return m_rank; }
    std::vector<uint8_t>* primary_special_ability() const { return m_primary_special_ability; }
    std::vector<uint8_t>* secondary_special_ability() const { return m_secondary_special_ability; }
    std::vector<uint8_t>* type() const { return m_type; }
    std::vector<uint8_t>* unknown5() const { return m_unknown5; }
    std::vector<uint8_t>* unknown6() const { return m_unknown6; }
    std::vector<uint8_t>* groundweapon() const { return m_groundweapon; }
    std::vector<uint8_t>* airweapon() const { return m_airweapon; }
    std::vector<uint8_t>* unknown7() const { return m_unknown7; }
    std::vector<uint32_t>* special_ability_flags() const { return m_special_ability_flags; }
    std::vector<uint8_t>* unknown8() const { return m_unknown8; }
    std::vector<uint8_t>* sightrange() const { return m_sightrange; }
    std::vector<uint8_t>* armor_upgrade_group() const { return m_armor_upgrade_group; }
    std::vector<uint8_t>* size() const { return m_size; }
    std::vector<uint8_t>* armor() const { return m_armor; }
    std::vector<uint8_t>* mineral_right_click() const { return m_mineral_right_click; }
    std::vector<uint16_t>* sounds() const { return m_sounds; }
    std::vector<uint16_t>* width() const { return m_width; }
    std::vector<uint16_t>* height() const { return m_height; }
    std::vector<uint16_t>* circle_width() const { return m_circle_width; }
    std::vector<uint16_t>* circle_height() const { return m_circle_height; }
    std::vector<uint16_t>* portrait() const { return m_portrait; }
    std::vector<uint16_t>* mineral_cost() const { return m_mineral_cost; }
    std::vector<uint16_t>* gas_cost() const { return m_gas_cost; }
    std::vector<uint16_t>* build_time() const { return m_build_time; }
    std::vector<uint16_t>* restrictions() const { return m_restrictions; }
    std::vector<uint8_t>* unit_group() const { return m_unit_group; }
    std::vector<uint8_t>* food_produced() const { return m_food_produced; }
    std::vector<uint8_t>* food_costs() const { return m_food_costs; }
    std::vector<uint8_t>* transport_space() const { return m_transport_space; }
    std::vector<uint16_t>* building_score() const { return m_building_score; }
    std::vector<uint16_t>* destroying_score() const { return m_destroying_score; }
    std::vector<uint8_t>* unknown14() const { return m_unknown14; }
    std::vector<uint16_t>* unknown15() const { return m_unknown15; }
    units_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // UNITS_DAT_H_
