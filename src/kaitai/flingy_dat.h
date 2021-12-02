#ifndef FLINGY_DAT_H_
#define FLINGY_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class flingy_dat_t : public kaitai::kstruct {

public:

    flingy_dat_t(uint8_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, flingy_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~flingy_dat_t();

private:
    std::vector<uint16_t>* m_sprite;
    std::vector<uint32_t>* m_speed;
    std::vector<uint16_t>* m_acceleration;
    std::vector<uint32_t>* m_halt_distance;
    std::vector<uint8_t>* m_turn_radius;
    std::vector<uint8_t>* m_unused;
    std::vector<uint8_t>* m_movement_control;
    uint8_t m_num_lines;
    flingy_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * The sprites.dat entry corresponding to the flingy.dat entry. [pointer to sprites.dat]
     */
    std::vector<uint16_t>* sprite() const { return m_sprite; }

    /**
     * Maximum speed at which the sprite will move. Measured in pixels-per-frame, but written as "Speed*(320/3)" (rounded up, it's weird, but that's how it works). Works ONLY if "Move Control" is set to "Flingy.dat Control".
     */
    std::vector<uint32_t>* speed() const { return m_speed; }

    /**
     * How fast the sprite speeds up or slows down. Added to or subtracted from current speed until it reaches the Top Speed or 0. Measured in pixels-per-frame.  Works ONLY if "Move Control" is set to "Flingy.dat Control".
     */
    std::vector<uint16_t>* acceleration() const { return m_acceleration; }

    /**
     * Distance from its destination at which the sprite will begin to deccelerate from its Top Speed to a complete halt. Measured in pixels*256.
     */
    std::vector<uint32_t>* halt_distance() const { return m_halt_distance; }

    /**
     * The distance the sprite requires to "wipe around" to turn to another direction. Works ONLY if "Move Control" is set to "Flingy.dat Control".
     */
    std::vector<uint8_t>* turn_radius() const { return m_turn_radius; }

    /**
     * Unused.
     */
    std::vector<uint8_t>* unused() const { return m_unused; }

    /**
     * Indicates the mechanism that is used to control the movement of the flingy.dat entry. "Flingy.dat Control" makes use of the Acceleration, Speed, Turn Style and Turn Radius properties, i.e. the values in this editor will be used. "Iscript.bin Control" ignores these properties and follows only the Iscript opcode sequence. "Partially Mobile/Weapon" is used for various weapons sprites, not completely understood.
     */
    std::vector<uint8_t>* movement_control() const { return m_movement_control; }
    uint8_t num_lines() const { return m_num_lines; }
    flingy_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // FLINGY_DAT_H_
