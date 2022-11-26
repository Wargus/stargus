#ifndef ISCRIPT_BIN_H_
#define ISCRIPT_BIN_H_

// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "kaitai/kaitaistruct.h"
#include <stdint.h>
#include "opcode_list_type.h"
#include <vector>

#if KAITAI_STRUCT_VERSION < 9000L
#error "Incompatible Kaitai Struct C++/STL API: version 0.9 or later is required"
#endif
class opcode_list_type_t;

class iscript_bin_t : public kaitai::kstruct {

public:
    class scpe_content_type_t;
    class trgtrangecondjmp_type_t;
    class u1_type_t;
    class playsounds_type_t;
    class randcondjmp_type_t;
    class empty_type_t;
    class pos_type_t;
    class sprl_type_t;
    class opcode_type_t;
    class trgcondjmp_type_t;
    class entree_offset_type_t;
    class scpe_type_t;
    class playsndbtwn_type_t;
    class imgl_type_t;
    class waitrand_type_t;
    class sprov_type_t;
    class scpe_header_type_t;
    class u2_type_t;

    enum opcode_t {
        OPCODE_PLAYFRAM = 0,
        OPCODE_PLAYFRAMTILE = 1,
        OPCODE_SETHORPOS = 2,
        OPCODE_SETVERTPOS = 3,
        OPCODE_SETPOS = 4,
        OPCODE_WAIT = 5,
        OPCODE_WAITRAND = 6,
        OPCODE_GOTO = 7,
        OPCODE_IMGOL = 8,
        OPCODE_IMGUL = 9,
        OPCODE_IMGOLORIG = 10,
        OPCODE_SWITCHUL = 11,
        OPCODE_UNKNOWN_0C = 12,
        OPCODE_IMGOLUSELO = 13,
        OPCODE_IMGULUSELO = 14,
        OPCODE_SPROL = 15,
        OPCODE_HIGHSPROL = 16,
        OPCODE_LOWSPRUL = 17,
        OPCODE_UFLUNSTABLE = 18,
        OPCODE_SPRULUSELO = 19,
        OPCODE_SPRUL = 20,
        OPCODE_SPROLUSELO = 21,
        OPCODE_END = 22,
        OPCODE_SETFLIPSTATE = 23,
        OPCODE_PLAYSND = 24,
        OPCODE_PLAYSNDRAND = 25,
        OPCODE_PLAYSNDBTWN = 26,
        OPCODE_DOMISSILEDMG = 27,
        OPCODE_ATTACKMELEE = 28,
        OPCODE_FOLLOWMAINGRAPHIC = 29,
        OPCODE_RANDCONDJMP = 30,
        OPCODE_TURNCCWISE = 31,
        OPCODE_TURNCWISE = 32,
        OPCODE_TURN1CWISE = 33,
        OPCODE_TURNRAND = 34,
        OPCODE_SETSPAWNFRAME = 35,
        OPCODE_SIGORDER = 36,
        OPCODE_ATTACKWITH = 37,
        OPCODE_ATTACK = 38,
        OPCODE_CASTSPELL = 39,
        OPCODE_USEWEAPON = 40,
        OPCODE_MOVE = 41,
        OPCODE_GOTOREPEATATTK = 42,
        OPCODE_ENGFRAME = 43,
        OPCODE_ENGSET = 44,
        OPCODE_UNKNOWN_2D = 45,
        OPCODE_NOBRKCODESTART = 46,
        OPCODE_NOBRKCODEEND = 47,
        OPCODE_IGNOREREST = 48,
        OPCODE_ATTKSHIFTPROJ = 49,
        OPCODE_TMPRMGRAPHICSTART = 50,
        OPCODE_TMPRMGRAPHICEND = 51,
        OPCODE_SETFLDIRECT = 52,
        OPCODE_CALL = 53,
        OPCODE_RETURN = 54,
        OPCODE_SETFLSPEED = 55,
        OPCODE_CREATEGASOVERLAYS = 56,
        OPCODE_PWRUPCONDJMP = 57,
        OPCODE_TRGTRANGECONDJMP = 58,
        OPCODE_TRGTARCCONDJMP = 59,
        OPCODE_CURDIRECTCONDJMP = 60,
        OPCODE_IMGULNEXTID = 61,
        OPCODE_UNKNOWN_3E = 62,
        OPCODE_LIFTOFFCONDJMP = 63,
        OPCODE_WARPOVERLAY = 64,
        OPCODE_ORDERDONE = 65,
        OPCODE_GRDSPROL = 66,
        OPCODE_UNKNOWN_43 = 67,
        OPCODE_DOGRDDAMAGE = 68
    };

    iscript_bin_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

private:
    void _read();
    void _clean_up();

public:
    ~iscript_bin_t();

    class scpe_content_type_t : public kaitai::kstruct {

    public:

        scpe_content_type_t(kaitai::kstream* p__io, iscript_bin_t::scpe_type_t* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~scpe_content_type_t();

    private:
        bool f_scpe_opcode_list;
        opcode_list_type_t* m_scpe_opcode_list;
        bool n_scpe_opcode_list;

    public:
        bool _is_null_scpe_opcode_list() { scpe_opcode_list(); return n_scpe_opcode_list; };

    private:

    public:
        opcode_list_type_t* scpe_opcode_list();

    private:
        uint16_t m_scpe_opcode_offset;
        iscript_bin_t* m__root;
        iscript_bin_t::scpe_type_t* m__parent;

    public:
        uint16_t scpe_opcode_offset() const { return m_scpe_opcode_offset; }
        iscript_bin_t* _root() const { return m__root; }
        iscript_bin_t::scpe_type_t* _parent() const { return m__parent; }
    };

    class trgtrangecondjmp_type_t : public kaitai::kstruct {

    public:

        trgtrangecondjmp_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~trgtrangecondjmp_type_t();

    private:
        uint16_t m_distance;
        uint16_t m_labelname;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint16_t distance() const { return m_distance; }
        uint16_t labelname() const { return m_labelname; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class u1_type_t : public kaitai::kstruct {

    public:

        u1_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~u1_type_t();

    private:
        uint8_t m_value;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint8_t value() const { return m_value; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class playsounds_type_t : public kaitai::kstruct {

    public:

        playsounds_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~playsounds_type_t();

    private:
        uint8_t m_number_sounds;
        std::vector<uint16_t>* m_sound;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint8_t number_sounds() const { return m_number_sounds; }
        std::vector<uint16_t>* sound() const { return m_sound; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class randcondjmp_type_t : public kaitai::kstruct {

    public:

        randcondjmp_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~randcondjmp_type_t();

    private:
        uint8_t m_randchance;
        uint16_t m_labelname;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint8_t randchance() const { return m_randchance; }
        uint16_t labelname() const { return m_labelname; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class empty_type_t : public kaitai::kstruct {

    public:

        empty_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~empty_type_t();

    private:
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class pos_type_t : public kaitai::kstruct {

    public:

        pos_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~pos_type_t();

    private:
        uint8_t m_x;
        uint8_t m_y;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint8_t x() const { return m_x; }
        uint8_t y() const { return m_y; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class sprl_type_t : public kaitai::kstruct {

    public:

        sprl_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~sprl_type_t();

    private:
        uint16_t m_sprite;
        pos_type_t* m_pos;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint16_t sprite() const { return m_sprite; }
        pos_type_t* pos() const { return m_pos; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class opcode_type_t : public kaitai::kstruct {

    public:

        opcode_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~opcode_type_t();

    private:
        opcode_t m_code;
        kaitai::kstruct* m_args;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        opcode_t code() const { return m_code; }
        kaitai::kstruct* args() const { return m_args; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class trgcondjmp_type_t : public kaitai::kstruct {

    public:

        trgcondjmp_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~trgcondjmp_type_t();

    private:
        uint16_t m_angle1;
        uint16_t m_angle2;
        uint16_t m_labelname;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint16_t angle1() const { return m_angle1; }
        uint16_t angle2() const { return m_angle2; }
        uint16_t labelname() const { return m_labelname; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class entree_offset_type_t : public kaitai::kstruct {

    public:

        entree_offset_type_t(kaitai::kstream* p__io, iscript_bin_t* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~entree_offset_type_t();

    private:
        uint16_t m_iscript_id;
        uint16_t m_offset;
        iscript_bin_t* m__root;
        iscript_bin_t* m__parent;

    public:
        uint16_t iscript_id() const { return m_iscript_id; }
        uint16_t offset() const { return m_offset; }
        iscript_bin_t* _root() const { return m__root; }
        iscript_bin_t* _parent() const { return m__parent; }
    };

    class scpe_type_t : public kaitai::kstruct {

    public:

        scpe_type_t(uint16_t p_i, kaitai::kstream* p__io, iscript_bin_t* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~scpe_type_t();

    private:
        bool f_scpe_header;
        scpe_header_type_t* m_scpe_header;

    public:
        scpe_header_type_t* scpe_header();

    private:
        bool f_num_scpe_content;
        int8_t m_num_scpe_content;

    public:
        int8_t num_scpe_content();

    private:
        bool f_scpe_content;
        std::vector<scpe_content_type_t*>* m_scpe_content;

    public:
        std::vector<scpe_content_type_t*>* scpe_content();

    private:
        uint16_t m_i;
        iscript_bin_t* m__root;
        iscript_bin_t* m__parent;

    public:
        uint16_t i() const { return m_i; }
        iscript_bin_t* _root() const { return m__root; }
        iscript_bin_t* _parent() const { return m__parent; }
    };

    class playsndbtwn_type_t : public kaitai::kstruct {

    public:

        playsndbtwn_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~playsndbtwn_type_t();

    private:
        uint16_t m_firstsound;
        uint16_t m_lastsound;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint16_t firstsound() const { return m_firstsound; }
        uint16_t lastsound() const { return m_lastsound; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class imgl_type_t : public kaitai::kstruct {

    public:

        imgl_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~imgl_type_t();

    private:
        uint16_t m_image;
        pos_type_t* m_pos;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint16_t image() const { return m_image; }
        pos_type_t* pos() const { return m_pos; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class waitrand_type_t : public kaitai::kstruct {

    public:

        waitrand_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~waitrand_type_t();

    private:
        uint8_t m_ticks1;
        uint8_t m_ticks2;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint8_t ticks1() const { return m_ticks1; }
        uint8_t ticks2() const { return m_ticks2; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class sprov_type_t : public kaitai::kstruct {

    public:

        sprov_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~sprov_type_t();

    private:
        uint16_t m_sprite;
        uint8_t m_overlay;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint16_t sprite() const { return m_sprite; }
        uint8_t overlay() const { return m_overlay; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

    class scpe_header_type_t : public kaitai::kstruct {

    public:

        scpe_header_type_t(kaitai::kstream* p__io, iscript_bin_t::scpe_type_t* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~scpe_header_type_t();

    private:
        uint32_t m_scpe_magic;
        uint8_t m_scpe_content_type;
        std::string m_padding;
        iscript_bin_t* m__root;
        iscript_bin_t::scpe_type_t* m__parent;

    public:
        uint32_t scpe_magic() const { return m_scpe_magic; }
        uint8_t scpe_content_type() const { return m_scpe_content_type; }
        std::string padding() const { return m_padding; }
        iscript_bin_t* _root() const { return m__root; }
        iscript_bin_t::scpe_type_t* _parent() const { return m__parent; }
    };

    class u2_type_t : public kaitai::kstruct {

    public:

        u2_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent = 0, iscript_bin_t* p__root = 0);

    private:
        void _read();
        void _clean_up();

    public:
        ~u2_type_t();

    private:
        uint16_t m_value;
        iscript_bin_t* m__root;
        kaitai::kstruct* m__parent;

    public:
        uint16_t value() const { return m_value; }
        iscript_bin_t* _root() const { return m__root; }
        kaitai::kstruct* _parent() const { return m__parent; }
    };

private:
    bool f_version_tag;
    uint32_t m_version_tag;

public:

    /**
     * value is 0x0 in case of broodwar and any other value for plain old starcraft
     */
    uint32_t version_tag();

private:
    bool f_entree_table_pos;
    uint16_t m_entree_table_pos;

public:
    uint16_t entree_table_pos();

private:
    bool f_entree_offsets;
    std::vector<entree_offset_type_t*>* m_entree_offsets;

public:

    /**
     * read entree offsets until the magic stop sign '0xFFFF 0x0000' is found
     */
    std::vector<entree_offset_type_t*>* entree_offsets();

private:
    bool f_scpe;
    std::vector<scpe_type_t*>* m_scpe;

public:

    /**
     * tbd
     */
    std::vector<scpe_type_t*>* scpe();

private:
    uint16_t m_first_word;
    iscript_bin_t* m__root;
    kaitai::kstruct* m__parent;

public:
    uint16_t first_word() const { return m_first_word; }
    iscript_bin_t* _root() const { return m__root; }
    kaitai::kstruct* _parent() const { return m__parent; }
};

#endif  // ISCRIPT_BIN_H_
