#ifndef TECHDATA_DAT_H_
#define TECHDATA_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class techdata_dat_t : public kaitai::kstruct {

public:

    techdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, techdata_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~techdata_dat_t();

private:
    bool f_record_count_broodwar;
    int32_t m_record_count_broodwar;

public:

    /**
     * Count of records in the data file. (Need to check with modulo operator if this is the case) [broodwar data]
     */
    int32_t record_count_broodwar();

private:
    bool f_record_count;
    int32_t m_record_count;

public:

    /**
     * Count of records in the data file. (Need to check with modulo operator if this is the case)
     */
    int32_t record_count();

private:
    bool f_num_lines;
    int32_t m_num_lines;

public:

    /**
     * A division of file size though the record size gives the number of records in the file to parse.
     */
    int32_t num_lines();

private:
    bool f_has_broodwar_flag;
    bool m_has_broodwar_flag;

public:

    /**
     * true in case the brodowar data is parsed
     */
    bool has_broodwar_flag();

private:
    bool f_file_size;
    int32_t m_file_size;

public:
    int32_t file_size();

private:
    bool f_record_size;
    int8_t m_record_size;

public:

    /**
     * The size of one data record. This is all type sizes in the format summarized.
     */
    int8_t record_size();

private:
    bool f_record_size_broodwar;
    int8_t m_record_size_broodwar;

public:

    /**
     * The size of one data record. This is all type sizes in the format summarized. [broodwar data]
     */
    int8_t record_size_broodwar();

private:
    std::vector<uint16_t>* m_mineral_cost;
    std::vector<uint16_t>* m_vespene_cost;
    std::vector<uint16_t>* m_research_time;
    std::vector<uint16_t>* m_energy_required;
    std::vector<uint32_t>* m_unknown4;
    std::vector<uint16_t>* m_icon;
    std::vector<uint16_t>* m_label;
    std::vector<uint8_t>* m_race;
    std::vector<uint8_t>* m_unused;
    std::vector<uint8_t>* m_broodwar_flag;
    bool n_broodwar_flag;

public:
    bool _is_null_broodwar_flag() { broodwar_flag(); return n_broodwar_flag; };

private:
    techdata_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * Minerals cost for the research of the technology.
     */
    std::vector<uint16_t>* mineral_cost() const { return m_mineral_cost; }

    /**
     * Vespene gas cost for the research of the technology.
     */
    std::vector<uint16_t>* vespene_cost() const { return m_vespene_cost; }

    /**
     * Research time of the technology in 1/24ths of a second (at Fastest speed). Value of 0 will crash the game.
     */
    std::vector<uint16_t>* research_time() const { return m_research_time; }

    /**
     * Energy cost for using the technology.
     */
    std::vector<uint16_t>* energy_required() const { return m_energy_required; }

    /**
     * unknown
     */
    std::vector<uint32_t>* unknown4() const { return m_unknown4; }

    /**
     * Icon displayed for the technology. [pointer to a frame in unit\cmdbtns\cmdicons.grp]
     */
    std::vector<uint16_t>* icon() const { return m_icon; }

    /**
     * The name of the technology. Displayed in StarEdit and when you highlight the tech's icon during research. [pointer to stat_txt.tbl]
     */
    std::vector<uint16_t>* label() const { return m_label; }

    /**
     * Determines which race can use/research the technology. "All" will disable the tech in StarEdit (but not in-game).
     */
    std::vector<uint8_t>* race() const { return m_race; }

    /**
     * unused
     */
    std::vector<uint8_t>* unused() const { return m_unused; }

    /**
     * Makes the technology available only while playing the BroodWar expansion set.
     */
    std::vector<uint8_t>* broodwar_flag() const { return m_broodwar_flag; }
    techdata_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // TECHDATA_DAT_H_
