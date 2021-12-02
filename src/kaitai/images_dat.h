#ifndef IMAGES_DAT_H_
#define IMAGES_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class images_dat_t : public kaitai::kstruct {

public:

    images_dat_t(uint16_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, images_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~images_dat_t();

private:
    std::vector<uint32_t>* m_grp_file;
    std::vector<uint8_t>* m_gfx_turns;
    std::vector<uint8_t>* m_clickable;
    std::vector<uint8_t>* m_use_full_iscript;
    std::vector<uint8_t>* m_draw_if_cloaked;
    std::vector<uint8_t>* m_draw_function;
    std::vector<uint8_t>* m_remapping;
    std::vector<uint32_t>* m_iscript_id;
    std::vector<uint32_t>* m_shield_overlay;
    std::vector<uint32_t>* m_attack_overlay;
    std::vector<uint32_t>* m_damage_overlay;
    std::vector<uint32_t>* m_special_overlay;
    std::vector<uint32_t>* m_landing_dust_overlay;
    std::vector<uint32_t>* m_lift_off_dust_overlay;
    uint16_t m_num_lines;
    images_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * Indicates the GRP graphics used by the current images.dat entry. If the value exceeds the number of lines in images.tbl, SC won't load. [pointer to images.tbl, -1 based]
     */
    std::vector<uint32_t>* grp_file() const { return m_grp_file; }

    /**
     * Determines if the game engine dynamically adds up to 16 frames and/or mirror them during animations, depending on what direction the sprite is facing. Unchecked, makes the sprite follow its Iscript animation with exactly the frame numbers contained in it.
     */
    std::vector<uint8_t>* gfx_turns() const { return m_gfx_turns; }

    /**
     * Determines if the graphics can be selected using the mouse cursor. Also determines the presence (or lack of) the cursor selection graphics. DOES NOT make the unit not at all selectable - it is still possible using the selection box.
     */
    std::vector<uint8_t>* clickable() const { return m_clickable; }

    /**
     * Allows running for Iscript animations other than the Initial and Death animations. Unchecked, prevents the sprite movement, attack, spellcasting etc. If the Movement Control for the corresponding flingy.dat entry is set to "Flingy.dat Control", the sprite movement WILL take place, but without any animation.
     */
    std::vector<uint8_t>* use_full_iscript() const { return m_use_full_iscript; }

    /**
     * Makes the image appear/disappear when cloacked.
     */
    std::vector<uint8_t>* draw_if_cloaked() const { return m_draw_if_cloaked; }

    /**
     * The drawing function used for the image. This property has rather various effects and not all options works with all entries so expect crashes. It can produce very interesting effects though, especially spell-related.
     */
    std::vector<uint8_t>* draw_function() const { return m_draw_function; }

    /**
     * An additional remapping "palette" that is to be used. Each tileset has its own files responsible for remapping. Used only if the Draw property is set to "9-Use Remapping". Values 8 and 9 produce a weird effect and most probably are a result of an error in Starcraft.
     */
    std::vector<uint8_t>* remapping() const { return m_remapping; }

    /**
     * Indicates the animation ID in the Iscript.bin file used to manage the animation of the current entry's GRP graphics. [pointer to Iscript.bin]
     */
    std::vector<uint32_t>* iscript_id() const { return m_iscript_id; }

    /**
     * Overlay used to place the Images.dat entry #424 ("Shield Overlay"), if the unit has shields and is hit. [pointer to images.tbl]
     */
    std::vector<uint32_t>* shield_overlay() const { return m_shield_overlay; }

    /**
     * This one usually controls a part of the attack animation. Except for the Bunker (which is hardcoded), the use of this property is not specific, but removing it will hang the game if unit's Iscript animation calls for the overlay with the opcodes: 0xD(imgoluselo), 0xE(imguluselo) or 0x15(sproluselo).[pointer to a LOG\LOL\LOX\LOA file in images.tbl]
     */
    std::vector<uint32_t>* attack_overlay() const { return m_attack_overlay; }

    /**
     * The "Flames/Bleeding" overlay control, dependent on the current HP value. If the number of frames of the used GRP file is higher than the number of frames of the overlay, the game will crash.[pointer to a LOF file in images.tbl]
     */
    std::vector<uint32_t>* damage_overlay() const { return m_damage_overlay; }

    /**
     * This one is used for various purposes: for "Resource Miners", it controls where they "hold" the resources;for the gas-containers, it controls the placement of the smoke graphics (iscript connection via the "creategasoverlays" (0x38) opcode); for the base-turret units, it controls the placement of the turret (also "imgoluselo" connection); for the Battlecruiser, it is the location of the Yamato Gun graphics.[pointer to a LOS\LOL\LOO\LOA\LOB file in images.tbl]
     */
    std::vector<uint32_t>* special_overlay() const { return m_special_overlay; }

    /**
     * Complementary to "Lift-off Dust", this one controls the placement of the landing dust. Some units (Dropship,Science Vessel) originally had this one too, but the idea was abandoned.Also used for the "2 in 1 Egg" zerg units, to determine the location where to put the 2 spawned units.[pointer to a LOB\LOU file in images.tbl]
     */
    std::vector<uint32_t>* landing_dust_overlay() const { return m_landing_dust_overlay; }

    /**
     * Complementary to "Landing Dust", this one controls the placement of the lifting-off dust. Some units (Dropship, Science Vessel) originally had this too, but the idea was abandoned. [pointer to a LOD file in images.tbl]
     */
    std::vector<uint32_t>* lift_off_dust_overlay() const { return m_lift_off_dust_overlay; }
    uint16_t num_lines() const { return m_num_lines; }
    images_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // IMAGES_DAT_H_
