// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "techdata_dat.h"

techdata_dat_t::techdata_dat_t(bool p_has_broodwar_flag, uint8_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent, techdata_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_has_broodwar_flag = p_has_broodwar_flag;
    m_num_lines = p_num_lines;
    m_mineral_cost = 0;
    m_vespene_cost = 0;
    m_research_time = 0;
    m_energy_required = 0;
    m_unknown4 = 0;
    m_icon = 0;
    m_label = 0;
    m_race = 0;
    m_unused = 0;
    m_broodwar_flag = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void techdata_dat_t::_read() {
    int l_mineral_cost = num_lines();
    m_mineral_cost = new std::vector<uint16_t>();
    m_mineral_cost->reserve(l_mineral_cost);
    for (int i = 0; i < l_mineral_cost; i++) {
        m_mineral_cost->push_back(m__io->read_u2le());
    }
    int l_vespene_cost = num_lines();
    m_vespene_cost = new std::vector<uint16_t>();
    m_vespene_cost->reserve(l_vespene_cost);
    for (int i = 0; i < l_vespene_cost; i++) {
        m_vespene_cost->push_back(m__io->read_u2le());
    }
    int l_research_time = num_lines();
    m_research_time = new std::vector<uint16_t>();
    m_research_time->reserve(l_research_time);
    for (int i = 0; i < l_research_time; i++) {
        m_research_time->push_back(m__io->read_u2le());
    }
    int l_energy_required = num_lines();
    m_energy_required = new std::vector<uint16_t>();
    m_energy_required->reserve(l_energy_required);
    for (int i = 0; i < l_energy_required; i++) {
        m_energy_required->push_back(m__io->read_u2le());
    }
    int l_unknown4 = num_lines();
    m_unknown4 = new std::vector<uint32_t>();
    m_unknown4->reserve(l_unknown4);
    for (int i = 0; i < l_unknown4; i++) {
        m_unknown4->push_back(m__io->read_u4le());
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
    int l_unused = num_lines();
    m_unused = new std::vector<uint8_t>();
    m_unused->reserve(l_unused);
    for (int i = 0; i < l_unused; i++) {
        m_unused->push_back(m__io->read_u1());
    }
    n_broodwar_flag = true;
    if (has_broodwar_flag() == true) {
        n_broodwar_flag = false;
        int l_broodwar_flag = num_lines();
        m_broodwar_flag = new std::vector<uint8_t>();
        m_broodwar_flag->reserve(l_broodwar_flag);
        for (int i = 0; i < l_broodwar_flag; i++) {
            m_broodwar_flag->push_back(m__io->read_u1());
        }
    }
}

techdata_dat_t::~techdata_dat_t() {
    _clean_up();
}

void techdata_dat_t::_clean_up() {
    if (m_mineral_cost) {
        delete m_mineral_cost; m_mineral_cost = 0;
    }
    if (m_vespene_cost) {
        delete m_vespene_cost; m_vespene_cost = 0;
    }
    if (m_research_time) {
        delete m_research_time; m_research_time = 0;
    }
    if (m_energy_required) {
        delete m_energy_required; m_energy_required = 0;
    }
    if (m_unknown4) {
        delete m_unknown4; m_unknown4 = 0;
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
    if (m_unused) {
        delete m_unused; m_unused = 0;
    }
    if (!n_broodwar_flag) {
        if (m_broodwar_flag) {
            delete m_broodwar_flag; m_broodwar_flag = 0;
        }
    }
}
