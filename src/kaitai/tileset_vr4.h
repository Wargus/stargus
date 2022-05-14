#ifndef TILESET_VR4_H_
#define TILESET_VR4_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class tileset_vr4_t : public kaitai::kstruct {

public:
    class pixel_type_t;

    tileset_vr4_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, tileset_vr4_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~tileset_vr4_t();

    class pixel_type_t : public kaitai::kstruct {

    public:

        pixel_type_t(kaitai::kstream* p__io, tileset_vr4_t* p__parent = 0, tileset_vr4_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~pixel_type_t();

    private:
        std::string m_color_palette;
        tileset_vr4_t* m__root;
        tileset_vr4_t* m__parent;

    public:
        std::string color_palette() const { return m_color_palette; }
        tileset_vr4_t* _root() const { return m__root; }
        tileset_vr4_t* _parent() const { return m__parent; }
    };

private:
    std::vector<pixel_type_t*>* m_pixel_data;
    tileset_vr4_t* m__root;
    kaitai::kstruct* m__parent;

public:
    std::vector<pixel_type_t*>* pixel_data() const { return m_pixel_data; }
    tileset_vr4_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // TILESET_VR4_H_
