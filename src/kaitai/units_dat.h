#ifndef UNITS_DAT_H_
#define UNITS_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class units_dat_t : public kaitai::kstruct {

public:
    class staredit_group_flags_type_t;
    class hit_points_type_t;
    class addon_position_type_t;
    class special_ability_flags_type_t;
    class staredit_placement_box_type_t;
    class unit_dimension_type_t;
    class staredit_availability_flags_type_t;

    enum unit_size_enum_t {
        UNIT_SIZE_ENUM_INDENDENT = 0,
        UNIT_SIZE_ENUM_SMALL = 1,
        UNIT_SIZE_ENUM_MEDIUM = 2,
        UNIT_SIZE_ENUM_LARGE = 3
    };

    enum right_click_action_enum_t {
        RIGHT_CLICK_ACTION_ENUM_NO_COMMANDS_AUO_ATTACK = 0,
        RIGHT_CLICK_ACTION_ENUM_NORMAL_MOVEMENT_NORMAL_ATTACK = 1,
        RIGHT_CLICK_ACTION_ENUM_NORMAL_MOVEMENT_NO_ATTACK = 2,
        RIGHT_CLICK_ACTION_ENUM_NO_MOVEMENT_NORMAL_ATTACK = 3,
        RIGHT_CLICK_ACTION_ENUM_HARVEST = 4,
        RIGHT_CLICK_ACTION_ENUM_HARVEST_REPAIR = 5,
        RIGHT_CLICK_ACTION_ENUM_NOTHING_WITH_INDICATOR = 6
    };

    units_dat_t(bool p_has_broodwar_flag, bool p_has_max_air_hits, bool p_has_max_ground_hits, kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, units_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~units_dat_t();

    /**
     * zerg: Unit is from race "Zerg"
     * terran: Unit is from race "Terran"
     * protoss: Unit is from race "Protoss"
     * men: Unit is a "Men"-type unit for triggers.
     * building: Unit is a "Building"-type unit for triggers.
     * factory: Unit is a "Factory"-type unit for triggers.
     * independent: Unit is treated as an Independent unit (abandoned unit type).
     * neutral: Unit is treated as a Neutral unit.
     *   
     */

    class staredit_group_flags_type_t : public kaitai::kstruct {

    public:

        staredit_group_flags_type_t(kaitai::kstream* p__io, units_dat_t* p__parent = 0, units_dat_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~staredit_group_flags_type_t();

    private:
        bool m_zerg;
        bool m_terran;
        bool m_protoss;
        bool m_men;
        bool m_building;
        bool m_factory;
        bool m_independent;
        bool m_neutral;
        units_dat_t* m__root;
        units_dat_t* m__parent;

    public:
        bool zerg() const { return m_zerg; }
        bool terran() const { return m_terran; }
        bool protoss() const { return m_protoss; }
        bool men() const { return m_men; }
        bool building() const { return m_building; }
        bool factory() const { return m_factory; }
        bool independent() const { return m_independent; }
        bool neutral() const { return m_neutral; }
        units_dat_t* _root() const { return m__root; }
        units_dat_t* _parent() const { return m__parent; }
    };

    class hit_points_type_t : public kaitai::kstruct {

    public:

        hit_points_type_t(kaitai::kstream* p__io, units_dat_t* p__parent = 0, units_dat_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~hit_points_type_t();

    private:
        uint16_t m_hitpoints;
        uint16_t m_unused;
        units_dat_t* m__root;
        units_dat_t* m__parent;

    public:
        uint16_t hitpoints() const { return m_hitpoints; }
        uint16_t unused() const { return m_unused; }
        units_dat_t* _root() const { return m__root; }
        units_dat_t* _parent() const { return m__parent; }
    };

    class addon_position_type_t : public kaitai::kstruct {

    public:

        addon_position_type_t(kaitai::kstream* p__io, units_dat_t* p__parent = 0, units_dat_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~addon_position_type_t();

    private:
        uint16_t m_horizontal;
        uint16_t m_vertical;
        units_dat_t* m__root;
        units_dat_t* m__parent;

    public:
        uint16_t horizontal() const { return m_horizontal; }
        uint16_t vertical() const { return m_vertical; }
        units_dat_t* _root() const { return m__root; }
        units_dat_t* _parent() const { return m__parent; }
    };

    /**
     * building: Unit is considered as a building for targeting purposes, and affects Addons-related properties. Also allows for other units to be built/trained 'inside' the unit and makes the unit placement dependent on the "Placement Box" property instead of the "Unit Dimensions".
     * addon: Makes the building placeable in a special way, dependent on the main building. If unchecked, the building will still use the standard way of placing the addon, but after lift-off, it will be inaccessible.
     * flyer: If unchecked, the unit is targeted by Ground weapons. If checked, unit can be targeted by Air weapons. It also makes the unit "fly" in the way that it chooses the shortest path to its destination, moving over terrain and other units.
     * resourceminer: Unit can gather/return resources. Does NOT affect building construction abilities (except a tiny Drone glitch if you cancel a building morph). Requires a .LOO file pointed from the "Overlay 3" property in Images.dat to work. Vespene Gas harvesting seems good for all units, but Minerals may cause crashes, depending on the unit you use (e.g. Marine is OK, but the Firebat will crash)
     * subunit: Makes the unit a "sub-unit", i.e. allows it to be a part of another unit (like the tank turret to the tank body) through the Subunit property (see Graphics tab). A non-subunit-type unit used as a subunit will crash the game. To have a sub-unit properly placed on a unit, you also require altering the images.dat properties of the base sprite as well as certain other settings. Expect crashes more than often while working with this property.
     * flyingbuilding: Allows/Disallows the unit to be in the "In Transit" (or "Flying") state both in the game and in StarEdit, but it will crash if the unit does not have a Lift-off and Landing animations (in Iscript.bin). Does not affect buttons available for the unit.
     * hero: Unit has all its upgrades researched from the start and receives a white wireframe box (instead of the standard blue one). If a unit is also a spellcaster, it will have 250 energy points, regardless if there is an energy upgrade for it or not. 
     * regenerate: Unit will slowly regain Hit Points, until its full HP capacity.
     * animatedidle: 
     * cloakable: Allows/Disallows the unit to use the Cloak technology. It does NOT give/remove the "Cloak" button but allows the unit to display the "Group (Cloakers)" button set when selected in a group.
     * twounitsinoneegg: 2 units will come out of one Zerg Egg instead of just one. The cost for morphing will NOT be doubled, but the amount of the used supplies will equal 2 times the normal amount. To accomplish the full effect you will also have to add a "Construction" graphics and set a "Landing Dust" overlay to it.
     * singleentity: Unit cannot be selected in a group, but only as a single unit. Unit cannot be selected by dragging a selection box, by a SHIFT-Click nor a double-click.
     * resourcedepot: Makes a building (and ONLY a building) a place workers can return resources to. Also makes it impossible to place/land the building next to a unit with the "Resource Container" property.
     * resourcecontainter: Unit does not generate an error message if targeted for Gathering by a worker. Allows/Disallows to set unit's resources capacity in StarEdit, but does not make a unit other than original resource actually store resources in-game. Unchecked, makes the original resources capacity equal to 0, although workers will still try to harvest it. Prevents "Resource Depots" from being located next to it.
     * robotic: Unit is treated as a robotic-type target for weapons and spells (e.g. it cannot be targeted with Spawn Broodlings)
     * detector: Unit can detect cloaked enemy units and receives the "Detector" title under its name.
     * organic: Unit is treated as an organic-type target for weapons and spells (e.g. Maelstrom).
     * requirescreep: Building MUST be built on creep. It will also get a creep outline around it.
     * unused: 
     * requirespsi: Unit must be built within a PSI field, like that produced by pylons. If it is not within a PSI field, it will become "Disabled" and not function. Can be given to any unit. You can also disable it on Protoss buildings so they can be built anywhere. 
     * burrowable: Allows/Disallows the unit to use the Burrow technology. It does NOT give/remove the "Burrow" button.
     * spellcaster: Unit receives a mana bar and will slowly regain mana points through time. Combined with the Permanent Cloak property, will prevent unit from regaining mana.
     * permanentcloak: Unit is constantly cloaked. If the unit is also a Spellcaster, giving this property will make it lose mana until 0.
     * pickupitem: Related to powerups. Not completely understood.
     * ignoresupplycheck: Even if you don't have the supply available to build the unit, the engine will still build it and add that to your supply.
     * usemediumoverlays: Unit will use medium spell overlay graphics.
     * uselargeoverlays: Unit will use large spell overlay graphics.
     * battlereactions: Unit will show battle reactions,i.e. if it sees an enemy it will move to it and attack, if it is attacked by an unreachable enemy (e.g. an Air unit and it doesn't have an Air weapon) it will run away. Works ONLY if the unit's Idle AI Orders are set to Guard.
     * fullautoattack: Unit will attack any enemy that enters its firing range. If unchecked, unit will attack the enemy ONLY if it is facing its direction, e.g. because it has an animated idle state. 
     * invincible: Unit cannot be a target of any sort of weapons or spells. It also hides the unit's Hit Points value.
     * mechanical: Unit is treated as a mechanical-type target for weapons and spells (e.g. Lockdown). It can also be repaired by SCVs.
     * producesunits: 
     *   
     */

    class special_ability_flags_type_t : public kaitai::kstruct {

    public:

        special_ability_flags_type_t(kaitai::kstream* p__io, units_dat_t* p__parent = 0, units_dat_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~special_ability_flags_type_t();

    private:
        bool m_building;
        bool m_addon;
        bool m_flyer;
        bool m_resourceminer;
        bool m_subunit;
        bool m_flyingbuilding;
        bool m_hero;
        bool m_regenerate;
        bool m_animatedidle;
        bool m_cloakable;
        bool m_twounitsinoneegg;
        bool m_singleentity;
        bool m_resourcedepot;
        bool m_resourcecontainter;
        bool m_robotic;
        bool m_detector;
        bool m_organic;
        bool m_requirescreep;
        bool m_unused;
        bool m_requirespsi;
        bool m_burrowable;
        bool m_spellcaster;
        bool m_permanentcloak;
        bool m_pickupitem;
        bool m_ignoresupplycheck;
        bool m_usemediumoverlays;
        bool m_uselargeoverlays;
        bool m_battlereactions;
        bool m_fullautoattack;
        bool m_invincible;
        bool m_mechanical;
        bool m_producesunits;
        units_dat_t* m__root;
        units_dat_t* m__parent;

    public:
        bool building() const { return m_building; }
        bool addon() const { return m_addon; }
        bool flyer() const { return m_flyer; }
        bool resourceminer() const { return m_resourceminer; }
        bool subunit() const { return m_subunit; }
        bool flyingbuilding() const { return m_flyingbuilding; }
        bool hero() const { return m_hero; }
        bool regenerate() const { return m_regenerate; }
        bool animatedidle() const { return m_animatedidle; }
        bool cloakable() const { return m_cloakable; }
        bool twounitsinoneegg() const { return m_twounitsinoneegg; }
        bool singleentity() const { return m_singleentity; }
        bool resourcedepot() const { return m_resourcedepot; }
        bool resourcecontainter() const { return m_resourcecontainter; }
        bool robotic() const { return m_robotic; }
        bool detector() const { return m_detector; }
        bool organic() const { return m_organic; }
        bool requirescreep() const { return m_requirescreep; }
        bool unused() const { return m_unused; }
        bool requirespsi() const { return m_requirespsi; }
        bool burrowable() const { return m_burrowable; }
        bool spellcaster() const { return m_spellcaster; }
        bool permanentcloak() const { return m_permanentcloak; }
        bool pickupitem() const { return m_pickupitem; }
        bool ignoresupplycheck() const { return m_ignoresupplycheck; }
        bool usemediumoverlays() const { return m_usemediumoverlays; }
        bool uselargeoverlays() const { return m_uselargeoverlays; }
        bool battlereactions() const { return m_battlereactions; }
        bool fullautoattack() const { return m_fullautoattack; }
        bool invincible() const { return m_invincible; }
        bool mechanical() const { return m_mechanical; }
        bool producesunits() const { return m_producesunits; }
        units_dat_t* _root() const { return m__root; }
        units_dat_t* _parent() const { return m__parent; }
    };

    class staredit_placement_box_type_t : public kaitai::kstruct {

    public:

        staredit_placement_box_type_t(kaitai::kstream* p__io, units_dat_t* p__parent = 0, units_dat_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~staredit_placement_box_type_t();

    private:
        uint16_t m_width;
        uint16_t m_height;
        units_dat_t* m__root;
        units_dat_t* m__parent;

    public:
        uint16_t width() const { return m_width; }
        uint16_t height() const { return m_height; }
        units_dat_t* _root() const { return m__root; }
        units_dat_t* _parent() const { return m__parent; }
    };

    class unit_dimension_type_t : public kaitai::kstruct {

    public:

        unit_dimension_type_t(kaitai::kstream* p__io, units_dat_t* p__parent = 0, units_dat_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~unit_dimension_type_t();

    private:
        uint16_t m_left;
        uint16_t m_up;
        uint16_t m_right;
        uint16_t m_down;
        units_dat_t* m__root;
        units_dat_t* m__parent;

    public:
        uint16_t left() const { return m_left; }
        uint16_t up() const { return m_up; }
        uint16_t right() const { return m_right; }
        uint16_t down() const { return m_down; }
        units_dat_t* _root() const { return m__root; }
        units_dat_t* _parent() const { return m__parent; }
    };

    /**
     * non_neutral: Unit belongs to a 1-8 Player, takes its corresponding color and appears in the player's corresponding menu in the unit listing on the left. If unchecked, the unit belongs to the 12th Player (neutral), takes the dark aqua color and appears under the "Neutral" menu in the unit listing.
     * unit_listing: Unit is availabe in the unit listing on the left and in the Brush Palette.
     * mission_briefing: Unit's portrait is available in Mission Briefing.
     * player_settings: Unit is available in the Player Settings.
     * all_races: Unit is available for all races in the unit list in StarEdit.
     * set_doodad_state: Unit is available for the "Set Doodad State" trigger.
     * non_location_triggers: Unit appears in the unit selection box when using Non-locational triggers (Remove, Kill etc.)
     * unit_hero_settings: Unit is available in Unit&Hero Settings.
     * location_triggers: Unit appears in the unit selection box when using locational triggers (Remove at, Kill at etc.). Even if unchecked, the unit WILL appear for selection when using the "Create at" trigger action.
     * brood_war_only: Unit is available only if BroodWar Expansion is installed.
     */

    class staredit_availability_flags_type_t : public kaitai::kstruct {

    public:

        staredit_availability_flags_type_t(kaitai::kstream* p__io, units_dat_t* p__parent = 0, units_dat_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~staredit_availability_flags_type_t();

    private:
        bool m_non_neutral;
        bool m_unit_listing;
        bool m_mission_briefing;
        bool m_player_settings;
        bool m_all_races;
        bool m_set_doodad_state;
        bool m_non_location_triggers;
        bool m_unit_hero_settings;
        bool m_location_triggers;
        bool m_brood_war_only;
        uint64_t m__unnamed10;
        units_dat_t* m__root;
        units_dat_t* m__parent;

    public:
        bool non_neutral() const { return m_non_neutral; }
        bool unit_listing() const { return m_unit_listing; }
        bool mission_briefing() const { return m_mission_briefing; }
        bool player_settings() const { return m_player_settings; }
        bool all_races() const { return m_all_races; }
        bool set_doodad_state() const { return m_set_doodad_state; }
        bool non_location_triggers() const { return m_non_location_triggers; }
        bool unit_hero_settings() const { return m_unit_hero_settings; }
        bool location_triggers() const { return m_location_triggers; }
        bool brood_war_only() const { return m_brood_war_only; }
        uint64_t _unnamed10() const { return m__unnamed10; }
        units_dat_t* _root() const { return m__root; }
        units_dat_t* _parent() const { return m__parent; }
    };

private:
    std::vector<uint8_t>* m_graphics;
    std::vector<uint16_t>* m_subunit1;
    std::vector<uint16_t>* m_subunit2;
    std::vector<uint16_t>* m_infestation;
    std::vector<uint32_t>* m_construction_animation;
    std::vector<uint8_t>* m_unit_direction;
    std::vector<uint8_t>* m_shield_enable;
    std::vector<uint16_t>* m_shield_amount;
    std::vector<hit_points_type_t*>* m_hit_points;
    std::vector<uint8_t>* m_elevation_level;
    std::vector<uint8_t>* m_unknown;
    std::vector<uint8_t>* m_rank;
    std::vector<uint8_t>* m_ai_computer_idle;
    std::vector<uint8_t>* m_ai_human_idle;
    std::vector<uint8_t>* m_ai_return_to_idle;
    std::vector<uint8_t>* m_ai_attack_unit;
    std::vector<uint8_t>* m_ai_attack_move;
    std::vector<uint8_t>* m_ground_weapon;
    std::vector<uint8_t>* m_max_ground_hits;
    bool n_max_ground_hits;

public:
    bool _is_null_max_ground_hits() { max_ground_hits(); return n_max_ground_hits; };

private:
    std::vector<uint8_t>* m_air_weapon;
    std::vector<uint8_t>* m_max_air_hits;
    bool n_max_air_hits;

public:
    bool _is_null_max_air_hits() { max_air_hits(); return n_max_air_hits; };

private:
    std::vector<uint8_t>* m_ai_internal;
    std::vector<special_ability_flags_type_t*>* m_special_ability_flags;
    std::vector<uint8_t>* m_target_acquisition_range;
    std::vector<uint8_t>* m_sight_range;
    std::vector<uint8_t>* m_armor_upgrade;
    std::vector<unit_size_enum_t>* m_unit_size;
    std::vector<uint8_t>* m_armor;
    std::vector<right_click_action_enum_t>* m_right_click_action;
    std::vector<uint16_t>* m_ready_sound;
    std::vector<uint16_t>* m_what_sound_start;
    std::vector<uint16_t>* m_what_sound_end;
    std::vector<uint16_t>* m_piss_sound_start;
    std::vector<uint16_t>* m_piss_sound_end;
    std::vector<uint16_t>* m_yes_sound_start;
    std::vector<uint16_t>* m_yes_sound_end;
    std::vector<staredit_placement_box_type_t*>* m_staredit_placement_box;
    std::vector<addon_position_type_t*>* m_addon_position;
    std::vector<unit_dimension_type_t*>* m_unit_dimension;
    std::vector<uint16_t>* m_portrait;
    std::vector<uint16_t>* m_mineral_cost;
    std::vector<uint16_t>* m_vespene_cost;
    std::vector<uint16_t>* m_build_time;
    std::vector<uint16_t>* m_requirements;
    std::vector<staredit_group_flags_type_t*>* m_staredit_group_flags;
    std::vector<uint8_t>* m_supply_provided;
    std::vector<uint8_t>* m_supply_required;
    std::vector<uint8_t>* m_space_required;
    std::vector<uint8_t>* m_space_provided;
    std::vector<uint16_t>* m_build_score;
    std::vector<uint16_t>* m_destroy_score;
    std::vector<uint16_t>* m_unit_map_string;
    std::vector<uint8_t>* m_broodwar_flag;
    bool n_broodwar_flag;

public:
    bool _is_null_broodwar_flag() { broodwar_flag(); return n_broodwar_flag; };

private:
    std::vector<staredit_availability_flags_type_t*>* m_staredit_availability_flags;
    bool m_has_broodwar_flag;
    bool m_has_max_air_hits;
    bool m_has_max_ground_hits;
    units_dat_t* m__root;
    kaitai::kstruct* m__parent;
    std::vector<std::string>* m__raw_special_ability_flags;
    std::vector<kaitai::kstream*>* m__io__raw_special_ability_flags;
    std::vector<std::string>* m__raw_staredit_group_flags;
    std::vector<kaitai::kstream*>* m__io__raw_staredit_group_flags;
    std::vector<std::string>* m__raw_staredit_availability_flags;
    std::vector<kaitai::kstream*>* m__io__raw_staredit_availability_flags;

public:

    /**
     * Unit's main graphics object. [pointer to flingy.dat]
     */
    std::vector<uint8_t>* graphics() const { return m_graphics; }

    /**
     * Main subunit to the unit. Various turrets mostly. [pointer to units.dat]
     */
    std::vector<uint16_t>* subunit1() const { return m_subunit1; }

    /**
     * Secondary subunit. Unused. [pointer to units.dat]
     */
    std::vector<uint16_t>* subunit2() const { return m_subunit2; }

    /**
     * Unit to transform into after Infestation. Exists only for units of ID 106-201 (buildings). [pointer to units.dat]
     */
    std::vector<uint16_t>* infestation() const { return m_infestation; }

    /**
     * Construction graphics of the unit (used mostly with buildings). 0-Scourge = No graphics. [pointer to images.dat]
     */
    std::vector<uint32_t>* construction_animation() const { return m_construction_animation; }

    /**
     * Direction unit will face after it is created. Values start at 0 (the unit will face the top of the screen) and go on clockwise through subsequent turning stages until 31 (unit will face a little left from the complete turn). Value of 32 means unit will face a random direction.
     */
    std::vector<uint8_t>* unit_direction() const { return m_unit_direction; }

    /**
     * Enables Shields for the unit. Works for any unit, not only Protoss. Terran and zerg buildings with shields do NOT acquire full shield capacity during construction.
     */
    std::vector<uint8_t>* shield_enable() const { return m_shield_enable; }

    /**
     * Amount of Shield Points the unit has. Shields are reduced before the unit's Hit Points are affected.
     */
    std::vector<uint16_t>* shield_amount() const { return m_shield_amount; }

    /**
     * Unit Hit Points (HP) or "life" amount.
     */
    std::vector<hit_points_type_t*>* hit_points() const { return m_hit_points; }

    /**
     * The elevation level at which the unit moves. It can be used to make units moves like flyers, but still be attacked by ground weapons and act as ground units to specific special abilities (like Recall). Higher values puts the unit higher over terrain and other units.
     */
    std::vector<uint8_t>* elevation_level() const { return m_elevation_level; }

    /**
     * TODO: this might be "movement_type" but meaning is unclear
     */
    std::vector<uint8_t>* unknown() const { return m_unknown; }

    /**
     * Controls ground units movement: units with lower Rank will stop and wait to allow units with higher Rank to continue movement. Has no effects on air units. Also the order this unit is displayed in its folder in StarEdit. Max of 255.
     * also known as 'sublabel'
     */
    std::vector<uint8_t>* rank() const { return m_rank; }

    /**
     * Order given to the unit if it is under computer control and does nothing. [pointer to orders.dat]      name 'Computer AI Idle'
     */
    std::vector<uint8_t>* ai_computer_idle() const { return m_ai_computer_idle; }

    /**
     * Order given to the unit if it is under a human player's control and does nothing. [pointer to orders.dat]
     */
    std::vector<uint8_t>* ai_human_idle() const { return m_ai_human_idle; }

    /**
     * Order executed after the unit has finished executing another order and returns to Idle state. [pointer to orders.dat]
     */
    std::vector<uint8_t>* ai_return_to_idle() const { return m_ai_return_to_idle; }

    /**
     * Order executed if the units is ordered to attack an enemy unit, also through the Right-Click action. [pointer to orders.dat]
     */
    std::vector<uint8_t>* ai_attack_unit() const { return m_ai_attack_unit; }

    /**
     * Order executed if the unit is ordered to Attack Ground. [pointer to orders.dat]
     */
    std::vector<uint8_t>* ai_attack_move() const { return m_ai_attack_move; }

    /**
     * Weapon used for attacking "ground" units - those with the "Flying Target" advanced flag unchecked. [pointer to weapons.dat]
     */
    std::vector<uint8_t>* ground_weapon() const { return m_ground_weapon; }

    /**
     * Max number of times unit hits its target per Ground attack. This value is for statistics purposes only. Changing it only affects the value displayed in StarEdit.
     * Only some variants of units.dat have this data block. If your version has this block activate the parameter.
     */
    std::vector<uint8_t>* max_ground_hits() const { return m_max_ground_hits; }

    /**
     * Weapon used for attacking "air" or "flying" units - those with the "Flying Target" advanced flag checked. [pointer to weapons.dat]
     */
    std::vector<uint8_t>* air_weapon() const { return m_air_weapon; }

    /**
     * Max number of times unit hits its target per Air attack. This value is for statistics purposes only. Changing it only affects the value displayed in StarEdit.
     * Only some variants of units.dat have this data block. If your version has this block activate the parameter.
     */
    std::vector<uint8_t>* max_air_hits() const { return m_max_air_hits; }

    /**
     * Some AI-related property. Not completely understood.
     */
    std::vector<uint8_t>* ai_internal() const { return m_ai_internal; }

    /**
     * Advanced flags. Check the type for detail specification.
     */
    std::vector<special_ability_flags_type_t*>* special_ability_flags() const { return m_special_ability_flags; }

    /**
     * Range at which the Carrier will launch Interceptors and Reaver Scarabs. Also determines the range at which melee units and Medics will pickup targets. Value of 0 makes the game use the Weapons.dat for range data. 1 range unit here equals 2 range units in weapons.dat.
     */
    std::vector<uint8_t>* target_acquisition_range() const { return m_target_acquisition_range; }

    /**
     * Range (in matrices) indicating how much Fog-Of-War will the unit clear up.
     */
    std::vector<uint8_t>* sight_range() const { return m_sight_range; }

    /**
     * Researching this upgrade will improve the unit's Armor by 1. [pointer to upgrades.dat]
     */
    std::vector<uint8_t>* armor_upgrade() const { return m_armor_upgrade; }

    /**
     * Used to calculate the "Explosive" and "Concussive" weapons damage: Explosive (50% to Small, 75% to Medium), Concussive (50% to Medium, 25% to Large). "Independent" - the unit will lose 1 HP every second attack it takes (by no matter what unit or which weapon and regardless of its Armor. Spell effects may vary, e.g. Plague works normally, but Irradiate doesn't).
     */
    std::vector<unit_size_enum_t>* unit_size() const { return m_unit_size; }

    /**
     * Unit basic Armor level. Armor is subtracted from damage caused by every attack from another unit. If Armor is higher than the attack damage, the unit will act as if was of "Independent" Unit Size.
     */
    std::vector<uint8_t>* armor() const { return m_armor; }

    /**
     * Determines what actions may, or may not be taken by the unit if it is given an order through the Right-Click action.
     */
    std::vector<right_click_action_enum_t>* right_click_action() const { return m_right_click_action; }

    /**
     * Sound played after the unit is trained/built. 0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat] 
     * Only unit id 0 to 106 have this sound.
     */
    std::vector<uint16_t>* ready_sound() const { return m_ready_sound; }

    /**
     * First of the "What" sounds - played when you select the unit.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]
     */
    std::vector<uint16_t>* what_sound_start() const { return m_what_sound_start; }

    /**
     * Last of the "What" sounds - played when you select the unit.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]
     */
    std::vector<uint16_t>* what_sound_end() const { return m_what_sound_end; }

    /**
     * First of the "Annoyed" sounds - played when you click multiple times on the same unit.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]
     */
    std::vector<uint16_t>* piss_sound_start() const { return m_piss_sound_start; }

    /**
     * Last of the "Annoyed" sounds - played when you click multiple times on the same unit.  0=No sound, substract 1 to get the target sfxdata entry. [pointer to sfxdata.dat]
     */
    std::vector<uint16_t>* piss_sound_end() const { return m_piss_sound_end; }

    /**
     * First of the "Yes" sounds - played when you give the unit an order.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]
     */
    std::vector<uint16_t>* yes_sound_start() const { return m_yes_sound_start; }

    /**
     * Last of the "Yes" sounds - played when you give the unit an order.  0=No sound, substract 1 to get the target sfxdata.dat entry. [pointer to sfxdata.dat]
     */
    std::vector<uint16_t>* yes_sound_end() const { return m_yes_sound_end; }

    /**
     * Width/Height of the green placement rectangle in StarEdit, in pixels.
     */
    std::vector<staredit_placement_box_type_t*>* staredit_placement_box() const { return m_staredit_placement_box; }

    /**
     * Horizontal/vertical distance in pixels at which an addon will be placed. Exists only for units of ID 106-201 (buildings).
     */
    std::vector<addon_position_type_t*>* addon_position() const { return m_addon_position; }

    /**
     * Space the unit takes from its position. Measured in pixels.
     */
    std::vector<unit_dimension_type_t*>* unit_dimension() const { return m_unit_dimension; }

    /**
     * Unit's Idle portrait. Talking Portraits are determined by adding 110 to this value [pointer to portdata.dat]
     */
    std::vector<uint16_t>* portrait() const { return m_portrait; }

    /**
     * Amount of minerals needed to train/build the unit.
     */
    std::vector<uint16_t>* mineral_cost() const { return m_mineral_cost; }

    /**
     * Amount of Vespene Gas needed to train/build the unit.
     */
    std::vector<uint16_t>* vespene_cost() const { return m_vespene_cost; }

    /**
     * Amount of time it takes to train/build the unit, in 1/24ths of a second (at Fastest speed).
     */
    std::vector<uint16_t>* build_time() const { return m_build_time; }

    /**
     * TBD
     */
    std::vector<uint16_t>* requirements() const { return m_requirements; }

    /**
     * Flags used in StarEdit. Check the type for detail specification.
     */
    std::vector<staredit_group_flags_type_t*>* staredit_group_flags() const { return m_staredit_group_flags; }

    /**
     * Amount of Supply/Psi/Control required to train/build the unit. Halves are rounded down for the display, but calculated normally.
     * TODO: check why StarDat shows always the half of what is in units.dat
     */
    std::vector<uint8_t>* supply_provided() const { return m_supply_provided; }

    /**
     * Amount of Supply/Psi/Control required to train/build the unit. Halves are rounded down for the display, but calculated normally.
     * TODO: check why StarDat shows always the half of what is in units.dat
     */
    std::vector<uint8_t>* supply_required() const { return m_supply_required; }

    /**
     * Amount of loading space the unit takes up in a transport. If it is higher than the transport's loading space, the unit cannot be loaded. It DOES NOT resize the unit's wireframe when inside the transport.
     */
    std::vector<uint8_t>* space_required() const { return m_space_required; }

    /**
     * Amout of loading space the unit has. Used with dropships. This IS NOT the number of units the transporting unit may carry as different unit may take up different amount of loading space.
     */
    std::vector<uint8_t>* space_provided() const { return m_space_provided; }

    /**
     * Amount of points given for training/building the unit, counted to the total score after the end of a game.
     */
    std::vector<uint16_t>* build_score() const { return m_build_score; }

    /**
     * Amount of points given for destroying the unit, counted to the total score after the end of a game. It is also used by the AI for targetting purposes. Units with a higher destroy score will be targeted first.
     */
    std::vector<uint16_t>* destroy_score() const { return m_destroy_score; }

    /**
     * If this property is different from 0, the unit's name will be read from the strings stored within the map (CHK) that is currently loaded, instead of the stat_txt.tbl file.
     */
    std::vector<uint16_t>* unit_map_string() const { return m_unit_map_string; }

    /**
     * Makes the unit available only while playing BroodWar expansion set.
     * Only some variants of units.dat have this data block. If your version has this block activate the parameter.
     */
    std::vector<uint8_t>* broodwar_flag() const { return m_broodwar_flag; }

    /**
     * Flags used in StarEdit. Check the type for detail specification.
     */
    std::vector<staredit_availability_flags_type_t*>* staredit_availability_flags() const { return m_staredit_availability_flags; }
    bool has_broodwar_flag() const { return m_has_broodwar_flag; }
    bool has_max_air_hits() const { return m_has_max_air_hits; }
    bool has_max_ground_hits() const { return m_has_max_ground_hits; }
    units_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
    std::vector<std::string>* _raw_special_ability_flags() const { return m__raw_special_ability_flags; }
    std::vector<kaitai::kstream*>* _io__raw_special_ability_flags() const { return m__io__raw_special_ability_flags; }
    std::vector<std::string>* _raw_staredit_group_flags() const { return m__raw_staredit_group_flags; }
    std::vector<kaitai::kstream*>* _io__raw_staredit_group_flags() const { return m__io__raw_staredit_group_flags; }
    std::vector<std::string>* _raw_staredit_availability_flags() const { return m__raw_staredit_availability_flags; }
    std::vector<kaitai::kstream*>* _io__raw_staredit_availability_flags() const { return m__io__raw_staredit_availability_flags; }
};

#endif  // UNITS_DAT_H_
