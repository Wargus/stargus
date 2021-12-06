#ifndef WEAPONS_DAT_H_
#define WEAPONS_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class weapons_dat_t : public kaitai::kstruct {

public:

    enum attack_type_enum_t {
        ATTACK_TYPE_ENUM_AIR_ONLY = 1,
        ATTACK_TYPE_ENUM_GROUND_ONLY = 2,
        ATTACK_TYPE_ENUM_GROUND_AND_AIR = 3,
        ATTACK_TYPE_ENUM_UNITS_ONLY = 4,
        ATTACK_TYPE_ENUM_GROUND_UNITS_ONLY = 18
    };

    enum weapon_type_enum_t {
        WEAPON_TYPE_ENUM_NDEPENDENT = 0,
        WEAPON_TYPE_ENUM_EXPLOSIVE = 1,
        WEAPON_TYPE_ENUM_CONCUSSIVE = 2,
        WEAPON_TYPE_ENUM_NORMAL = 3,
        WEAPON_TYPE_ENUM_IGNORE_AMOR = 4
    };

    weapons_dat_t(uint8_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, weapons_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~weapons_dat_t();

private:
    std::vector<uint16_t>* m_label;
    std::vector<uint32_t>* m_graphics;
    std::vector<uint8_t>* m_explosion;
    std::vector<attack_type_enum_t>* m_target_flags;
    std::vector<uint32_t>* m_minimum_range;
    std::vector<uint32_t>* m_maximum_range;
    std::vector<uint8_t>* m_damage_upgrade;
    std::vector<weapon_type_enum_t>* m_weapon_type;
    std::vector<uint8_t>* m_weapon_behaviour;
    std::vector<uint8_t>* m_remove_after;
    std::vector<uint8_t>* m_explosive_type;
    std::vector<uint16_t>* m_inner_splash_range;
    std::vector<uint16_t>* m_medium_splash_range;
    std::vector<uint16_t>* m_outer_splash_range;
    std::vector<uint16_t>* m_damage_amount;
    std::vector<uint16_t>* m_damage_bonus;
    std::vector<uint8_t>* m_weapon_cooldown;
    std::vector<uint8_t>* m_damage_factor;
    std::vector<uint8_t>* m_attack_angle;
    std::vector<uint8_t>* m_launch_spin;
    std::vector<uint8_t>* m_x_offset;
    std::vector<uint8_t>* m_y_offset;
    std::vector<uint16_t>* m_error_message;
    std::vector<uint16_t>* m_icon;
    uint8_t m_num_lines;
    weapons_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * The name of the weapon, displayed when you highlight its icon in the control bar. [pointer to stat_txt.tbl]
     */
    std::vector<uint16_t>* label() const { return m_label; }

    /**
     * The main graphics that the weapon uses. 0-Scourge = No graphics.[pointer to flingy.dat]
     */
    std::vector<uint32_t>* graphics() const { return m_graphics; }

    /**
     * Effect the weapon has on the area around the target after hitting its target. Used to determine different type of spell effects and splash damage.
     * TODO: create enum
     * 0 = Nothing
     * 1 = Lockdown
     * 2 = Irradiate
     * 3 = Spider Mines (Chase Unit)
     * 4 = Normal
     * 5 = No Damage
     * 6 = No Damage
     * 7 = EMP Shockwave
     * 8 = Yamato Gun
     * 9 = No Damage
     * 10 = No Damage
     * 11 = No Damage
     * 12 = No Damage
     * 13 = Broodling
     * 14 = Dark Swarm
     * 15 = Plague
     * 16 = Consume
     * 17 = Ensnare
     * 18 = Parasite
     * 19 = Psi Storm
     * 20 = Normal
     * 21 = Normal
     * 22 = Stasis
     * 23 = 1/4 Damage?
     * 24 = Normal
     * 25 = 1/3 Damage?
     */
    std::vector<uint8_t>* explosion() const { return m_explosion; }
    std::vector<attack_type_enum_t>* target_flags() const { return m_target_flags; }

    /**
     * Minimal range from which the weapon can be used.
     * TODO: StaDat shows here value/16 but no sure why.
     */
    std::vector<uint32_t>* minimum_range() const { return m_minimum_range; }

    /**
     * Maximal range from which the weapon can be used.
     * TODO: StaDat shows here value/16 but no sure why.
     */
    std::vector<uint32_t>* maximum_range() const { return m_maximum_range; }

    /**
     * The upgrade that will increase the damage dealt by the weapon by the "Bonus" value.
     * Pointer to [upgrades.dat]
     */
    std::vector<uint8_t>* damage_upgrade() const { return m_damage_upgrade; }

    /**
     * The type of damage the weapon does. Normal, Explosive and Concussive do different amount of damage to units of different Size (Small, Medium or Large): Normal does equal damage to Small, Medium and Large. Explosive does 50% to Small and 75% to Medium. Concussive does 50% to Medium and 25% to Large.  Independent deals 1 point of damage every second attack, regardless of target's armor.
     */
    std::vector<weapon_type_enum_t>* weapon_type() const { return m_weapon_type; }

    /**
     * Determines how the weapon sprite will "behave" when it attacks the target. Weapon behaviours that "Follow" will track the target as it moves, those that "Don't Follow" will strike the place where the target was at the moment of attack.
     * TODO: take enum values from StarDat
     */
    std::vector<uint8_t>* weapon_behaviour() const { return m_weapon_behaviour; }

    /**
     * Time until the weapon is removed if it does not hit a target. 1 game second equals: on Fastest-24, on Faster-21, on Fast-18, on Normal-15, on Slow-12, on Slower-9 and on Slowest-6.
     */
    std::vector<uint8_t>* remove_after() const { return m_remove_after; }

    /**
     * Effect the weapon has on the area around the target after hitting its target. Used to determine different type of spell effects and splash damage.
     */
    std::vector<uint8_t>* explosive_type() const { return m_explosive_type; }

    /**
     * Distance from the target at which the weapon will deal 100% of its base damage. Works ONLY if the "Explosion" is set to "Nuclear Missile", "Splash (Radial)", "Splash (Enemy)" or "Splash (Air)".
     */
    std::vector<uint16_t>* inner_splash_range() const { return m_inner_splash_range; }

    /**
     * Distance from the target at which the weapon will deal 50% of its base damage. Works ONLY if the "Explosion" is set to "Nuclear Missile", "Splash (Radial)", "Splash (Enemy)" or "Splash (Air)".
     */
    std::vector<uint16_t>* medium_splash_range() const { return m_medium_splash_range; }

    /**
     * Distance from the target at which the weapon will deal 25% of its base damage. Works ONLY if the "Explosion" is set to "Nuclear Missile", "Splash (Radial)", "Splash (Enemy)" or "Splash (Air)".
     */
    std::vector<uint16_t>* outer_splash_range() const { return m_outer_splash_range; }

    /**
     * The basic amount of damage the weapon will inflict when it hits.
     */
    std::vector<uint16_t>* damage_amount() const { return m_damage_amount; }

    /**
     * The amount of damage added to the basic value for each level of the upgrade.
     */
    std::vector<uint16_t>* damage_bonus() const { return m_damage_bonus; }

    /**
     * "Reload time" - time delay between two attacks. Depends on the game speed used. 1 game second equals: on Fastest-24, on Faster-21, on Fast-18, on Normal-15, on Slow-12, on Slower-9 and on Slowest-6. Value of 0 will crash the game.
     */
    std::vector<uint8_t>* weapon_cooldown() const { return m_weapon_cooldown; }

    /**
     * Usually, multiple this value by the Damage Amount to get the total damage that is DISPLAYED for the weapon. To a degree also the number of weapons used per attack, but anything other than 2 will result in 1 weapon being used. (e.g. Goliath, Scout and Valkyrie use 2 missiles per attack).
     */
    std::vector<uint8_t>* damage_factor() const { return m_damage_factor; }

    /**
     * Angle within which the weapon can be fired without waiting for the unit's graphics to turn. 128 = 180 degrees.
     */
    std::vector<uint8_t>* attack_angle() const { return m_attack_angle; }

    /**
     * Angle by which the weapon's sprite will spin after it is spawned. 128 = 180 degrees.
     */
    std::vector<uint8_t>* launch_spin() const { return m_launch_spin; }

    /**
     * Distance (in pixels) from the front of the attacking unit (depending on which direction it is facing), at which the weapon's sprite will be spawned.
     */
    std::vector<uint8_t>* x_offset() const { return m_x_offset; }

    /**
     * Distance (in pixels) from the top of the attacking unit, at which the weapon's sprite will be spawned.
     */
    std::vector<uint8_t>* y_offset() const { return m_y_offset; }

    /**
     * The line displayed when the weapon is to acquire an invalid target (e.g. attacking a Mutalisk with a ground-only weapon, like Flamethrower) [pointer to stat_txt.tbl]
     */
    std::vector<uint16_t>* error_message() const { return m_error_message; }

    /**
     * The icon used for the weapon. [pointer to a frame in unit\cmdbtns\cmdicons.grp]
     */
    std::vector<uint16_t>* icon() const { return m_icon; }
    uint8_t num_lines() const { return m_num_lines; }
    weapons_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // WEAPONS_DAT_H_
