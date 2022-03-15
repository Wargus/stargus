// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "grp_file.h"

grp_file_t::grp_file_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, grp_file_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_image_frames = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void grp_file_t::_read() {
    m_num_images = m__io->read_u2le();
    m_max_width = m__io->read_u2le();
    m_max_height = m__io->read_u2le();
    int l_image_frames = num_images();
    m_image_frames = new std::vector<image_frame_type_t*>();
    m_image_frames->reserve(l_image_frames);
    for (int i = 0; i < l_image_frames; i++) {
        m_image_frames->push_back(new image_frame_type_t(m__io, this, m__root));
    }
}

grp_file_t::~grp_file_t() {
    _clean_up();
}

void grp_file_t::_clean_up() {
    if (m_image_frames) {
        for (std::vector<image_frame_type_t*>::iterator it = m_image_frames->begin(); it != m_image_frames->end(); ++it) {
            delete *it;
        }
        delete m_image_frames; m_image_frames = 0;
    }
}

grp_file_t::image_frame_type_t::image_frame_type_t(kaitai::kstream* p__io, grp_file_t* p__parent, grp_file_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_line_offsets = 0;
    f_line_offsets = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void grp_file_t::image_frame_type_t::_read() {
    m_x_offset = m__io->read_u1();
    m_y_offset = m__io->read_u1();
    m_width = m__io->read_u1();
    m_height = m__io->read_u1();
    m_line_offset = m__io->read_u4le();
}

grp_file_t::image_frame_type_t::~image_frame_type_t() {
    _clean_up();
}

void grp_file_t::image_frame_type_t::_clean_up() {
    if (f_line_offsets) {
        if (m_line_offsets) {
            for (std::vector<line_offset_type_t*>::iterator it = m_line_offsets->begin(); it != m_line_offsets->end(); ++it) {
                delete *it;
            }
            delete m_line_offsets; m_line_offsets = 0;
        }
    }
}

std::vector<grp_file_t::line_offset_type_t*>* grp_file_t::image_frame_type_t::line_offsets() {
    if (f_line_offsets)
        return m_line_offsets;
    std::streampos _pos = m__io->pos();
    m__io->seek(line_offset());
    int l_line_offsets = height();
    m_line_offsets = new std::vector<line_offset_type_t*>();
    m_line_offsets->reserve(l_line_offsets);
    for (int i = 0; i < l_line_offsets; i++) {
        m_line_offsets->push_back(new line_offset_type_t(i, i != (height() - 1), m__io, this, m__root));
    }
    m__io->seek(_pos);
    f_line_offsets = true;
    return m_line_offsets;
}

grp_file_t::line_offset_type_t::line_offset_type_t(uint16_t p_index, bool p_has_next, kaitai::kstream* p__io, grp_file_t::image_frame_type_t* p__parent, grp_file_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_index = p_index;
    m_has_next = p_has_next;
    f_rle_offsets = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void grp_file_t::line_offset_type_t::_read() {
    m_offset = m__io->read_u2le();
}

grp_file_t::line_offset_type_t::~line_offset_type_t() {
    _clean_up();
}

void grp_file_t::line_offset_type_t::_clean_up() {
    if (f_rle_offsets) {
    }
}

std::string grp_file_t::line_offset_type_t::rle_offsets() {
    if (f_rle_offsets)
        return m_rle_offsets;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->line_offset() + offset()));
    m_rle_offsets = m__io->read_bytes(((has_next()) ? ((_parent()->line_offsets()->at((index() + 1))->offset() - offset())) : ((_io()->size() - _io()->pos()))));
    m__io->seek(_pos);
    f_rle_offsets = true;
    return m_rle_offsets;
}
