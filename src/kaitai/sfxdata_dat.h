#ifndef SFXDATA_DAT_H_
#define SFXDATA_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class sfxdata_dat_t : public kaitai::kstruct {

public:

    sfxdata_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, sfxdata_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~sfxdata_dat_t();

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
    std::vector<uint32_t>* m_sound_file;
    std::vector<uint8_t>* m_unknown1;
    std::vector<uint8_t>* m_unknown2;
    std::vector<uint16_t>* m_unknown3;
    std::vector<uint8_t>* m_unknown4;
    sfxdata_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * The actual wave file associated with the sfxdata entry. [pointer to sfxdata.tbl]
     */
    std::vector<uint32_t>* sound_file() const { return m_sound_file; }
    std::vector<uint8_t>* unknown1() const { return m_unknown1; }
    std::vector<uint8_t>* unknown2() const { return m_unknown2; }
    std::vector<uint16_t>* unknown3() const { return m_unknown3; }
    std::vector<uint8_t>* unknown4() const { return m_unknown4; }
    sfxdata_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // SFXDATA_DAT_H_
