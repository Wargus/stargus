#ifndef SPRITES_DAT_H_
#define SPRITES_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class sprites_dat_t : public kaitai::kstruct {

public:

    sprites_dat_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, sprites_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~sprites_dat_t();

private:
    bool f_file_size_rest;
    int32_t m_file_size_rest;

public:

    /**
     * File size for the records after 130. This number might change from file to file.
     */
    int32_t file_size_rest();

private:
    bool f_file_size_first_130;
    int32_t m_file_size_first_130;

public:

    /**
     * File size for the first 130 records that is always static size.
     */
    int32_t file_size_first_130();

private:
    bool f_num_lines;
    int32_t m_num_lines;

public:

    /**
     * A division of the dynamic rest file size though the record size gives the number of records in the file to parse.
     * The static first 130 are then added to this number.
     */
    int32_t num_lines();

private:
    bool f_file_size;
    int32_t m_file_size;

public:
    int32_t file_size();

private:
    bool f_record_size;
    int8_t m_record_size;

public:

    /**
     * The size of one data record. This is all type sizes in the format summarized (starting from record 130).
     */
    int8_t record_size();

private:
    bool f_record_size_first_130;
    int8_t m_record_size_first_130;

public:

    /**
     * The size of one data record. This is all type sizes in the format summarized (the first 130 records).
     */
    int8_t record_size_first_130();

private:
    std::vector<uint16_t>* m_image;
    std::vector<uint8_t>* m_health_bar;
    std::vector<uint8_t>* m_unknown2;
    std::vector<uint8_t>* m_is_visible;
    std::vector<uint8_t>* m_select_circle_image_size;
    std::vector<uint8_t>* m_select_circle_vertical_pos;
    sprites_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * The images.dat entry corresponding to the sprites.dat entry [pointer to images.dat]
     */
    std::vector<uint16_t>* image() const { return m_image; }

    /**
     * The length of the Hit Points/Shields/Energy bar below the sprite, in pixels. The way the actual number of "boxes" is calculated is the following: substract 1 from the value, divide the result by 3 and round it down. Even though a sprite may actually USE less than 6 boxes, 6 boxes is the minimal amount that will be SHOWN in-game (just that some will not be functional). Values below 6 will all result in 1 box being USED.
     * This property is only available from unit index 130 to num_lines
     */
    std::vector<uint8_t>* health_bar() const { return m_health_bar; }

    /**
     * tbd
     */
    std::vector<uint8_t>* unknown2() const { return m_unknown2; }

    /**
     * Sprite will start as visible. Unchecked, used to hide the "White Circle", the Zerg Beacon used by Subterranean Spines, and few other things.
     */
    std::vector<uint8_t>* is_visible() const { return m_is_visible; }

    /**
     * The size of the in-game selection circle. The different sizes are actually different images.dat entries, so in order to use custom ones you need to replace them. The "Dashed" selection circles are used to mark allied units in multiplayer games, but if used on the players own units they will not disappear after deselecting the unit, and also they will NOT be removed on its death, still providing limited vision to the player.[pointer to images.dat, starting at ID#561 as 0]
     * This property is only available from unit index 130 to num_lines
     */
    std::vector<uint8_t>* select_circle_image_size() const { return m_select_circle_image_size; }

    /**
     * The vertical position of the in-game selection circle and the Health/Shield/Energy bar. The higher the number, the more downwards from the main sprite will they be positioned. Around 127 the display "loops back" and appears actually ABOVE the main sprite. 255 will put it back in its original position.
     * This property is only available from unit index 130 to num_lines
     */
    std::vector<uint8_t>* select_circle_vertical_pos() const { return m_select_circle_vertical_pos; }
    sprites_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // SPRITES_DAT_H_
