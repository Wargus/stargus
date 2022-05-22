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
    class megatile_type_t;
    class graphic_ref_type_t;

    tileset_vx4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, tileset_vx4_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~tileset_vx4_t();

    class megatile_type_t : public kaitai::kstruct {

    public:

        megatile_type_t(kaitai::kstream* p__io, tileset_vx4_t* p__parent = 0, tileset_vx4_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~megatile_type_t();

    private:
        std::vector<graphic_ref_type_t*>* m_graphic_ref;
        tileset_vx4_t* m__root;
        tileset_vx4_t* m__parent;

    public:
        std::vector<graphic_ref_type_t*>* graphic_ref() const { return m_graphic_ref; }
        tileset_vx4_t* _root() const { return m__root; }
        tileset_vx4_t* _parent() const { return m__parent; }
    };

    class graphic_ref_type_t : public kaitai::kstruct {

    public:

        graphic_ref_type_t(kaitai::kstream* p__io, tileset_vx4_t::megatile_type_t* p__parent = 0, tileset_vx4_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~graphic_ref_type_t();

    private:
        bool f_vr4_ref;
        int32_t m_vr4_ref;

    public:
        int32_t vr4_ref();

    private:
        uint64_t m_vr4_ref_raw;
        bool m_horizontal_flip;
        tileset_vx4_t* m__root;
        tileset_vx4_t::megatile_type_t* m__parent;

    public:
        uint64_t vr4_ref_raw() const { return m_vr4_ref_raw; }
        bool horizontal_flip() const { return m_horizontal_flip; }
        tileset_vx4_t* _root() const { return m__root; }
        tileset_vx4_t::megatile_type_t* _parent() const { return m__parent; }
    };

private:
    std::vector<megatile_type_t*>* m_elements;
    tileset_vx4_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<megatile_type_t*>* elements() const { return m_elements; }
    tileset_vx4_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // TILESET_VX4_H_
