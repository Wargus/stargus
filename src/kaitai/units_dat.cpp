// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "units_dat.h"

units_dat_t::units_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_graphic_id = 0;
    m_subunit1 = 0;
    m_subunit2 = 0;
    m_subunit3 = 0;
    m_contruction_animation = 0;
    m_unknown1 = 0;
    m_shield_enable = 0;
    m_shields = 0;
    m_hitpoints = 0;
    m_animation_level = 0;
    m_movement_type = 0;
    m_rank = 0;
    m_primary_special_ability = 0;
    m_secondary_special_ability = 0;
    m_type = 0;
    m_unknown5 = 0;
    m_unknown6 = 0;
    m_groundweapon = 0;
    m_airweapon = 0;
    m_unknown7 = 0;
    m_special_ability_flags = 0;
    m_unknown8 = 0;
    m_sightrange = 0;
    m_armor_upgrade_group = 0;
    m_size = 0;
    m_armor = 0;
    m_mineral_right_click = 0;
    m_sounds = 0;
    m_width = 0;
    m_height = 0;
    m_circle_width = 0;
    m_circle_height = 0;
    m_portrait = 0;
    m_mineral_cost = 0;
    m_gas_cost = 0;
    m_build_time = 0;
    m_restrictions = 0;
    m_unit_group = 0;
    m_food_produced = 0;
    m_food_costs = 0;
    m_transport_space = 0;
    m_building_score = 0;
    m_destroying_score = 0;
    m_unknown14 = 0;
    m_unknown15 = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::_read() {
    int l_graphic_id = 228;
    m_graphic_id = new std::vector<uint8_t>();
    m_graphic_id->reserve(l_graphic_id);
    for (int i = 0; i < l_graphic_id; i++) {
        m_graphic_id->push_back(m__io->read_u1());
    }
    int l_subunit1 = 456;
    m_subunit1 = new std::vector<uint8_t>();
    m_subunit1->reserve(l_subunit1);
    for (int i = 0; i < l_subunit1; i++) {
        m_subunit1->push_back(m__io->read_u1());
    }
    int l_subunit2 = 456;
    m_subunit2 = new std::vector<uint8_t>();
    m_subunit2->reserve(l_subunit2);
    for (int i = 0; i < l_subunit2; i++) {
        m_subunit2->push_back(m__io->read_u1());
    }
    int l_subunit3 = 192;
    m_subunit3 = new std::vector<uint8_t>();
    m_subunit3->reserve(l_subunit3);
    for (int i = 0; i < l_subunit3; i++) {
        m_subunit3->push_back(m__io->read_u1());
    }
    int l_contruction_animation = 228;
    m_contruction_animation = new std::vector<uint32_t>();
    m_contruction_animation->reserve(l_contruction_animation);
    for (int i = 0; i < l_contruction_animation; i++) {
        m_contruction_animation->push_back(m__io->read_u4le());
    }
    int l_unknown1 = 228;
    m_unknown1 = new std::vector<uint8_t>();
    m_unknown1->reserve(l_unknown1);
    for (int i = 0; i < l_unknown1; i++) {
        m_unknown1->push_back(m__io->read_u1());
    }
    int l_shield_enable = 228;
    m_shield_enable = new std::vector<uint8_t>();
    m_shield_enable->reserve(l_shield_enable);
    for (int i = 0; i < l_shield_enable; i++) {
        m_shield_enable->push_back(m__io->read_u1());
    }
    int l_shields = 228;
    m_shields = new std::vector<uint16_t>();
    m_shields->reserve(l_shields);
    for (int i = 0; i < l_shields; i++) {
        m_shields->push_back(m__io->read_u2le());
    }
    int l_hitpoints = 228;
    m_hitpoints = new std::vector<uint32_t>();
    m_hitpoints->reserve(l_hitpoints);
    for (int i = 0; i < l_hitpoints; i++) {
        m_hitpoints->push_back(m__io->read_u4le());
    }
    int l_animation_level = 228;
    m_animation_level = new std::vector<uint8_t>();
    m_animation_level->reserve(l_animation_level);
    for (int i = 0; i < l_animation_level; i++) {
        m_animation_level->push_back(m__io->read_u1());
    }
    int l_movement_type = 228;
    m_movement_type = new std::vector<uint8_t>();
    m_movement_type->reserve(l_movement_type);
    for (int i = 0; i < l_movement_type; i++) {
        m_movement_type->push_back(m__io->read_u1());
    }
    int l_rank = 228;
    m_rank = new std::vector<uint8_t>();
    m_rank->reserve(l_rank);
    for (int i = 0; i < l_rank; i++) {
        m_rank->push_back(m__io->read_u1());
    }
    int l_primary_special_ability = 228;
    m_primary_special_ability = new std::vector<uint8_t>();
    m_primary_special_ability->reserve(l_primary_special_ability);
    for (int i = 0; i < l_primary_special_ability; i++) {
        m_primary_special_ability->push_back(m__io->read_u1());
    }
    int l_secondary_special_ability = 228;
    m_secondary_special_ability = new std::vector<uint8_t>();
    m_secondary_special_ability->reserve(l_secondary_special_ability);
    for (int i = 0; i < l_secondary_special_ability; i++) {
        m_secondary_special_ability->push_back(m__io->read_u1());
    }
    int l_type = 228;
    m_type = new std::vector<uint8_t>();
    m_type->reserve(l_type);
    for (int i = 0; i < l_type; i++) {
        m_type->push_back(m__io->read_u1());
    }
    int l_unknown5 = 228;
    m_unknown5 = new std::vector<uint8_t>();
    m_unknown5->reserve(l_unknown5);
    for (int i = 0; i < l_unknown5; i++) {
        m_unknown5->push_back(m__io->read_u1());
    }
    int l_unknown6 = 228;
    m_unknown6 = new std::vector<uint8_t>();
    m_unknown6->reserve(l_unknown6);
    for (int i = 0; i < l_unknown6; i++) {
        m_unknown6->push_back(m__io->read_u1());
    }
    int l_groundweapon = 228;
    m_groundweapon = new std::vector<uint8_t>();
    m_groundweapon->reserve(l_groundweapon);
    for (int i = 0; i < l_groundweapon; i++) {
        m_groundweapon->push_back(m__io->read_u1());
    }
    int l_airweapon = 228;
    m_airweapon = new std::vector<uint8_t>();
    m_airweapon->reserve(l_airweapon);
    for (int i = 0; i < l_airweapon; i++) {
        m_airweapon->push_back(m__io->read_u1());
    }
    int l_unknown7 = 228;
    m_unknown7 = new std::vector<uint8_t>();
    m_unknown7->reserve(l_unknown7);
    for (int i = 0; i < l_unknown7; i++) {
        m_unknown7->push_back(m__io->read_u1());
    }
    int l_special_ability_flags = 228;
    m_special_ability_flags = new std::vector<uint32_t>();
    m_special_ability_flags->reserve(l_special_ability_flags);
    for (int i = 0; i < l_special_ability_flags; i++) {
        m_special_ability_flags->push_back(m__io->read_u4le());
    }
    int l_unknown8 = 228;
    m_unknown8 = new std::vector<uint8_t>();
    m_unknown8->reserve(l_unknown8);
    for (int i = 0; i < l_unknown8; i++) {
        m_unknown8->push_back(m__io->read_u1());
    }
    int l_sightrange = 228;
    m_sightrange = new std::vector<uint8_t>();
    m_sightrange->reserve(l_sightrange);
    for (int i = 0; i < l_sightrange; i++) {
        m_sightrange->push_back(m__io->read_u1());
    }
    int l_armor_upgrade_group = 228;
    m_armor_upgrade_group = new std::vector<uint8_t>();
    m_armor_upgrade_group->reserve(l_armor_upgrade_group);
    for (int i = 0; i < l_armor_upgrade_group; i++) {
        m_armor_upgrade_group->push_back(m__io->read_u1());
    }
    int l_size = 228;
    m_size = new std::vector<uint8_t>();
    m_size->reserve(l_size);
    for (int i = 0; i < l_size; i++) {
        m_size->push_back(m__io->read_u1());
    }
    int l_armor = 228;
    m_armor = new std::vector<uint8_t>();
    m_armor->reserve(l_armor);
    for (int i = 0; i < l_armor; i++) {
        m_armor->push_back(m__io->read_u1());
    }
    int l_mineral_right_click = 228;
    m_mineral_right_click = new std::vector<uint8_t>();
    m_mineral_right_click->reserve(l_mineral_right_click);
    for (int i = 0; i < l_mineral_right_click; i++) {
        m_mineral_right_click->push_back(m__io->read_u1());
    }
    int l_sounds = 228;
    m_sounds = new std::vector<uint16_t>();
    m_sounds->reserve(l_sounds);
    for (int i = 0; i < l_sounds; i++) {
        m_sounds->push_back(m__io->read_u2le());
    }
    int l_width = 228;
    m_width = new std::vector<uint16_t>();
    m_width->reserve(l_width);
    for (int i = 0; i < l_width; i++) {
        m_width->push_back(m__io->read_u2le());
    }
    int l_height = 228;
    m_height = new std::vector<uint16_t>();
    m_height->reserve(l_height);
    for (int i = 0; i < l_height; i++) {
        m_height->push_back(m__io->read_u2le());
    }
    int l_circle_width = 228;
    m_circle_width = new std::vector<uint16_t>();
    m_circle_width->reserve(l_circle_width);
    for (int i = 0; i < l_circle_width; i++) {
        m_circle_width->push_back(m__io->read_u2le());
    }
    int l_circle_height = 228;
    m_circle_height = new std::vector<uint16_t>();
    m_circle_height->reserve(l_circle_height);
    for (int i = 0; i < l_circle_height; i++) {
        m_circle_height->push_back(m__io->read_u2le());
    }
    int l_portrait = 228;
    m_portrait = new std::vector<uint16_t>();
    m_portrait->reserve(l_portrait);
    for (int i = 0; i < l_portrait; i++) {
        m_portrait->push_back(m__io->read_u2le());
    }
    int l_mineral_cost = 228;
    m_mineral_cost = new std::vector<uint16_t>();
    m_mineral_cost->reserve(l_mineral_cost);
    for (int i = 0; i < l_mineral_cost; i++) {
        m_mineral_cost->push_back(m__io->read_u2le());
    }
    int l_gas_cost = 228;
    m_gas_cost = new std::vector<uint16_t>();
    m_gas_cost->reserve(l_gas_cost);
    for (int i = 0; i < l_gas_cost; i++) {
        m_gas_cost->push_back(m__io->read_u2le());
    }
    int l_build_time = 228;
    m_build_time = new std::vector<uint16_t>();
    m_build_time->reserve(l_build_time);
    for (int i = 0; i < l_build_time; i++) {
        m_build_time->push_back(m__io->read_u2le());
    }
    int l_restrictions = 228;
    m_restrictions = new std::vector<uint16_t>();
    m_restrictions->reserve(l_restrictions);
    for (int i = 0; i < l_restrictions; i++) {
        m_restrictions->push_back(m__io->read_u2le());
    }
    int l_unit_group = 228;
    m_unit_group = new std::vector<uint8_t>();
    m_unit_group->reserve(l_unit_group);
    for (int i = 0; i < l_unit_group; i++) {
        m_unit_group->push_back(m__io->read_u1());
    }
    int l_food_produced = 228;
    m_food_produced = new std::vector<uint8_t>();
    m_food_produced->reserve(l_food_produced);
    for (int i = 0; i < l_food_produced; i++) {
        m_food_produced->push_back(m__io->read_u1());
    }
    int l_food_costs = 228;
    m_food_costs = new std::vector<uint8_t>();
    m_food_costs->reserve(l_food_costs);
    for (int i = 0; i < l_food_costs; i++) {
        m_food_costs->push_back(m__io->read_u1());
    }
    int l_transport_space = 228;
    m_transport_space = new std::vector<uint8_t>();
    m_transport_space->reserve(l_transport_space);
    for (int i = 0; i < l_transport_space; i++) {
        m_transport_space->push_back(m__io->read_u1());
    }
    int l_building_score = 228;
    m_building_score = new std::vector<uint16_t>();
    m_building_score->reserve(l_building_score);
    for (int i = 0; i < l_building_score; i++) {
        m_building_score->push_back(m__io->read_u2le());
    }
    int l_destroying_score = 228;
    m_destroying_score = new std::vector<uint16_t>();
    m_destroying_score->reserve(l_destroying_score);
    for (int i = 0; i < l_destroying_score; i++) {
        m_destroying_score->push_back(m__io->read_u2le());
    }
    int l_unknown14 = 228;
    m_unknown14 = new std::vector<uint8_t>();
    m_unknown14->reserve(l_unknown14);
    for (int i = 0; i < l_unknown14; i++) {
        m_unknown14->push_back(m__io->read_u1());
    }
    int l_unknown15 = 228;
    m_unknown15 = new std::vector<uint16_t>();
    m_unknown15->reserve(l_unknown15);
    for (int i = 0; i < l_unknown15; i++) {
        m_unknown15->push_back(m__io->read_u2le());
    }
}

units_dat_t::~units_dat_t() {
    _clean_up();
}

void units_dat_t::_clean_up() {
    if (m_graphic_id) {
        delete m_graphic_id; m_graphic_id = 0;
    }
    if (m_subunit1) {
        delete m_subunit1; m_subunit1 = 0;
    }
    if (m_subunit2) {
        delete m_subunit2; m_subunit2 = 0;
    }
    if (m_subunit3) {
        delete m_subunit3; m_subunit3 = 0;
    }
    if (m_contruction_animation) {
        delete m_contruction_animation; m_contruction_animation = 0;
    }
    if (m_unknown1) {
        delete m_unknown1; m_unknown1 = 0;
    }
    if (m_shield_enable) {
        delete m_shield_enable; m_shield_enable = 0;
    }
    if (m_shields) {
        delete m_shields; m_shields = 0;
    }
    if (m_hitpoints) {
        delete m_hitpoints; m_hitpoints = 0;
    }
    if (m_animation_level) {
        delete m_animation_level; m_animation_level = 0;
    }
    if (m_movement_type) {
        delete m_movement_type; m_movement_type = 0;
    }
    if (m_rank) {
        delete m_rank; m_rank = 0;
    }
    if (m_primary_special_ability) {
        delete m_primary_special_ability; m_primary_special_ability = 0;
    }
    if (m_secondary_special_ability) {
        delete m_secondary_special_ability; m_secondary_special_ability = 0;
    }
    if (m_type) {
        delete m_type; m_type = 0;
    }
    if (m_unknown5) {
        delete m_unknown5; m_unknown5 = 0;
    }
    if (m_unknown6) {
        delete m_unknown6; m_unknown6 = 0;
    }
    if (m_groundweapon) {
        delete m_groundweapon; m_groundweapon = 0;
    }
    if (m_airweapon) {
        delete m_airweapon; m_airweapon = 0;
    }
    if (m_unknown7) {
        delete m_unknown7; m_unknown7 = 0;
    }
    if (m_special_ability_flags) {
        delete m_special_ability_flags; m_special_ability_flags = 0;
    }
    if (m_unknown8) {
        delete m_unknown8; m_unknown8 = 0;
    }
    if (m_sightrange) {
        delete m_sightrange; m_sightrange = 0;
    }
    if (m_armor_upgrade_group) {
        delete m_armor_upgrade_group; m_armor_upgrade_group = 0;
    }
    if (m_size) {
        delete m_size; m_size = 0;
    }
    if (m_armor) {
        delete m_armor; m_armor = 0;
    }
    if (m_mineral_right_click) {
        delete m_mineral_right_click; m_mineral_right_click = 0;
    }
    if (m_sounds) {
        delete m_sounds; m_sounds = 0;
    }
    if (m_width) {
        delete m_width; m_width = 0;
    }
    if (m_height) {
        delete m_height; m_height = 0;
    }
    if (m_circle_width) {
        delete m_circle_width; m_circle_width = 0;
    }
    if (m_circle_height) {
        delete m_circle_height; m_circle_height = 0;
    }
    if (m_portrait) {
        delete m_portrait; m_portrait = 0;
    }
    if (m_mineral_cost) {
        delete m_mineral_cost; m_mineral_cost = 0;
    }
    if (m_gas_cost) {
        delete m_gas_cost; m_gas_cost = 0;
    }
    if (m_build_time) {
        delete m_build_time; m_build_time = 0;
    }
    if (m_restrictions) {
        delete m_restrictions; m_restrictions = 0;
    }
    if (m_unit_group) {
        delete m_unit_group; m_unit_group = 0;
    }
    if (m_food_produced) {
        delete m_food_produced; m_food_produced = 0;
    }
    if (m_food_costs) {
        delete m_food_costs; m_food_costs = 0;
    }
    if (m_transport_space) {
        delete m_transport_space; m_transport_space = 0;
    }
    if (m_building_score) {
        delete m_building_score; m_building_score = 0;
    }
    if (m_destroying_score) {
        delete m_destroying_score; m_destroying_score = 0;
    }
    if (m_unknown14) {
        delete m_unknown14; m_unknown14 = 0;
    }
    if (m_unknown15) {
        delete m_unknown15; m_unknown15 = 0;
    }
}
