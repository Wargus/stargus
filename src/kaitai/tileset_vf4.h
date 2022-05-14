#ifndef TILESET_VF4_H_
#define TILESET_VF4_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class tileset_vf4_t : public kaitai::kstruct {

public:
    class minitile_flags_t;

    tileset_vf4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, tileset_vf4_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~tileset_vf4_t();

    class minitile_flags_t : public kaitai::kstruct {

    public:

        minitile_flags_t(kaitai::kstream* p__io, tileset_vf4_t* p__parent = 0, tileset_vf4_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~minitile_flags_t();

    private:
        std::vector<uint16_t>* m_flags;
        tileset_vf4_t* m__root;
        tileset_vf4_t* m__parent;

    public:
        std::vector<uint16_t>* flags() const { return m_flags; }
        tileset_vf4_t* _root() const { return m__root; }
        tileset_vf4_t* _parent() const { return m__parent; }
    };

private:
    std::vector<minitile_flags_t*>* m_id;
    tileset_vf4_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<minitile_flags_t*>* id() const { return m_id; }
    tileset_vf4_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // TILESET_VF4_H_
