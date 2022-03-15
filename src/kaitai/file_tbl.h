#ifndef FILE_TBL_H_
#define FILE_TBL_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class file_tbl_t : public kaitai::kstruct {

public:
    class tbl_entry_t;

    file_tbl_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, file_tbl_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~file_tbl_t();

    class tbl_entry_t : public kaitai::kstruct {

    public:

        tbl_entry_t(uint16_t p_i, kaitai::kstream* p__io, file_tbl_t* p__parent = 0, file_tbl_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~tbl_entry_t();

    private:
        bool f_len;
        int32_t m_len;

    public:
        int32_t len();

    private:
        bool f_dyn_end;
        int32_t m_dyn_end;

    public:
        int32_t dyn_end();

    private:
        bool f_entry;
        std::vector<uint8_t>* m_entry;

    public:
        std::vector<uint8_t>* entry();

    private:
        uint16_t m_i;
        file_tbl_t* m__root;
        file_tbl_t* m__parent;

    public:
        uint16_t i() const { return m_i; }
        file_tbl_t* _root() const { return m__root; }
        file_tbl_t* _parent() const { return m__parent; }
    };

private:
    bool f_tbl_entries;
    std::vector<tbl_entry_t*>* m_tbl_entries;

public:
    std::vector<tbl_entry_t*>* tbl_entries();

private:
    uint16_t m_num_offsets;
    std::vector<uint16_t>* m_ofs_files;
    file_tbl_t* m__root;
    kaitai::kstruct* m__parent;

public:
    uint16_t num_offsets() const { return m_num_offsets; }
    std::vector<uint16_t>* ofs_files() const { return m_ofs_files; }
    file_tbl_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // FILE_TBL_H_
