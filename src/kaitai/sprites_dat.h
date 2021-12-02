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

    sprites_dat_t(uint16_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, sprites_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~sprites_dat_t();

private:
    std::vector<uint16_t>* m_image_file;
    std::vector<uint8_t>* m_heath_bar;
    bool n_heath_bar;

public:
    bool _is_null_heath_bar() { heath_bar(); return n_heath_bar; };

private:
    std::vector<uint8_t>* m_unknown2;
    bool n_unknown2;

public:
    bool _is_null_unknown2() { unknown2(); return n_unknown2; };

private:
    std::vector<uint8_t>* m_is_visible;
    bool n_is_visible;

public:
    bool _is_null_is_visible() { is_visible(); return n_is_visible; };

private:
    std::vector<uint8_t>* m_select_circle_image_size;
    bool n_select_circle_image_size;

public:
    bool _is_null_select_circle_image_size() { select_circle_image_size(); return n_select_circle_image_size; };

private:
    std::vector<uint8_t>* m_select_circle_vertical_pos;
    bool n_select_circle_vertical_pos;

public:
    bool _is_null_select_circle_vertical_pos() { select_circle_vertical_pos(); return n_select_circle_vertical_pos; };

private:
    uint16_t m_num_lines;
    sprites_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * The images.dat entry corresponding to the sprites.dat entry [pointer to images.dat]
     */
    std::vector<uint16_t>* image_file() const { return m_image_file; }

    /**
     * The length of the Hit Points/Shields/Energy bar below the sprite, in pixels. The way the actual number of "boxes" is calculated is the following: substract 1 from the value, divide the result by 3 and round it down. Even though a sprite may actually USE less than 6 boxes, 6 boxes is the minimal amount that will be SHOWN in-game (just that some will not be functional). Values below 6 will all result in 1 box being USED.
     * This property is only available from unit index 130 to 516
     */
    std::vector<uint8_t>* heath_bar() const { return m_heath_bar; }

    /**
     * tbd
     */
    std::vector<uint8_t>* unknown2() const { return m_unknown2; }

    /**
     * Sprite will start as visible. Unchecked, used to hide the "White Circle", the Zerg Beacon used by Subterranean Spines, and few other things.
     * This property is only available from unit index 130 to 516
     */
    std::vector<uint8_t>* is_visible() const { return m_is_visible; }

    /**
     * The size of the in-game selection circle. The different sizes are actually different images.dat entries, so in order to use custom ones you need to replace them. The "Dashed" selection circles are used to mark allied units in multiplayer games, but if used on the players own units they will not disappear after deselecting the unit, and also they will NOT be removed on its death, still providing limited vision to the player.[pointer to images.dat, starting at ID#561 as 0]
     * This property is only available from unit index 130 to 516
     */
    std::vector<uint8_t>* select_circle_image_size() const { return m_select_circle_image_size; }

    /**
     * The vertical position of the in-game selection circle and the Health/Shield/Energy bar. The higher the number, the more downwards from the main sprite will they be positioned. Around 127 the display "loops back" and appears actually ABOVE the main sprite. 255 will put it back in its original position.
     * This property is only available from unit index 130 to 516
     */
    std::vector<uint8_t>* select_circle_vertical_pos() const { return m_select_circle_vertical_pos; }
    uint16_t num_lines() const { return m_num_lines; }
    sprites_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // SPRITES_DAT_H_
