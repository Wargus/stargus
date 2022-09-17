// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "techdata_dat.h"

techdata_dat_t::techdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, techdata_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
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
    f_record_count_broodwar = false;
    f_record_count = false;
    f_num_lines = false;
    f_has_broodwar_flag = false;
    f_file_size = false;
    f_record_size = false;
    f_record_size_broodwar = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void techdata_dat_t::_read() {
    m_mineral_cost = new std::vector<uint16_t>();
    const int l_mineral_cost = num_lines();
    for (int i = 0; i < l_mineral_cost; i++) {
        m_mineral_cost->push_back(m__io->read_u2le());
    }
    m_vespene_cost = new std::vector<uint16_t>();
    const int l_vespene_cost = num_lines();
    for (int i = 0; i < l_vespene_cost; i++) {
        m_vespene_cost->push_back(m__io->read_u2le());
    }
    m_research_time = new std::vector<uint16_t>();
    const int l_research_time = num_lines();
    for (int i = 0; i < l_research_time; i++) {
        m_research_time->push_back(m__io->read_u2le());
    }
    m_energy_required = new std::vector<uint16_t>();
    const int l_energy_required = num_lines();
    for (int i = 0; i < l_energy_required; i++) {
        m_energy_required->push_back(m__io->read_u2le());
    }
    m_unknown4 = new std::vector<uint32_t>();
    const int l_unknown4 = num_lines();
    for (int i = 0; i < l_unknown4; i++) {
        m_unknown4->push_back(m__io->read_u4le());
    }
    m_icon = new std::vector<uint16_t>();
    const int l_icon = num_lines();
    for (int i = 0; i < l_icon; i++) {
        m_icon->push_back(m__io->read_u2le());
    }
    m_label = new std::vector<uint16_t>();
    const int l_label = num_lines();
    for (int i = 0; i < l_label; i++) {
        m_label->push_back(m__io->read_u2le());
    }
    m_race = new std::vector<uint8_t>();
    const int l_race = num_lines();
    for (int i = 0; i < l_race; i++) {
        m_race->push_back(m__io->read_u1());
    }
    m_unused = new std::vector<uint8_t>();
    const int l_unused = num_lines();
    for (int i = 0; i < l_unused; i++) {
        m_unused->push_back(m__io->read_u1());
    }
    n_broodwar_flag = true;
    if (has_broodwar_flag() == true) {
        n_broodwar_flag = false;
        m_broodwar_flag = new std::vector<uint8_t>();
        const int l_broodwar_flag = num_lines();
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

int32_t techdata_dat_t::record_count_broodwar() {
    if (f_record_count_broodwar)
        return m_record_count_broodwar;
    m_record_count_broodwar = (file_size() / record_size_broodwar());
    f_record_count_broodwar = true;
    return m_record_count_broodwar;
}

int32_t techdata_dat_t::record_count() {
    if (f_record_count)
        return m_record_count;
    m_record_count = (file_size() / record_size());
    f_record_count = true;
    return m_record_count;
}

int32_t techdata_dat_t::num_lines() {
    if (f_num_lines)
        return m_num_lines;
    m_num_lines = ((kaitai::kstream::mod(file_size(), record_size()) == 0) ? (record_count()) : (record_count_broodwar()));
    f_num_lines = true;
    return m_num_lines;
}

bool techdata_dat_t::has_broodwar_flag() {
    if (f_has_broodwar_flag)
        return m_has_broodwar_flag;
    m_has_broodwar_flag = ((kaitai::kstream::mod(file_size(), record_size()) == 0) ? (false) : (true));
    f_has_broodwar_flag = true;
    return m_has_broodwar_flag;
}

int32_t techdata_dat_t::file_size() {
    if (f_file_size)
        return m_file_size;
    m_file_size = _io()->size();
    f_file_size = true;
    return m_file_size;
}

int8_t techdata_dat_t::record_size() {
    if (f_record_size)
        return m_record_size;
    m_record_size = 18;
    f_record_size = true;
    return m_record_size;
}

int8_t techdata_dat_t::record_size_broodwar() {
    if (f_record_size_broodwar)
        return m_record_size_broodwar;
    m_record_size_broodwar = 19;
    f_record_size_broodwar = true;
    return m_record_size_broodwar;
}
