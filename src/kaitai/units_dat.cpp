// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "units_dat.h"

units_dat_t::units_dat_t(bool p_has_broodwar_flag, bool p_has_max_air_hits, bool p_has_max_ground_hits, kaitai::kstream* p__io, kaitai::kstruct* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_has_broodwar_flag = p_has_broodwar_flag;
    m_has_max_air_hits = p_has_max_air_hits;
    m_has_max_ground_hits = p_has_max_ground_hits;
    m_graphics = 0;
    m_subunit1 = 0;
    m_subunit2 = 0;
    m_infestation = 0;
    m_construction_animation = 0;
    m_unit_direction = 0;
    m_shield_enable = 0;
    m_shield_amount = 0;
    m_hit_points = 0;
    m_elevation_level = 0;
    m_unknown = 0;
    m_rank = 0;
    m_ai_computer_idle = 0;
    m_ai_human_idle = 0;
    m_ai_return_to_idle = 0;
    m_ai_attack_unit = 0;
    m_ai_attack_move = 0;
    m_ground_weapon = 0;
    m_max_ground_hits = 0;
    m_air_weapon = 0;
    m_max_air_hits = 0;
    m_ai_internal = 0;
    m_special_ability_flags = 0;
    m__raw_special_ability_flags = 0;
    m__io__raw_special_ability_flags = 0;
    m_target_acquisition_range = 0;
    m_sight_range = 0;
    m_armor_upgrade = 0;
    m_unit_size = 0;
    m_armor = 0;
    m_right_click_action = 0;
    m_ready_sound = 0;
    m_what_sound_start = 0;
    m_what_sound_end = 0;
    m_piss_sound_start = 0;
    m_piss_sound_end = 0;
    m_yes_sound_start = 0;
    m_yes_sound_end = 0;
    m_staredit_placement_box = 0;
    m_addon_position = 0;
    m_unit_dimension = 0;
    m_portrait = 0;
    m_mineral_cost = 0;
    m_vespene_cost = 0;
    m_build_time = 0;
    m_requirements = 0;
    m_staredit_group_flags = 0;
    m__raw_staredit_group_flags = 0;
    m__io__raw_staredit_group_flags = 0;
    m_supply_provided = 0;
    m_supply_required = 0;
    m_space_required = 0;
    m_space_provided = 0;
    m_build_score = 0;
    m_destroy_score = 0;
    m_unit_map_string = 0;
    m_broodwar_flag = 0;
    m_staredit_availability_flags = 0;
    m__raw_staredit_availability_flags = 0;
    m__io__raw_staredit_availability_flags = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::_read() {
    int l_graphics = 228;
    m_graphics = new std::vector<uint8_t>();
    m_graphics->reserve(l_graphics);
    for (int i = 0; i < l_graphics; i++) {
        m_graphics->push_back(m__io->read_u1());
    }
    int l_subunit1 = 228;
    m_subunit1 = new std::vector<uint16_t>();
    m_subunit1->reserve(l_subunit1);
    for (int i = 0; i < l_subunit1; i++) {
        m_subunit1->push_back(m__io->read_u2le());
    }
    int l_subunit2 = 228;
    m_subunit2 = new std::vector<uint16_t>();
    m_subunit2->reserve(l_subunit2);
    for (int i = 0; i < l_subunit2; i++) {
        m_subunit2->push_back(m__io->read_u2le());
    }
    int l_infestation = 96;
    m_infestation = new std::vector<uint16_t>();
    m_infestation->reserve(l_infestation);
    for (int i = 0; i < l_infestation; i++) {
        m_infestation->push_back(m__io->read_u2le());
    }
    int l_construction_animation = 228;
    m_construction_animation = new std::vector<uint32_t>();
    m_construction_animation->reserve(l_construction_animation);
    for (int i = 0; i < l_construction_animation; i++) {
        m_construction_animation->push_back(m__io->read_u4le());
    }
    int l_unit_direction = 228;
    m_unit_direction = new std::vector<uint8_t>();
    m_unit_direction->reserve(l_unit_direction);
    for (int i = 0; i < l_unit_direction; i++) {
        m_unit_direction->push_back(m__io->read_u1());
    }
    int l_shield_enable = 228;
    m_shield_enable = new std::vector<uint8_t>();
    m_shield_enable->reserve(l_shield_enable);
    for (int i = 0; i < l_shield_enable; i++) {
        m_shield_enable->push_back(m__io->read_u1());
    }
    int l_shield_amount = 228;
    m_shield_amount = new std::vector<uint16_t>();
    m_shield_amount->reserve(l_shield_amount);
    for (int i = 0; i < l_shield_amount; i++) {
        m_shield_amount->push_back(m__io->read_u2le());
    }
    int l_hit_points = 228;
    m_hit_points = new std::vector<hit_points_type_t*>();
    m_hit_points->reserve(l_hit_points);
    for (int i = 0; i < l_hit_points; i++) {
        m_hit_points->push_back(new hit_points_type_t(m__io, this, m__root));
    }
    int l_elevation_level = 228;
    m_elevation_level = new std::vector<uint8_t>();
    m_elevation_level->reserve(l_elevation_level);
    for (int i = 0; i < l_elevation_level; i++) {
        m_elevation_level->push_back(m__io->read_u1());
    }
    int l_unknown = 228;
    m_unknown = new std::vector<uint8_t>();
    m_unknown->reserve(l_unknown);
    for (int i = 0; i < l_unknown; i++) {
        m_unknown->push_back(m__io->read_u1());
    }
    int l_rank = 228;
    m_rank = new std::vector<uint8_t>();
    m_rank->reserve(l_rank);
    for (int i = 0; i < l_rank; i++) {
        m_rank->push_back(m__io->read_u1());
    }
    int l_ai_computer_idle = 228;
    m_ai_computer_idle = new std::vector<uint8_t>();
    m_ai_computer_idle->reserve(l_ai_computer_idle);
    for (int i = 0; i < l_ai_computer_idle; i++) {
        m_ai_computer_idle->push_back(m__io->read_u1());
    }
    int l_ai_human_idle = 228;
    m_ai_human_idle = new std::vector<uint8_t>();
    m_ai_human_idle->reserve(l_ai_human_idle);
    for (int i = 0; i < l_ai_human_idle; i++) {
        m_ai_human_idle->push_back(m__io->read_u1());
    }
    int l_ai_return_to_idle = 228;
    m_ai_return_to_idle = new std::vector<uint8_t>();
    m_ai_return_to_idle->reserve(l_ai_return_to_idle);
    for (int i = 0; i < l_ai_return_to_idle; i++) {
        m_ai_return_to_idle->push_back(m__io->read_u1());
    }
    int l_ai_attack_unit = 228;
    m_ai_attack_unit = new std::vector<uint8_t>();
    m_ai_attack_unit->reserve(l_ai_attack_unit);
    for (int i = 0; i < l_ai_attack_unit; i++) {
        m_ai_attack_unit->push_back(m__io->read_u1());
    }
    int l_ai_attack_move = 228;
    m_ai_attack_move = new std::vector<uint8_t>();
    m_ai_attack_move->reserve(l_ai_attack_move);
    for (int i = 0; i < l_ai_attack_move; i++) {
        m_ai_attack_move->push_back(m__io->read_u1());
    }
    int l_ground_weapon = 228;
    m_ground_weapon = new std::vector<uint8_t>();
    m_ground_weapon->reserve(l_ground_weapon);
    for (int i = 0; i < l_ground_weapon; i++) {
        m_ground_weapon->push_back(m__io->read_u1());
    }
    n_max_ground_hits = true;
    if (has_max_ground_hits() == true) {
        n_max_ground_hits = false;
        int l_max_ground_hits = 228;
        m_max_ground_hits = new std::vector<uint8_t>();
        m_max_ground_hits->reserve(l_max_ground_hits);
        for (int i = 0; i < l_max_ground_hits; i++) {
            m_max_ground_hits->push_back(m__io->read_u1());
        }
    }
    int l_air_weapon = 228;
    m_air_weapon = new std::vector<uint8_t>();
    m_air_weapon->reserve(l_air_weapon);
    for (int i = 0; i < l_air_weapon; i++) {
        m_air_weapon->push_back(m__io->read_u1());
    }
    n_max_air_hits = true;
    if (has_max_air_hits() == true) {
        n_max_air_hits = false;
        int l_max_air_hits = 228;
        m_max_air_hits = new std::vector<uint8_t>();
        m_max_air_hits->reserve(l_max_air_hits);
        for (int i = 0; i < l_max_air_hits; i++) {
            m_max_air_hits->push_back(m__io->read_u1());
        }
    }
    int l_ai_internal = 228;
    m_ai_internal = new std::vector<uint8_t>();
    m_ai_internal->reserve(l_ai_internal);
    for (int i = 0; i < l_ai_internal; i++) {
        m_ai_internal->push_back(m__io->read_u1());
    }
    int l_special_ability_flags = 228;
    m__raw_special_ability_flags = new std::vector<std::string>();
    m__raw_special_ability_flags->reserve(l_special_ability_flags);
    m__io__raw_special_ability_flags = new std::vector<kaitai::kstream*>();
    m__io__raw_special_ability_flags->reserve(l_special_ability_flags);
    m_special_ability_flags = new std::vector<special_ability_flags_type_t*>();
    m_special_ability_flags->reserve(l_special_ability_flags);
    for (int i = 0; i < l_special_ability_flags; i++) {
        m__raw_special_ability_flags->push_back(m__io->read_bytes(4));
        kaitai::kstream* io__raw_special_ability_flags = new kaitai::kstream(m__raw_special_ability_flags->at(m__raw_special_ability_flags->size() - 1));
        m__io__raw_special_ability_flags->push_back(io__raw_special_ability_flags);
        m_special_ability_flags->push_back(new special_ability_flags_type_t(io__raw_special_ability_flags, this, m__root));
    }
    int l_target_acquisition_range = 228;
    m_target_acquisition_range = new std::vector<uint8_t>();
    m_target_acquisition_range->reserve(l_target_acquisition_range);
    for (int i = 0; i < l_target_acquisition_range; i++) {
        m_target_acquisition_range->push_back(m__io->read_u1());
    }
    int l_sight_range = 228;
    m_sight_range = new std::vector<uint8_t>();
    m_sight_range->reserve(l_sight_range);
    for (int i = 0; i < l_sight_range; i++) {
        m_sight_range->push_back(m__io->read_u1());
    }
    int l_armor_upgrade = 228;
    m_armor_upgrade = new std::vector<uint8_t>();
    m_armor_upgrade->reserve(l_armor_upgrade);
    for (int i = 0; i < l_armor_upgrade; i++) {
        m_armor_upgrade->push_back(m__io->read_u1());
    }
    int l_unit_size = 228;
    m_unit_size = new std::vector<unit_size_enum_t>();
    m_unit_size->reserve(l_unit_size);
    for (int i = 0; i < l_unit_size; i++) {
        m_unit_size->push_back(static_cast<units_dat_t::unit_size_enum_t>(m__io->read_u1()));
    }
    int l_armor = 228;
    m_armor = new std::vector<uint8_t>();
    m_armor->reserve(l_armor);
    for (int i = 0; i < l_armor; i++) {
        m_armor->push_back(m__io->read_u1());
    }
    int l_right_click_action = 228;
    m_right_click_action = new std::vector<right_click_action_enum_t>();
    m_right_click_action->reserve(l_right_click_action);
    for (int i = 0; i < l_right_click_action; i++) {
        m_right_click_action->push_back(static_cast<units_dat_t::right_click_action_enum_t>(m__io->read_u1()));
    }
    int l_ready_sound = 106;
    m_ready_sound = new std::vector<uint16_t>();
    m_ready_sound->reserve(l_ready_sound);
    for (int i = 0; i < l_ready_sound; i++) {
        m_ready_sound->push_back(m__io->read_u2le());
    }
    int l_what_sound_start = 228;
    m_what_sound_start = new std::vector<uint16_t>();
    m_what_sound_start->reserve(l_what_sound_start);
    for (int i = 0; i < l_what_sound_start; i++) {
        m_what_sound_start->push_back(m__io->read_u2le());
    }
    int l_what_sound_end = 228;
    m_what_sound_end = new std::vector<uint16_t>();
    m_what_sound_end->reserve(l_what_sound_end);
    for (int i = 0; i < l_what_sound_end; i++) {
        m_what_sound_end->push_back(m__io->read_u2le());
    }
    int l_piss_sound_start = 106;
    m_piss_sound_start = new std::vector<uint16_t>();
    m_piss_sound_start->reserve(l_piss_sound_start);
    for (int i = 0; i < l_piss_sound_start; i++) {
        m_piss_sound_start->push_back(m__io->read_u2le());
    }
    int l_piss_sound_end = 106;
    m_piss_sound_end = new std::vector<uint16_t>();
    m_piss_sound_end->reserve(l_piss_sound_end);
    for (int i = 0; i < l_piss_sound_end; i++) {
        m_piss_sound_end->push_back(m__io->read_u2le());
    }
    int l_yes_sound_start = 106;
    m_yes_sound_start = new std::vector<uint16_t>();
    m_yes_sound_start->reserve(l_yes_sound_start);
    for (int i = 0; i < l_yes_sound_start; i++) {
        m_yes_sound_start->push_back(m__io->read_u2le());
    }
    int l_yes_sound_end = 106;
    m_yes_sound_end = new std::vector<uint16_t>();
    m_yes_sound_end->reserve(l_yes_sound_end);
    for (int i = 0; i < l_yes_sound_end; i++) {
        m_yes_sound_end->push_back(m__io->read_u2le());
    }
    int l_staredit_placement_box = 228;
    m_staredit_placement_box = new std::vector<staredit_placement_box_type_t*>();
    m_staredit_placement_box->reserve(l_staredit_placement_box);
    for (int i = 0; i < l_staredit_placement_box; i++) {
        m_staredit_placement_box->push_back(new staredit_placement_box_type_t(m__io, this, m__root));
    }
    int l_addon_position = 96;
    m_addon_position = new std::vector<addon_position_type_t*>();
    m_addon_position->reserve(l_addon_position);
    for (int i = 0; i < l_addon_position; i++) {
        m_addon_position->push_back(new addon_position_type_t(m__io, this, m__root));
    }
    int l_unit_dimension = 228;
    m_unit_dimension = new std::vector<unit_dimension_type_t*>();
    m_unit_dimension->reserve(l_unit_dimension);
    for (int i = 0; i < l_unit_dimension; i++) {
        m_unit_dimension->push_back(new unit_dimension_type_t(m__io, this, m__root));
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
    int l_vespene_cost = 228;
    m_vespene_cost = new std::vector<uint16_t>();
    m_vespene_cost->reserve(l_vespene_cost);
    for (int i = 0; i < l_vespene_cost; i++) {
        m_vespene_cost->push_back(m__io->read_u2le());
    }
    int l_build_time = 228;
    m_build_time = new std::vector<uint16_t>();
    m_build_time->reserve(l_build_time);
    for (int i = 0; i < l_build_time; i++) {
        m_build_time->push_back(m__io->read_u2le());
    }
    int l_requirements = 228;
    m_requirements = new std::vector<uint16_t>();
    m_requirements->reserve(l_requirements);
    for (int i = 0; i < l_requirements; i++) {
        m_requirements->push_back(m__io->read_u2le());
    }
    int l_staredit_group_flags = 228;
    m__raw_staredit_group_flags = new std::vector<std::string>();
    m__raw_staredit_group_flags->reserve(l_staredit_group_flags);
    m__io__raw_staredit_group_flags = new std::vector<kaitai::kstream*>();
    m__io__raw_staredit_group_flags->reserve(l_staredit_group_flags);
    m_staredit_group_flags = new std::vector<staredit_group_flags_type_t*>();
    m_staredit_group_flags->reserve(l_staredit_group_flags);
    for (int i = 0; i < l_staredit_group_flags; i++) {
        m__raw_staredit_group_flags->push_back(m__io->read_bytes(1));
        kaitai::kstream* io__raw_staredit_group_flags = new kaitai::kstream(m__raw_staredit_group_flags->at(m__raw_staredit_group_flags->size() - 1));
        m__io__raw_staredit_group_flags->push_back(io__raw_staredit_group_flags);
        m_staredit_group_flags->push_back(new staredit_group_flags_type_t(io__raw_staredit_group_flags, this, m__root));
    }
    int l_supply_provided = 228;
    m_supply_provided = new std::vector<uint8_t>();
    m_supply_provided->reserve(l_supply_provided);
    for (int i = 0; i < l_supply_provided; i++) {
        m_supply_provided->push_back(m__io->read_u1());
    }
    int l_supply_required = 228;
    m_supply_required = new std::vector<uint8_t>();
    m_supply_required->reserve(l_supply_required);
    for (int i = 0; i < l_supply_required; i++) {
        m_supply_required->push_back(m__io->read_u1());
    }
    int l_space_required = 228;
    m_space_required = new std::vector<uint8_t>();
    m_space_required->reserve(l_space_required);
    for (int i = 0; i < l_space_required; i++) {
        m_space_required->push_back(m__io->read_u1());
    }
    int l_space_provided = 228;
    m_space_provided = new std::vector<uint8_t>();
    m_space_provided->reserve(l_space_provided);
    for (int i = 0; i < l_space_provided; i++) {
        m_space_provided->push_back(m__io->read_u1());
    }
    int l_build_score = 228;
    m_build_score = new std::vector<uint16_t>();
    m_build_score->reserve(l_build_score);
    for (int i = 0; i < l_build_score; i++) {
        m_build_score->push_back(m__io->read_u2le());
    }
    int l_destroy_score = 228;
    m_destroy_score = new std::vector<uint16_t>();
    m_destroy_score->reserve(l_destroy_score);
    for (int i = 0; i < l_destroy_score; i++) {
        m_destroy_score->push_back(m__io->read_u2le());
    }
    int l_unit_map_string = 228;
    m_unit_map_string = new std::vector<uint16_t>();
    m_unit_map_string->reserve(l_unit_map_string);
    for (int i = 0; i < l_unit_map_string; i++) {
        m_unit_map_string->push_back(m__io->read_u2le());
    }
    n_broodwar_flag = true;
    if (has_broodwar_flag() == true) {
        n_broodwar_flag = false;
        int l_broodwar_flag = 228;
        m_broodwar_flag = new std::vector<uint8_t>();
        m_broodwar_flag->reserve(l_broodwar_flag);
        for (int i = 0; i < l_broodwar_flag; i++) {
            m_broodwar_flag->push_back(m__io->read_u1());
        }
    }
    int l_staredit_availability_flags = 228;
    m__raw_staredit_availability_flags = new std::vector<std::string>();
    m__raw_staredit_availability_flags->reserve(l_staredit_availability_flags);
    m__io__raw_staredit_availability_flags = new std::vector<kaitai::kstream*>();
    m__io__raw_staredit_availability_flags->reserve(l_staredit_availability_flags);
    m_staredit_availability_flags = new std::vector<staredit_availability_flags_type_t*>();
    m_staredit_availability_flags->reserve(l_staredit_availability_flags);
    for (int i = 0; i < l_staredit_availability_flags; i++) {
        m__raw_staredit_availability_flags->push_back(m__io->read_bytes(2));
        kaitai::kstream* io__raw_staredit_availability_flags = new kaitai::kstream(m__raw_staredit_availability_flags->at(m__raw_staredit_availability_flags->size() - 1));
        m__io__raw_staredit_availability_flags->push_back(io__raw_staredit_availability_flags);
        m_staredit_availability_flags->push_back(new staredit_availability_flags_type_t(io__raw_staredit_availability_flags, this, m__root));
    }
}

units_dat_t::~units_dat_t() {
    _clean_up();
}

void units_dat_t::_clean_up() {
    if (m_graphics) {
        delete m_graphics; m_graphics = 0;
    }
    if (m_subunit1) {
        delete m_subunit1; m_subunit1 = 0;
    }
    if (m_subunit2) {
        delete m_subunit2; m_subunit2 = 0;
    }
    if (m_infestation) {
        delete m_infestation; m_infestation = 0;
    }
    if (m_construction_animation) {
        delete m_construction_animation; m_construction_animation = 0;
    }
    if (m_unit_direction) {
        delete m_unit_direction; m_unit_direction = 0;
    }
    if (m_shield_enable) {
        delete m_shield_enable; m_shield_enable = 0;
    }
    if (m_shield_amount) {
        delete m_shield_amount; m_shield_amount = 0;
    }
    if (m_hit_points) {
        for (std::vector<hit_points_type_t*>::iterator it = m_hit_points->begin(); it != m_hit_points->end(); ++it) {
            delete *it;
        }
        delete m_hit_points; m_hit_points = 0;
    }
    if (m_elevation_level) {
        delete m_elevation_level; m_elevation_level = 0;
    }
    if (m_unknown) {
        delete m_unknown; m_unknown = 0;
    }
    if (m_rank) {
        delete m_rank; m_rank = 0;
    }
    if (m_ai_computer_idle) {
        delete m_ai_computer_idle; m_ai_computer_idle = 0;
    }
    if (m_ai_human_idle) {
        delete m_ai_human_idle; m_ai_human_idle = 0;
    }
    if (m_ai_return_to_idle) {
        delete m_ai_return_to_idle; m_ai_return_to_idle = 0;
    }
    if (m_ai_attack_unit) {
        delete m_ai_attack_unit; m_ai_attack_unit = 0;
    }
    if (m_ai_attack_move) {
        delete m_ai_attack_move; m_ai_attack_move = 0;
    }
    if (m_ground_weapon) {
        delete m_ground_weapon; m_ground_weapon = 0;
    }
    if (!n_max_ground_hits) {
        if (m_max_ground_hits) {
            delete m_max_ground_hits; m_max_ground_hits = 0;
        }
    }
    if (m_air_weapon) {
        delete m_air_weapon; m_air_weapon = 0;
    }
    if (!n_max_air_hits) {
        if (m_max_air_hits) {
            delete m_max_air_hits; m_max_air_hits = 0;
        }
    }
    if (m_ai_internal) {
        delete m_ai_internal; m_ai_internal = 0;
    }
    if (m__raw_special_ability_flags) {
        delete m__raw_special_ability_flags; m__raw_special_ability_flags = 0;
    }
    if (m__io__raw_special_ability_flags) {
        for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_special_ability_flags->begin(); it != m__io__raw_special_ability_flags->end(); ++it) {
            delete *it;
        }
        delete m__io__raw_special_ability_flags; m__io__raw_special_ability_flags = 0;
    }
    if (m_special_ability_flags) {
        for (std::vector<special_ability_flags_type_t*>::iterator it = m_special_ability_flags->begin(); it != m_special_ability_flags->end(); ++it) {
            delete *it;
        }
        delete m_special_ability_flags; m_special_ability_flags = 0;
    }
    if (m_target_acquisition_range) {
        delete m_target_acquisition_range; m_target_acquisition_range = 0;
    }
    if (m_sight_range) {
        delete m_sight_range; m_sight_range = 0;
    }
    if (m_armor_upgrade) {
        delete m_armor_upgrade; m_armor_upgrade = 0;
    }
    if (m_unit_size) {
        delete m_unit_size; m_unit_size = 0;
    }
    if (m_armor) {
        delete m_armor; m_armor = 0;
    }
    if (m_right_click_action) {
        delete m_right_click_action; m_right_click_action = 0;
    }
    if (m_ready_sound) {
        delete m_ready_sound; m_ready_sound = 0;
    }
    if (m_what_sound_start) {
        delete m_what_sound_start; m_what_sound_start = 0;
    }
    if (m_what_sound_end) {
        delete m_what_sound_end; m_what_sound_end = 0;
    }
    if (m_piss_sound_start) {
        delete m_piss_sound_start; m_piss_sound_start = 0;
    }
    if (m_piss_sound_end) {
        delete m_piss_sound_end; m_piss_sound_end = 0;
    }
    if (m_yes_sound_start) {
        delete m_yes_sound_start; m_yes_sound_start = 0;
    }
    if (m_yes_sound_end) {
        delete m_yes_sound_end; m_yes_sound_end = 0;
    }
    if (m_staredit_placement_box) {
        for (std::vector<staredit_placement_box_type_t*>::iterator it = m_staredit_placement_box->begin(); it != m_staredit_placement_box->end(); ++it) {
            delete *it;
        }
        delete m_staredit_placement_box; m_staredit_placement_box = 0;
    }
    if (m_addon_position) {
        for (std::vector<addon_position_type_t*>::iterator it = m_addon_position->begin(); it != m_addon_position->end(); ++it) {
            delete *it;
        }
        delete m_addon_position; m_addon_position = 0;
    }
    if (m_unit_dimension) {
        for (std::vector<unit_dimension_type_t*>::iterator it = m_unit_dimension->begin(); it != m_unit_dimension->end(); ++it) {
            delete *it;
        }
        delete m_unit_dimension; m_unit_dimension = 0;
    }
    if (m_portrait) {
        delete m_portrait; m_portrait = 0;
    }
    if (m_mineral_cost) {
        delete m_mineral_cost; m_mineral_cost = 0;
    }
    if (m_vespene_cost) {
        delete m_vespene_cost; m_vespene_cost = 0;
    }
    if (m_build_time) {
        delete m_build_time; m_build_time = 0;
    }
    if (m_requirements) {
        delete m_requirements; m_requirements = 0;
    }
    if (m__raw_staredit_group_flags) {
        delete m__raw_staredit_group_flags; m__raw_staredit_group_flags = 0;
    }
    if (m__io__raw_staredit_group_flags) {
        for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_staredit_group_flags->begin(); it != m__io__raw_staredit_group_flags->end(); ++it) {
            delete *it;
        }
        delete m__io__raw_staredit_group_flags; m__io__raw_staredit_group_flags = 0;
    }
    if (m_staredit_group_flags) {
        for (std::vector<staredit_group_flags_type_t*>::iterator it = m_staredit_group_flags->begin(); it != m_staredit_group_flags->end(); ++it) {
            delete *it;
        }
        delete m_staredit_group_flags; m_staredit_group_flags = 0;
    }
    if (m_supply_provided) {
        delete m_supply_provided; m_supply_provided = 0;
    }
    if (m_supply_required) {
        delete m_supply_required; m_supply_required = 0;
    }
    if (m_space_required) {
        delete m_space_required; m_space_required = 0;
    }
    if (m_space_provided) {
        delete m_space_provided; m_space_provided = 0;
    }
    if (m_build_score) {
        delete m_build_score; m_build_score = 0;
    }
    if (m_destroy_score) {
        delete m_destroy_score; m_destroy_score = 0;
    }
    if (m_unit_map_string) {
        delete m_unit_map_string; m_unit_map_string = 0;
    }
    if (!n_broodwar_flag) {
        if (m_broodwar_flag) {
            delete m_broodwar_flag; m_broodwar_flag = 0;
        }
    }
    if (m__raw_staredit_availability_flags) {
        delete m__raw_staredit_availability_flags; m__raw_staredit_availability_flags = 0;
    }
    if (m__io__raw_staredit_availability_flags) {
        for (std::vector<kaitai::kstream*>::iterator it = m__io__raw_staredit_availability_flags->begin(); it != m__io__raw_staredit_availability_flags->end(); ++it) {
            delete *it;
        }
        delete m__io__raw_staredit_availability_flags; m__io__raw_staredit_availability_flags = 0;
    }
    if (m_staredit_availability_flags) {
        for (std::vector<staredit_availability_flags_type_t*>::iterator it = m_staredit_availability_flags->begin(); it != m_staredit_availability_flags->end(); ++it) {
            delete *it;
        }
        delete m_staredit_availability_flags; m_staredit_availability_flags = 0;
    }
}

units_dat_t::staredit_group_flags_type_t::staredit_group_flags_type_t(kaitai::kstream* p__io, units_dat_t* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::staredit_group_flags_type_t::_read() {
    m_zerg = m__io->read_bits_int_le(1);
    m_terran = m__io->read_bits_int_le(1);
    m_protoss = m__io->read_bits_int_le(1);
    m_men = m__io->read_bits_int_le(1);
    m_building = m__io->read_bits_int_le(1);
    m_factory = m__io->read_bits_int_le(1);
    m_independent = m__io->read_bits_int_le(1);
    m_neutral = m__io->read_bits_int_le(1);
}

units_dat_t::staredit_group_flags_type_t::~staredit_group_flags_type_t() {
    _clean_up();
}

void units_dat_t::staredit_group_flags_type_t::_clean_up() {
}

units_dat_t::hit_points_type_t::hit_points_type_t(kaitai::kstream* p__io, units_dat_t* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::hit_points_type_t::_read() {
    m_hitpoints = m__io->read_u2be();
    m_unused = m__io->read_u2be();
}

units_dat_t::hit_points_type_t::~hit_points_type_t() {
    _clean_up();
}

void units_dat_t::hit_points_type_t::_clean_up() {
}

units_dat_t::addon_position_type_t::addon_position_type_t(kaitai::kstream* p__io, units_dat_t* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::addon_position_type_t::_read() {
    m_horizontal = m__io->read_u2le();
    m_vertical = m__io->read_u2le();
}

units_dat_t::addon_position_type_t::~addon_position_type_t() {
    _clean_up();
}

void units_dat_t::addon_position_type_t::_clean_up() {
}

units_dat_t::special_ability_flags_type_t::special_ability_flags_type_t(kaitai::kstream* p__io, units_dat_t* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::special_ability_flags_type_t::_read() {
    m_building = m__io->read_bits_int_le(1);
    m_addon = m__io->read_bits_int_le(1);
    m_flyer = m__io->read_bits_int_le(1);
    m_resourceminer = m__io->read_bits_int_le(1);
    m_subunit = m__io->read_bits_int_le(1);
    m_flyingbuilding = m__io->read_bits_int_le(1);
    m_hero = m__io->read_bits_int_le(1);
    m_regenerate = m__io->read_bits_int_le(1);
    m_animatedidle = m__io->read_bits_int_le(1);
    m_cloakable = m__io->read_bits_int_le(1);
    m_twounitsinoneegg = m__io->read_bits_int_le(1);
    m_singleentity = m__io->read_bits_int_le(1);
    m_resourcedepot = m__io->read_bits_int_le(1);
    m_resourcecontainter = m__io->read_bits_int_le(1);
    m_robotic = m__io->read_bits_int_le(1);
    m_detector = m__io->read_bits_int_le(1);
    m_organic = m__io->read_bits_int_le(1);
    m_requirescreep = m__io->read_bits_int_le(1);
    m_unused = m__io->read_bits_int_le(1);
    m_requirespsi = m__io->read_bits_int_le(1);
    m_burrowable = m__io->read_bits_int_le(1);
    m_spellcaster = m__io->read_bits_int_le(1);
    m_permanentcloak = m__io->read_bits_int_le(1);
    m_pickupitem = m__io->read_bits_int_le(1);
    m_ignoresupplycheck = m__io->read_bits_int_le(1);
    m_usemediumoverlays = m__io->read_bits_int_le(1);
    m_uselargeoverlays = m__io->read_bits_int_le(1);
    m_battlereactions = m__io->read_bits_int_le(1);
    m_fullautoattack = m__io->read_bits_int_le(1);
    m_invincible = m__io->read_bits_int_le(1);
    m_mechanical = m__io->read_bits_int_le(1);
    m_producesunits = m__io->read_bits_int_le(1);
}

units_dat_t::special_ability_flags_type_t::~special_ability_flags_type_t() {
    _clean_up();
}

void units_dat_t::special_ability_flags_type_t::_clean_up() {
}

units_dat_t::staredit_placement_box_type_t::staredit_placement_box_type_t(kaitai::kstream* p__io, units_dat_t* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::staredit_placement_box_type_t::_read() {
    m_width = m__io->read_u2le();
    m_height = m__io->read_u2le();
}

units_dat_t::staredit_placement_box_type_t::~staredit_placement_box_type_t() {
    _clean_up();
}

void units_dat_t::staredit_placement_box_type_t::_clean_up() {
}

units_dat_t::unit_dimension_type_t::unit_dimension_type_t(kaitai::kstream* p__io, units_dat_t* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::unit_dimension_type_t::_read() {
    m_left = m__io->read_u2le();
    m_up = m__io->read_u2le();
    m_right = m__io->read_u2le();
    m_down = m__io->read_u2le();
}

units_dat_t::unit_dimension_type_t::~unit_dimension_type_t() {
    _clean_up();
}

void units_dat_t::unit_dimension_type_t::_clean_up() {
}

units_dat_t::staredit_availability_flags_type_t::staredit_availability_flags_type_t(kaitai::kstream* p__io, units_dat_t* p__parent, units_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void units_dat_t::staredit_availability_flags_type_t::_read() {
    m_non_neutral = m__io->read_bits_int_le(1);
    m_unit_listing = m__io->read_bits_int_le(1);
    m_mission_briefing = m__io->read_bits_int_le(1);
    m_player_settings = m__io->read_bits_int_le(1);
    m_all_races = m__io->read_bits_int_le(1);
    m_set_doodad_state = m__io->read_bits_int_le(1);
    m_non_location_triggers = m__io->read_bits_int_le(1);
    m_unit_hero_settings = m__io->read_bits_int_le(1);
    m_location_triggers = m__io->read_bits_int_le(1);
    m_brood_war_only = m__io->read_bits_int_le(1);
    m__unnamed10 = m__io->read_bits_int_le(6);
}

units_dat_t::staredit_availability_flags_type_t::~staredit_availability_flags_type_t() {
    _clean_up();
}

void units_dat_t::staredit_availability_flags_type_t::_clean_up() {
}
