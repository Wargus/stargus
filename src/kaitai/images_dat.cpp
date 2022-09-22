// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "images_dat.h"

images_dat_t::images_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, images_dat_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_grp = 0;
    m_gfx_turns = 0;
    m_clickable = 0;
    m_use_full_iscript = 0;
    m_draw_if_cloaked = 0;
    m_draw_function = 0;
    m_remapping = 0;
    m_iscript_id = 0;
    m_shield_overlay = 0;
    m_attack_overlay = 0;
    m_damage_overlay = 0;
    m_special_overlay = 0;
    m_landing_dust_overlay = 0;
    m_lift_off_dust_overlay = 0;
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

void images_dat_t::_read() {
    m_grp = new std::vector<uint32_t>();
    const int l_grp = num_lines();
    for (int i = 0; i < l_grp; i++) {
        m_grp->push_back(m__io->read_u4le());
    }
    m_gfx_turns = new std::vector<uint8_t>();
    const int l_gfx_turns = num_lines();
    for (int i = 0; i < l_gfx_turns; i++) {
        m_gfx_turns->push_back(m__io->read_u1());
    }
    m_clickable = new std::vector<uint8_t>();
    const int l_clickable = num_lines();
    for (int i = 0; i < l_clickable; i++) {
        m_clickable->push_back(m__io->read_u1());
    }
    m_use_full_iscript = new std::vector<uint8_t>();
    const int l_use_full_iscript = num_lines();
    for (int i = 0; i < l_use_full_iscript; i++) {
        m_use_full_iscript->push_back(m__io->read_u1());
    }
    m_draw_if_cloaked = new std::vector<uint8_t>();
    const int l_draw_if_cloaked = num_lines();
    for (int i = 0; i < l_draw_if_cloaked; i++) {
        m_draw_if_cloaked->push_back(m__io->read_u1());
    }
    m_draw_function = new std::vector<draw_function_enum_t>();
    const int l_draw_function = num_lines();
    for (int i = 0; i < l_draw_function; i++) {
        m_draw_function->push_back(static_cast<images_dat_t::draw_function_enum_t>(m__io->read_u1()));
    }
    m_remapping = new std::vector<remapping_enum_t>();
    const int l_remapping = num_lines();
    for (int i = 0; i < l_remapping; i++) {
        m_remapping->push_back(static_cast<images_dat_t::remapping_enum_t>(m__io->read_u1()));
    }
    m_iscript_id = new std::vector<uint32_t>();
    const int l_iscript_id = num_lines();
    for (int i = 0; i < l_iscript_id; i++) {
        m_iscript_id->push_back(m__io->read_u4le());
    }
    m_shield_overlay = new std::vector<uint32_t>();
    const int l_shield_overlay = num_lines();
    for (int i = 0; i < l_shield_overlay; i++) {
        m_shield_overlay->push_back(m__io->read_u4le());
    }
    m_attack_overlay = new std::vector<uint32_t>();
    const int l_attack_overlay = num_lines();
    for (int i = 0; i < l_attack_overlay; i++) {
        m_attack_overlay->push_back(m__io->read_u4le());
    }
    m_damage_overlay = new std::vector<uint32_t>();
    const int l_damage_overlay = num_lines();
    for (int i = 0; i < l_damage_overlay; i++) {
        m_damage_overlay->push_back(m__io->read_u4le());
    }
    m_special_overlay = new std::vector<uint32_t>();
    const int l_special_overlay = num_lines();
    for (int i = 0; i < l_special_overlay; i++) {
        m_special_overlay->push_back(m__io->read_u4le());
    }
    m_landing_dust_overlay = new std::vector<uint32_t>();
    const int l_landing_dust_overlay = num_lines();
    for (int i = 0; i < l_landing_dust_overlay; i++) {
        m_landing_dust_overlay->push_back(m__io->read_u4le());
    }
    m_lift_off_dust_overlay = new std::vector<uint32_t>();
    const int l_lift_off_dust_overlay = num_lines();
    for (int i = 0; i < l_lift_off_dust_overlay; i++) {
        m_lift_off_dust_overlay->push_back(m__io->read_u4le());
    }
}

images_dat_t::~images_dat_t() {
    _clean_up();
}

void images_dat_t::_clean_up() {
    if (m_grp) {
        delete m_grp; m_grp = 0;
    }
    if (m_gfx_turns) {
        delete m_gfx_turns; m_gfx_turns = 0;
    }
    if (m_clickable) {
        delete m_clickable; m_clickable = 0;
    }
    if (m_use_full_iscript) {
        delete m_use_full_iscript; m_use_full_iscript = 0;
    }
    if (m_draw_if_cloaked) {
        delete m_draw_if_cloaked; m_draw_if_cloaked = 0;
    }
    if (m_draw_function) {
        delete m_draw_function; m_draw_function = 0;
    }
    if (m_remapping) {
        delete m_remapping; m_remapping = 0;
    }
    if (m_iscript_id) {
        delete m_iscript_id; m_iscript_id = 0;
    }
    if (m_shield_overlay) {
        delete m_shield_overlay; m_shield_overlay = 0;
    }
    if (m_attack_overlay) {
        delete m_attack_overlay; m_attack_overlay = 0;
    }
    if (m_damage_overlay) {
        delete m_damage_overlay; m_damage_overlay = 0;
    }
    if (m_special_overlay) {
        delete m_special_overlay; m_special_overlay = 0;
    }
    if (m_landing_dust_overlay) {
        delete m_landing_dust_overlay; m_landing_dust_overlay = 0;
    }
    if (m_lift_off_dust_overlay) {
        delete m_lift_off_dust_overlay; m_lift_off_dust_overlay = 0;
    }
}

int32_t images_dat_t::num_lines() {
    if (f_num_lines)
        return m_num_lines;
    m_num_lines = (file_size() / record_size());
    f_num_lines = true;
    return m_num_lines;
}

int8_t images_dat_t::record_size() {
    if (f_record_size)
        return m_record_size;
    m_record_size = 38;
    f_record_size = true;
    return m_record_size;
}

int32_t images_dat_t::file_size() {
    if (f_file_size)
        return m_file_size;
    m_file_size = _io()->size();
    f_file_size = true;
    return m_file_size;
}
