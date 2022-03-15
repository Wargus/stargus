#ifndef GRP_FILE_H_
#define GRP_FILE_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class grp_file_t : public kaitai::kstruct {

public:
    class image_frame_type_t;
    class line_offset_type_t;

    grp_file_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, grp_file_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~grp_file_t();

    class image_frame_type_t : public kaitai::kstruct {

    public:

        image_frame_type_t(kaitai::kstream* p__io, grp_file_t* p__parent = 0, grp_file_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~image_frame_type_t();

    private:
        bool f_line_offsets;
        std::vector<line_offset_type_t*>* m_line_offsets;

    public:
        std::vector<line_offset_type_t*>* line_offsets();

    private:
        uint8_t m_x_offset;
        uint8_t m_y_offset;
        uint8_t m_width;
        uint8_t m_height;
        uint32_t m_line_offset;
        grp_file_t* m__root;
        grp_file_t* m__parent;

    public:

        /**
         * test
         */
        uint8_t x_offset() const { return m_x_offset; }

        /**
         * test
         */
        uint8_t y_offset() const { return m_y_offset; }

        /**
         * test
         */
        uint8_t width() const { return m_width; }

        /**
         * test
         */
        uint8_t height() const { return m_height; }

        /**
         * test
         */
        uint32_t line_offset() const { return m_line_offset; }
        grp_file_t* _root() const { return m__root; }
        grp_file_t* _parent() const { return m__parent; }
    };

    class line_offset_type_t : public kaitai::kstruct {

    public:

        line_offset_type_t(uint16_t p_index, bool p_has_next, kaitai::kstream* p__io, grp_file_t::image_frame_type_t* p__parent = 0, grp_file_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~line_offset_type_t();

    private:
        bool f_rle_offsets;
        std::string m_rle_offsets;

    public:
        std::string rle_offsets();

    private:
        uint16_t m_offset;
        uint16_t m_index;
        bool m_has_next;
        grp_file_t* m__root;
        grp_file_t::image_frame_type_t* m__parent;

    public:

        /**
         * test
         */
        uint16_t offset() const { return m_offset; }
        uint16_t index() const { return m_index; }
        bool has_next() const { return m_has_next; }
        grp_file_t* _root() const { return m__root; }
        grp_file_t::image_frame_type_t* _parent() const { return m__parent; }
    };

private:
    uint16_t m_num_images;
    uint16_t m_max_width;
    uint16_t m_max_height;
    std::vector<image_frame_type_t*>* m_image_frames;
    grp_file_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * test
     */
    uint16_t num_images() const { return m_num_images; }

    /**
     * test
     */
    uint16_t max_width() const { return m_max_width; }

    /**
     * test
     */
    uint16_t max_height() const { return m_max_height; }

    /**
     * test
     */
    std::vector<image_frame_type_t*>* image_frames() const { return m_image_frames; }
    grp_file_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // GRP_FILE_H_
