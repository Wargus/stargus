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

        image_frame_type_t(uint16_t p_frame_id, kaitai::kstream* p__io, grp_file_t* p__parent = 0, grp_file_t* p__root = 0);

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
        uint16_t m_frame_id;
        grp_file_t* m__root;
        grp_file_t* m__parent;

    public:

        /**
         * todo
         */
        uint8_t x_offset() const { return m_x_offset; }

        /**
         * todo
         */
        uint8_t y_offset() const { return m_y_offset; }

        /**
         * todo
         */
        uint8_t width() const { return m_width; }

        /**
         * todo
         */
        uint8_t height() const { return m_height; }

        /**
         * todo
         */
        uint32_t line_offset() const { return m_line_offset; }
        uint16_t frame_id() const { return m_frame_id; }
        grp_file_t* _root() const { return m__root; }
        grp_file_t* _parent() const { return m__parent; }
    };

    class line_offset_type_t : public kaitai::kstruct {

    public:

        line_offset_type_t(uint16_t p_index, bool p_has_line, kaitai::kstream* p__io, grp_file_t::image_frame_type_t* p__parent = 0, grp_file_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~line_offset_type_t();

    private:
        bool f_last_line_len;
        int32_t m_last_line_len;

    public:

        /**
         * if a next frame is available then
         *   take the line_offset from the next frame AND substract start
         * else (last frame)
         *   from last position in the file substract the start position
         * => the result is the length of the last line of a frame
         */
        int32_t last_line_len();

    private:
        bool f_start;
        int32_t m_start;

    public:

        /**
         * start position of the current RLE line
         */
        int32_t start();

    private:
        bool f_has_frame;
        bool m_has_frame;

    public:

        /**
         * boolean value if the current frame is followed by another frame
         */
        bool has_frame();

    private:
        bool f_rle_offsets;
        std::string m_rle_offsets;

    public:
        std::string rle_offsets();

    private:
        bool f_file_size;
        int32_t m_file_size;

    public:

        /**
         * size of the complete file
         */
        int32_t file_size();

    private:
        bool f_len;
        int32_t m_len;

    public:

        /**
         * check if there is another line following and depending in the result take next offset or complex calculation of last line
         */
        int32_t len();

    private:
        uint16_t m_offset;
        uint16_t m_index;
        bool m_has_line;
        grp_file_t* m__root;
        grp_file_t::image_frame_type_t* m__parent;

    public:

        /**
         * todo
         */
        uint16_t offset() const { return m_offset; }
        uint16_t index() const { return m_index; }

        /**
         * boolean value if the current line is followed by another line in the same frame
         */
        bool has_line() const { return m_has_line; }
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
     * todo
     */
    uint16_t num_images() const { return m_num_images; }

    /**
     * todo
     */
    uint16_t max_width() const { return m_max_width; }

    /**
     * todo
     */
    uint16_t max_height() const { return m_max_height; }

    /**
     * todo
     */
    std::vector<image_frame_type_t*>* image_frames() const { return m_image_frames; }
    grp_file_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // GRP_FILE_H_
