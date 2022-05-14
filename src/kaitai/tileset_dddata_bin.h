#ifndef TILESET_DDDATA_BIN_H_
#define TILESET_DDDATA_BIN_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class tileset_dddata_bin_t : public kaitai::kstruct {

public:
    class doodad_type_t;

    tileset_dddata_bin_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, tileset_dddata_bin_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~tileset_dddata_bin_t();

    class doodad_type_t : public kaitai::kstruct {

    public:

        doodad_type_t(kaitai::kstream* p__io, tileset_dddata_bin_t* p__parent = 0, tileset_dddata_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~doodad_type_t();

    private:
        std::vector<uint16_t>* m_placing;
        tileset_dddata_bin_t* m__root;
        tileset_dddata_bin_t* m__parent;

    public:
        std::vector<uint16_t>* placing() const { return m_placing; }
        tileset_dddata_bin_t* _root() const { return m__root; }
        tileset_dddata_bin_t* _parent() const { return m__parent; }
    };

private:
    std::vector<doodad_type_t*>* m_doodad;
    tileset_dddata_bin_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<doodad_type_t*>* doodad() const { return m_doodad; }
    tileset_dddata_bin_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // TILESET_DDDATA_BIN_H_
