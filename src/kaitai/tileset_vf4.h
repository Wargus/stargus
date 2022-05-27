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
    class minitile_t;
    class minitile_flags_types_t;

    tileset_vf4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, tileset_vf4_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~tileset_vf4_t();

    class minitile_t : public kaitai::kstruct {

    public:

        minitile_t(kaitai::kstream* p__io, tileset_vf4_t* p__parent = 0, tileset_vf4_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~minitile_t();

    private:
        std::vector<minitile_flags_types_t*>* m_flags;
        tileset_vf4_t* m__root;
        tileset_vf4_t* m__parent;

    public:
        std::vector<minitile_flags_types_t*>* flags() const { return m_flags; }
        tileset_vf4_t* _root() const { return m__root; }
        tileset_vf4_t* _parent() const { return m__parent; }
    };

    class minitile_flags_types_t : public kaitai::kstruct {

    public:

        minitile_flags_types_t(kaitai::kstream* p__io, tileset_vf4_t::minitile_t* p__parent = 0, tileset_vf4_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~minitile_flags_types_t();

    private:
        bool f_walkable;
        int32_t m_walkable;

    public:
        int32_t walkable();

    private:
        bool f_blocks_view;
        int32_t m_blocks_view;

    public:
        int32_t blocks_view();

    private:
        bool f_mid_elevation;
        int32_t m_mid_elevation;

    public:
        int32_t mid_elevation();

    private:
        bool f_ramp;
        int32_t m_ramp;

    public:
        int32_t ramp();

    private:
        bool f_high_elevation;
        int32_t m_high_elevation;

    public:
        int32_t high_elevation();

    private:
        uint16_t m_flags_raw;
        tileset_vf4_t* m__root;
        tileset_vf4_t::minitile_t* m__parent;

    public:
        uint16_t flags_raw() const { return m_flags_raw; }
        tileset_vf4_t* _root() const { return m__root; }
        tileset_vf4_t::minitile_t* _parent() const { return m__parent; }
    };

private:
    std::vector<minitile_t*>* m_elements;
    tileset_vf4_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<minitile_t*>* elements() const { return m_elements; }
    tileset_vf4_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // TILESET_VF4_H_
