#ifndef TILESET_CV5_H_
#define TILESET_CV5_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class tileset_cv5_t : public kaitai::kstruct {

public:
    class group_t;
    class ground_nibbles_t;

    tileset_cv5_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, tileset_cv5_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~tileset_cv5_t();

    class group_t : public kaitai::kstruct {

    public:

        group_t(kaitai::kstream* p__io, tileset_cv5_t* p__parent = 0, tileset_cv5_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~group_t();

    private:
        uint16_t m_doodad;
        ground_nibbles_t* m_ground;
        uint16_t m_unknown1;
        uint16_t m_unknown2;
        uint16_t m_unknown3;
        uint16_t m_unknown4;
        uint16_t m_unknown5;
        uint16_t m_unknown6;
        uint16_t m_unknown7;
        uint16_t m_unknown8;
        std::vector<uint16_t>* m_megatile_references;
        tileset_cv5_t* m__root;
        tileset_cv5_t* m__parent;

    public:
        uint16_t doodad() const { return m_doodad; }
        ground_nibbles_t* ground() const { return m_ground; }
        uint16_t unknown1() const { return m_unknown1; }
        uint16_t unknown2() const { return m_unknown2; }
        uint16_t unknown3() const { return m_unknown3; }
        uint16_t unknown4() const { return m_unknown4; }
        uint16_t unknown5() const { return m_unknown5; }
        uint16_t unknown6() const { return m_unknown6; }
        uint16_t unknown7() const { return m_unknown7; }
        uint16_t unknown8() const { return m_unknown8; }
        std::vector<uint16_t>* megatile_references() const { return m_megatile_references; }
        tileset_cv5_t* _root() const { return m__root; }
        tileset_cv5_t* _parent() const { return m__parent; }
    };

    class ground_nibbles_t : public kaitai::kstruct {

    public:

        ground_nibbles_t(kaitai::kstream* p__io, tileset_cv5_t::group_t* p__parent = 0, tileset_cv5_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~ground_nibbles_t();

    private:
        uint64_t m_one;
        uint64_t m_two;
        uint64_t m_tree;
        uint64_t m_four;
        tileset_cv5_t* m__root;
        tileset_cv5_t::group_t* m__parent;

    public:
        uint64_t one() const { return m_one; }
        uint64_t two() const { return m_two; }
        uint64_t tree() const { return m_tree; }
        uint64_t four() const { return m_four; }
        tileset_cv5_t* _root() const { return m__root; }
        tileset_cv5_t::group_t* _parent() const { return m__parent; }
    };

private:
    std::vector<group_t*>* m_element;
    tileset_cv5_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<group_t*>* element() const { return m_element; }
    tileset_cv5_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // TILESET_CV5_H_
