#ifndef UPGRADES_DAT_H_
#define UPGRADES_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class upgrades_dat_t : public kaitai::kstruct {

public:

    upgrades_dat_t(bool p_has_broodwar_flag, uint8_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, upgrades_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~upgrades_dat_t();

private:
    std::vector<uint16_t>* m_mineral_cost_base;
    std::vector<uint16_t>* m_mineral_cost_factor;
    std::vector<uint16_t>* m_vespene_cost_base;
    std::vector<uint16_t>* m_vespene_cost_factor;
    std::vector<uint16_t>* m_research_time_base;
    std::vector<uint16_t>* m_research_time_factor;
    std::vector<uint16_t>* m_unknown6;
    std::vector<uint16_t>* m_icon;
    std::vector<uint16_t>* m_label;
    std::vector<uint8_t>* m_race;
    std::vector<uint8_t>* m_max_repeats;
    std::vector<uint8_t>* m_broodwar_flags;
    bool n_broodwar_flags;

public:
    bool _is_null_broodwar_flags() { broodwar_flags(); return n_broodwar_flags; };

private:
    bool m_has_broodwar_flag;
    uint8_t m_num_lines;
    upgrades_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * Basic minerals cost for the upgrade.
     */
    std::vector<uint16_t>* mineral_cost_base() const { return m_mineral_cost_base; }

    /**
     * Additional cost in minerals, per level of the upgrade.
     */
    std::vector<uint16_t>* mineral_cost_factor() const { return m_mineral_cost_factor; }

    /**
     * Basic Vespene gas cost for the upgrade.
     */
    std::vector<uint16_t>* vespene_cost_base() const { return m_vespene_cost_base; }

    /**
     * Additional cost in Vespene gas, per level of the upgrade.
     */
    std::vector<uint16_t>* vespene_cost_factor() const { return m_vespene_cost_factor; }

    /**
     * Basic research time for the upgrade, in 1/24ths of a second (at Fastest speed). A value of 0 will crash the original game.
     */
    std::vector<uint16_t>* research_time_base() const { return m_research_time_base; }

    /**
     * Additional time the research takes, per level of the upgrade, in 1/24ths of a second (at Fastest speed).
     */
    std::vector<uint16_t>* research_time_factor() const { return m_research_time_factor; }
    std::vector<uint16_t>* unknown6() const { return m_unknown6; }

    /**
     * Icon displayed for the upgrade. [pointer to a frame in unit\cmdbtns\cmdicons.grp]
     */
    std::vector<uint16_t>* icon() const { return m_icon; }

    /**
     * The name of the upgrade. Displayed in StarEdit and when you highlight the upgrade's icon during research. [pointer to stat_txt.tbl]
     */
    std::vector<uint16_t>* label() const { return m_label; }

    /**
     * Determines which race can use/research the upgrade. "All" will disable the tech in StarEdit (but not in-game).
     */
    std::vector<uint8_t>* race() const { return m_race; }

    /**
     * Total number of times the upgrade can be researched.
     */
    std::vector<uint8_t>* max_repeats() const { return m_max_repeats; }

    /**
     * Makes the upgrade available only while playing the BroodWar expansion set.
     */
    std::vector<uint8_t>* broodwar_flags() const { return m_broodwar_flags; }
    bool has_broodwar_flag() const { return m_has_broodwar_flag; }
    uint8_t num_lines() const { return m_num_lines; }
    upgrades_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // UPGRADES_DAT_H_
