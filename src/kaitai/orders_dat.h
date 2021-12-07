#ifndef ORDERS_DAT_H_
#define ORDERS_DAT_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif

class orders_dat_t : public kaitai::kstruct {

public:

    orders_dat_t(uint8_t p_num_lines, kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, orders_dat_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~orders_dat_t();

private:
    std::vector<uint16_t>* m_label;
    std::vector<uint8_t>* m_use_weapon_targeting;
    std::vector<uint8_t>* m_unknown2;
    std::vector<uint8_t>* m_unknown3;
    std::vector<uint8_t>* m_unknown4;
    std::vector<uint8_t>* m_unknown5;
    std::vector<uint8_t>* m_interruptible;
    std::vector<uint8_t>* m_unknown7;
    std::vector<uint8_t>* m_queueable;
    std::vector<uint8_t>* m_unknown9;
    std::vector<uint8_t>* m_unknown10;
    std::vector<uint8_t>* m_unknown11;
    std::vector<uint8_t>* m_unknown12;
    std::vector<uint8_t>* m_targeting;
    std::vector<uint8_t>* m_energy;
    std::vector<uint8_t>* m_animation;
    std::vector<uint16_t>* m_highlight;
    std::vector<uint16_t>* m_unknown17;
    std::vector<uint8_t>* m_obscured_order;
    uint8_t m_num_lines;
    orders_dat_t* m__root;
    kaitai::kstruct* m__parent;

public:

    /**
     * Probably the label of the order. Doesn't do anything - used only for convenience.[pointer to stat_txt.tbl]
     */
    std::vector<uint16_t>* label() const { return m_label; }

    /**
     * Order will use the weapons.dat targeting settings.
     */
    std::vector<uint8_t>* use_weapon_targeting() const { return m_use_weapon_targeting; }
    std::vector<uint8_t>* unknown2() const { return m_unknown2; }
    std::vector<uint8_t>* unknown3() const { return m_unknown3; }
    std::vector<uint8_t>* unknown4() const { return m_unknown4; }
    std::vector<uint8_t>* unknown5() const { return m_unknown5; }

    /**
     * Order's execution can be interrupted by calling another order (e.g. movement or something). Does not work for the "Die" order.
     */
    std::vector<uint8_t>* interruptible() const { return m_interruptible; }
    std::vector<uint8_t>* unknown7() const { return m_unknown7; }
    std::vector<uint8_t>* queueable() const { return m_queueable; }

    /**
     * Order execution can be queued using the SHIFT+click combination, up to 16 times.
     */
    std::vector<uint8_t>* unknown9() const { return m_unknown9; }
    std::vector<uint8_t>* unknown10() const { return m_unknown10; }
    std::vector<uint8_t>* unknown11() const { return m_unknown11; }
    std::vector<uint8_t>* unknown12() const { return m_unknown12; }

    /**
     * Weapon used by the order to determine the targeting rules, if "Use Weapon Targeting" is checked. [pointer to weapons.dat]
     */
    std::vector<uint8_t>* targeting() const { return m_targeting; }

    /**
     * Technology used to determine the energy cost of calling the order. [pointer to techdata.dat]
     */
    std::vector<uint8_t>* energy() const { return m_energy; }

    /**
     * Unit Iscript animation to use while calling the order.
     */
    std::vector<uint8_t>* animation() const { return m_animation; }

    /**
     * Determines which icon on the button panel is highlightened when the order is being called. If the selected icon is not present, no icon is highlightened. 65535 = no highlight at all [pointer to cmdicons.grp]
     */
    std::vector<uint16_t>* highlight() const { return m_highlight; }
    std::vector<uint16_t>* unknown17() const { return m_unknown17; }

    /**
     * Order to be run if the target is obscured by the Fog-of-War. [pointer to orders.dat]
     */
    std::vector<uint8_t>* obscured_order() const { return m_obscured_order; }
    uint8_t num_lines() const { return m_num_lines; }
    orders_dat_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // ORDERS_DAT_H_
