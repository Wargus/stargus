#ifndef TILESET_VX4_H_
#define TILESET_VX4_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class tileset_vx4_t : public kaitai::kstruct {

public:
    class tile_t;

    tileset_vx4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, tileset_vx4_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~tileset_vx4_t();

    class tile_t : public kaitai::kstruct {

    public:

        tile_t(kaitai::kstream* p__io, tileset_vx4_t* p__parent = 0, tileset_vx4_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~tile_t();

    private:
        std::vector<uint16_t>* m_flags;
        tileset_vx4_t* m__root;
        tileset_vx4_t* m__parent;

    public:
        std::vector<uint16_t>* flags() const { return m_flags; }
        tileset_vx4_t* _root() const { return m__root; }
        tileset_vx4_t* _parent() const { return m__parent; }
    };

private:
    std::vector<tile_t*>* m_id;
    tileset_vx4_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<tile_t*>* id() const { return m_id; }
    tileset_vx4_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // TILESET_VX4_H_
