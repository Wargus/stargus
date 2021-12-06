// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "upgrades_dat.h"

upgrades_dat_t::upgrades_dat_t(bool p_has_broodwar_flag, uint8_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent, upgrades_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_has_broodwar_flag = p_has_broodwar_flag;
    m_num_lines = p_num_lines;
    m_mineral_cost_base = 0;
    m_mineral_cost_factor = 0;
    m_vespene_cost_base = 0;
    m_vespene_cost_factor = 0;
    m_research_time_base = 0;
    m_research_time_factor = 0;
    m_unknown6 = 0;
    m_icon = 0;
    m_label = 0;
    m_race = 0;
    m_max_repeats = 0;
    m_broodwar_flags = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void upgrades_dat_t::_read() {
    int l_mineral_cost_base = num_lines();
    m_mineral_cost_base = new std::vector<uint16_t>();
    m_mineral_cost_base->reserve(l_mineral_cost_base);
    for (int i = 0; i < l_mineral_cost_base; i++) {
        m_mineral_cost_base->push_back(m__io->read_u2le());
    }
    int l_mineral_cost_factor = num_lines();
    m_mineral_cost_factor = new std::vector<uint16_t>();
    m_mineral_cost_factor->reserve(l_mineral_cost_factor);
    for (int i = 0; i < l_mineral_cost_factor; i++) {
        m_mineral_cost_factor->push_back(m__io->read_u2le());
    }
    int l_vespene_cost_base = num_lines();
    m_vespene_cost_base = new std::vector<uint16_t>();
    m_vespene_cost_base->reserve(l_vespene_cost_base);
    for (int i = 0; i < l_vespene_cost_base; i++) {
        m_vespene_cost_base->push_back(m__io->read_u2le());
    }
    int l_vespene_cost_factor = num_lines();
    m_vespene_cost_factor = new std::vector<uint16_t>();
    m_vespene_cost_factor->reserve(l_vespene_cost_factor);
    for (int i = 0; i < l_vespene_cost_factor; i++) {
        m_vespene_cost_factor->push_back(m__io->read_u2le());
    }
    int l_research_time_base = num_lines();
    m_research_time_base = new std::vector<uint16_t>();
    m_research_time_base->reserve(l_research_time_base);
    for (int i = 0; i < l_research_time_base; i++) {
        m_research_time_base->push_back(m__io->read_u2le());
    }
    int l_research_time_factor = num_lines();
    m_research_time_factor = new std::vector<uint16_t>();
    m_research_time_factor->reserve(l_research_time_factor);
    for (int i = 0; i < l_research_time_factor; i++) {
        m_research_time_factor->push_back(m__io->read_u2le());
    }
    int l_unknown6 = num_lines();
    m_unknown6 = new std::vector<uint16_t>();
    m_unknown6->reserve(l_unknown6);
    for (int i = 0; i < l_unknown6; i++) {
        m_unknown6->push_back(m__io->read_u2le());
    }
    int l_icon = num_lines();
    m_icon = new std::vector<uint16_t>();
    m_icon->reserve(l_icon);
    for (int i = 0; i < l_icon; i++) {
        m_icon->push_back(m__io->read_u2le());
    }
    int l_label = num_lines();
    m_label = new std::vector<uint16_t>();
    m_label->reserve(l_label);
    for (int i = 0; i < l_label; i++) {
        m_label->push_back(m__io->read_u2le());
    }
    int l_race = num_lines();
    m_race = new std::vector<uint8_t>();
    m_race->reserve(l_race);
    for (int i = 0; i < l_race; i++) {
        m_race->push_back(m__io->read_u1());
    }
    int l_max_repeats = num_lines();
    m_max_repeats = new std::vector<uint8_t>();
    m_max_repeats->reserve(l_max_repeats);
    for (int i = 0; i < l_max_repeats; i++) {
        m_max_repeats->push_back(m__io->read_u1());
    }
    n_broodwar_flags = true;
    if (has_broodwar_flag() == true) {
        n_broodwar_flags = false;
        int l_broodwar_flags = num_lines();
        m_broodwar_flags = new std::vector<uint8_t>();
        m_broodwar_flags->reserve(l_broodwar_flags);
        for (int i = 0; i < l_broodwar_flags; i++) {
            m_broodwar_flags->push_back(m__io->read_u1());
        }
    }
}

upgrades_dat_t::~upgrades_dat_t() {
    _clean_up();
}

void upgrades_dat_t::_clean_up() {
    if (m_mineral_cost_base) {
        delete m_mineral_cost_base; m_mineral_cost_base = 0;
    }
    if (m_mineral_cost_factor) {
        delete m_mineral_cost_factor; m_mineral_cost_factor = 0;
    }
    if (m_vespene_cost_base) {
        delete m_vespene_cost_base; m_vespene_cost_base = 0;
    }
    if (m_vespene_cost_factor) {
        delete m_vespene_cost_factor; m_vespene_cost_factor = 0;
    }
    if (m_research_time_base) {
        delete m_research_time_base; m_research_time_base = 0;
    }
    if (m_research_time_factor) {
        delete m_research_time_factor; m_research_time_factor = 0;
    }
    if (m_unknown6) {
        delete m_unknown6; m_unknown6 = 0;
    }
    if (m_icon) {
        delete m_icon; m_icon = 0;
    }
    if (m_label) {
        delete m_label; m_label = 0;
    }
    if (m_race) {
        delete m_race; m_race = 0;
    }
    if (m_max_repeats) {
        delete m_max_repeats; m_max_repeats = 0;
    }
    if (!n_broodwar_flags) {
        if (m_broodwar_flags) {
            delete m_broodwar_flags; m_broodwar_flags = 0;
        }
    }
}
