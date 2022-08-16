#ifndef PORTDATA_DAT_H_
#define PORTDATA_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class portdata_dat_t : public kaitai::kstruct {

public:

    portdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, portdata_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~portdata_dat_t();

private:
    bool f_num_lines;
    int32_t m_num_lines;

public:

    /**
     * A division of file size though the record size gives the number of records in the file to parse.
     */
    int32_t num_lines();

private:
    bool f_record_size;
    int8_t m_record_size;

public:

    /**
     * The size of one data record. This is all type sizes in the format summarized.
     */
    int8_t record_size();

private:
    bool f_file_size;
    int32_t m_file_size;

public:
    int32_t file_size();

private:
    std::vector<uint32_t>* m_video;
    std::vector<uint8_t>* m_smk_change;
    std::vector<uint8_t>* m_unknown1;
    portdata_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * Smacker portrait video for idle and talking animation. Add 110 to get the talking animation. [1-based pointer to portdata.tbl]
     */
    std::vector<uint32_t>* video() const { return m_video; }

    /**
     * Controls how often the first SMK animation, with the index of 0, will be overlooked and a portrait with different index will be played. The higher the value and the more it gets near 100, the more often will the first SMK be skipped. Values over 100 make the game use only the first portrait.
     */
    std::vector<uint8_t>* smk_change() const { return m_smk_change; }
    std::vector<uint8_t>* unknown1() const { return m_unknown1; }
    portdata_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // PORTDATA_DAT_H_
