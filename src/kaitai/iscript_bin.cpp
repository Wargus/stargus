// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

#include "iscript_bin.h"

iscript_bin_t::iscript_bin_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = this;
    m_entree_offsets = 0;
    m_scpe = 0;
    f_version_tag = false;
    f_entree_table_pos = false;
    f_entree_offsets = false;
    f_scpe = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::_read() {
    m_first_word = m__io->read_u2le();
}

iscript_bin_t::~iscript_bin_t() {
    _clean_up();
}

void iscript_bin_t::_clean_up() {
    if (f_version_tag) {
    }
    if (f_entree_offsets) {
        if (m_entree_offsets) {
            for (std::vector<entree_offset_type_t*>::iterator it = m_entree_offsets->begin(); it != m_entree_offsets->end(); ++it) {
                delete *it;
            }
            delete m_entree_offsets; m_entree_offsets = 0;
        }
    }
    if (f_scpe) {
        if (m_scpe) {
            for (std::vector<scpe_type_t*>::iterator it = m_scpe->begin(); it != m_scpe->end(); ++it) {
                delete *it;
            }
            delete m_scpe; m_scpe = 0;
        }
    }
}

iscript_bin_t::scpe_content_type_t::scpe_content_type_t(kaitai::kstream* p__io, iscript_bin_t::scpe_type_t* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_scpe_opcode_list = 0;
    f_scpe_opcode_list = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::scpe_content_type_t::_read() {
    m_scpe_opcode_offset = m__io->read_u2le();
}

iscript_bin_t::scpe_content_type_t::~scpe_content_type_t() {
    _clean_up();
}

void iscript_bin_t::scpe_content_type_t::_clean_up() {
    if (f_scpe_opcode_list) {
        if (m_scpe_opcode_list) {
            delete m_scpe_opcode_list; m_scpe_opcode_list = 0;
        }
    }
}

opcode_list_type_t* iscript_bin_t::scpe_content_type_t::scpe_opcode_list() {
    if (f_scpe_opcode_list)
        return m_scpe_opcode_list;
    std::streampos _pos = m__io->pos();
    m__io->seek(scpe_opcode_offset());
    m_scpe_opcode_list = new opcode_list_type_t(_parent(), _root(), m__io);
    m__io->seek(_pos);
    f_scpe_opcode_list = true;
    return m_scpe_opcode_list;
}

iscript_bin_t::trgtrangecondjmp_type_t::trgtrangecondjmp_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::trgtrangecondjmp_type_t::_read() {
    m_distance = m__io->read_u2le();
    m_labelname = m__io->read_u2le();
}

iscript_bin_t::trgtrangecondjmp_type_t::~trgtrangecondjmp_type_t() {
    _clean_up();
}

void iscript_bin_t::trgtrangecondjmp_type_t::_clean_up() {
}

iscript_bin_t::u1_type_t::u1_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::u1_type_t::_read() {
    m_value = m__io->read_u1();
}

iscript_bin_t::u1_type_t::~u1_type_t() {
    _clean_up();
}

void iscript_bin_t::u1_type_t::_clean_up() {
}

iscript_bin_t::playsounds_type_t::playsounds_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_sound = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::playsounds_type_t::_read() {
    m_number_sounds = m__io->read_u1();
    m_sound = new std::vector<uint16_t>();
    const int l_sound = number_sounds();
    for (int i = 0; i < l_sound; i++) {
        m_sound->push_back(m__io->read_u2le());
    }
}

iscript_bin_t::playsounds_type_t::~playsounds_type_t() {
    _clean_up();
}

void iscript_bin_t::playsounds_type_t::_clean_up() {
    if (m_sound) {
        delete m_sound; m_sound = 0;
    }
}

iscript_bin_t::randcondjmp_type_t::randcondjmp_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::randcondjmp_type_t::_read() {
    m_randchance = m__io->read_u1();
    m_labelname = m__io->read_u2le();
}

iscript_bin_t::randcondjmp_type_t::~randcondjmp_type_t() {
    _clean_up();
}

void iscript_bin_t::randcondjmp_type_t::_clean_up() {
}

iscript_bin_t::empty_type_t::empty_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::empty_type_t::_read() {
}

iscript_bin_t::empty_type_t::~empty_type_t() {
    _clean_up();
}

void iscript_bin_t::empty_type_t::_clean_up() {
}

iscript_bin_t::pos_type_t::pos_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::pos_type_t::_read() {
    m_x = m__io->read_u1();
    m_y = m__io->read_u1();
}

iscript_bin_t::pos_type_t::~pos_type_t() {
    _clean_up();
}

void iscript_bin_t::pos_type_t::_clean_up() {
}

iscript_bin_t::sprl_type_t::sprl_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_pos = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::sprl_type_t::_read() {
    m_sprite = m__io->read_u2le();
    m_pos = new pos_type_t(m__io, this, m__root);
}

iscript_bin_t::sprl_type_t::~sprl_type_t() {
    _clean_up();
}

void iscript_bin_t::sprl_type_t::_clean_up() {
    if (m_pos) {
        delete m_pos; m_pos = 0;
    }
}

iscript_bin_t::opcode_type_t::opcode_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::opcode_type_t::_read() {
    m_code = static_cast<iscript_bin_t::opcode_t>(m__io->read_u1());
    switch (code()) {
    case iscript_bin_t::OPCODE_TURN1CWISE: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_IMGOLORIG: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_UNKNOWN_3E: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SIGORDER: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_ENGFRAME: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_TURNCCWISE: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_UNKNOWN_2D: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_END: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_PLAYFRAM: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_TMPRMGRAPHICSTART: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_IMGULNEXTID: {
        m_args = new pos_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_PLAYSNDBTWN: {
        m_args = new playsndbtwn_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_UNKNOWN_0C: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_ENGSET: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SWITCHUL: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_TRGTARCCONDJMP: {
        m_args = new trgcondjmp_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SETFLIPSTATE: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SETPOS: {
        m_args = new pos_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_IMGOLUSELO: {
        m_args = new imgl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_LOWSPRUL: {
        m_args = new sprl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_TURNRAND: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_DOMISSILEDMG: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_HIGHSPROL: {
        m_args = new sprl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SETFLSPEED: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_USEWEAPON: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_WARPOVERLAY: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_GOTOREPEATATTK: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_UFLUNSTABLE: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_ORDERDONE: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_TRGTRANGECONDJMP: {
        m_args = new trgtrangecondjmp_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_RETURN: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_CASTSPELL: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_FOLLOWMAINGRAPHIC: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_RANDCONDJMP: {
        m_args = new randcondjmp_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_NOBRKCODEEND: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_CALL: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_NOBRKCODESTART: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_WAIT: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SPROL: {
        m_args = new sprl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_TMPRMGRAPHICEND: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_CREATEGASOVERLAYS: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SETFLDIRECT: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_PWRUPCONDJMP: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SETHORPOS: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SPRULUSELO: {
        m_args = new sprl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SPRUL: {
        m_args = new sprl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_GRDSPROL: {
        m_args = new sprl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_MOVE: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_GOTO: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_IMGUL: {
        m_args = new imgl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_PLAYFRAMTILE: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_ATTKSHIFTPROJ: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_LIFTOFFCONDJMP: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_IMGOL: {
        m_args = new imgl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_IMGULUSELO: {
        m_args = new imgl_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_ATTACK: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_ATTACKMELEE: {
        m_args = new playsounds_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SPROLUSELO: {
        m_args = new sprov_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_PLAYSNDRAND: {
        m_args = new playsounds_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_IGNOREREST: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_PLAYSND: {
        m_args = new u2_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_UNKNOWN_43: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SETVERTPOS: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_DOGRDDAMAGE: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_WAITRAND: {
        m_args = new waitrand_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_TURNCWISE: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_CURDIRECTCONDJMP: {
        m_args = new trgcondjmp_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_SETSPAWNFRAME: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    case iscript_bin_t::OPCODE_ATTACKWITH: {
        m_args = new u1_type_t(m__io, this, m__root);
        break;
    }
    default: {
        m_args = new empty_type_t(m__io, this, m__root);
        break;
    }
    }
}

iscript_bin_t::opcode_type_t::~opcode_type_t() {
    _clean_up();
}

void iscript_bin_t::opcode_type_t::_clean_up() {
    if (m_args) {
        delete m_args; m_args = 0;
    }
}

iscript_bin_t::trgcondjmp_type_t::trgcondjmp_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::trgcondjmp_type_t::_read() {
    m_angle1 = m__io->read_u2le();
    m_angle2 = m__io->read_u2le();
    m_labelname = m__io->read_u2le();
}

iscript_bin_t::trgcondjmp_type_t::~trgcondjmp_type_t() {
    _clean_up();
}

void iscript_bin_t::trgcondjmp_type_t::_clean_up() {
}

iscript_bin_t::entree_offset_type_t::entree_offset_type_t(kaitai::kstream* p__io, iscript_bin_t* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::entree_offset_type_t::_read() {
    m_iscript_id = m__io->read_u2le();
    m_offset = m__io->read_u2le();
}

iscript_bin_t::entree_offset_type_t::~entree_offset_type_t() {
    _clean_up();
}

void iscript_bin_t::entree_offset_type_t::_clean_up() {
}

iscript_bin_t::scpe_type_t::scpe_type_t(uint16_t p_i, kaitai::kstream* p__io, iscript_bin_t* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_i = p_i;
    m_scpe_header = 0;
    m_scpe_content = 0;
    f_scpe_header = false;
    f_scpe_content = false;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::scpe_type_t::_read() {
}

iscript_bin_t::scpe_type_t::~scpe_type_t() {
    _clean_up();
}

void iscript_bin_t::scpe_type_t::_clean_up() {
    if (f_scpe_header) {
        if (m_scpe_header) {
            delete m_scpe_header; m_scpe_header = 0;
        }
    }
    if (f_scpe_content) {
        if (m_scpe_content) {
            for (std::vector<scpe_content_type_t*>::iterator it = m_scpe_content->begin(); it != m_scpe_content->end(); ++it) {
                delete *it;
            }
            delete m_scpe_content; m_scpe_content = 0;
        }
    }
}

iscript_bin_t::scpe_header_type_t* iscript_bin_t::scpe_type_t::scpe_header() {
    if (f_scpe_header)
        return m_scpe_header;
    std::streampos _pos = m__io->pos();
    m__io->seek(_parent()->entree_offsets()->at(i())->offset());
    m_scpe_header = new scpe_header_type_t(m__io, this, m__root);
    m__io->seek(_pos);
    f_scpe_header = true;
    return m_scpe_header;
}

std::vector<iscript_bin_t::scpe_content_type_t*>* iscript_bin_t::scpe_type_t::scpe_content() {
    if (f_scpe_content)
        return m_scpe_content;
    std::streampos _pos = m__io->pos();
    m__io->seek((_parent()->entree_offsets()->at(i())->offset() + 8));
    m_scpe_content = new std::vector<scpe_content_type_t*>();
    const int l_scpe_content = ((scpe_header()->scpe_content_type() == 0) ? (2) : (((scpe_header()->scpe_content_type() == 1) ? (2) : (((scpe_header()->scpe_content_type() == 2) ? (4) : (((scpe_header()->scpe_content_type() == 12) ? (14) : (((scpe_header()->scpe_content_type() == 13) ? (14) : (((scpe_header()->scpe_content_type() == 14) ? (15) : (((scpe_header()->scpe_content_type() == 15) ? (15) : (((scpe_header()->scpe_content_type() == 20) ? (21) : (((scpe_header()->scpe_content_type() == 21) ? (21) : (((scpe_header()->scpe_content_type() == 23) ? (23) : (((scpe_header()->scpe_content_type() == 24) ? (25) : (((scpe_header()->scpe_content_type() == 26) ? (27) : (((scpe_header()->scpe_content_type() == 27) ? (27) : (((scpe_header()->scpe_content_type() == 28) ? (27) : (((scpe_header()->scpe_content_type() == 29) ? (27) : (0))))))))))))))))))))))))))))));
    for (int i = 0; i < l_scpe_content; i++) {
        m_scpe_content->push_back(new scpe_content_type_t(m__io, this, m__root));
    }
    m__io->seek(_pos);
    f_scpe_content = true;
    return m_scpe_content;
}

iscript_bin_t::playsndbtwn_type_t::playsndbtwn_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::playsndbtwn_type_t::_read() {
    m_firstsound = m__io->read_u2le();
    m_lastsound = m__io->read_u2le();
}

iscript_bin_t::playsndbtwn_type_t::~playsndbtwn_type_t() {
    _clean_up();
}

void iscript_bin_t::playsndbtwn_type_t::_clean_up() {
}

iscript_bin_t::imgl_type_t::imgl_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;
    m_pos = 0;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::imgl_type_t::_read() {
    m_image = m__io->read_u2le();
    m_pos = new pos_type_t(m__io, this, m__root);
}

iscript_bin_t::imgl_type_t::~imgl_type_t() {
    _clean_up();
}

void iscript_bin_t::imgl_type_t::_clean_up() {
    if (m_pos) {
        delete m_pos; m_pos = 0;
    }
}

iscript_bin_t::waitrand_type_t::waitrand_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::waitrand_type_t::_read() {
    m_ticks1 = m__io->read_u1();
    m_ticks2 = m__io->read_u1();
}

iscript_bin_t::waitrand_type_t::~waitrand_type_t() {
    _clean_up();
}

void iscript_bin_t::waitrand_type_t::_clean_up() {
}

iscript_bin_t::sprov_type_t::sprov_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::sprov_type_t::_read() {
    m_sprite = m__io->read_u2le();
    m_overlay = m__io->read_u1();
}

iscript_bin_t::sprov_type_t::~sprov_type_t() {
    _clean_up();
}

void iscript_bin_t::sprov_type_t::_clean_up() {
}

iscript_bin_t::scpe_header_type_t::scpe_header_type_t(kaitai::kstream* p__io, iscript_bin_t::scpe_type_t* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::scpe_header_type_t::_read() {
    m_scpe_magic = m__io->read_u4le();
    m_scpe_content_type = m__io->read_u1();
    m_padding = m__io->read_bytes(3);
}

iscript_bin_t::scpe_header_type_t::~scpe_header_type_t() {
    _clean_up();
}

void iscript_bin_t::scpe_header_type_t::_clean_up() {
}

iscript_bin_t::u2_type_t::u2_type_t(kaitai::kstream* p__io, kaitai::kstruct* p__parent, iscript_bin_t* p__root) : kaitai::kstruct(p__io) {
    m__parent = p__parent;
    m__root = p__root;

    try {
        _read();
    } catch(...) {
        _clean_up();
        throw;
    }
}

void iscript_bin_t::u2_type_t::_read() {
    m_value = m__io->read_u2le();
}

iscript_bin_t::u2_type_t::~u2_type_t() {
    _clean_up();
}

void iscript_bin_t::u2_type_t::_clean_up() {
}

uint32_t iscript_bin_t::version_tag() {
    if (f_version_tag)
        return m_version_tag;
    std::streampos _pos = m__io->pos();
    m__io->seek(2);
    m_version_tag = m__io->read_u4le();
    m__io->seek(_pos);
    f_version_tag = true;
    return m_version_tag;
}

uint16_t iscript_bin_t::entree_table_pos() {
    if (f_entree_table_pos)
        return m_entree_table_pos;
    m_entree_table_pos = ((version_tag() == 0) ? (first_word()) : (0));
    f_entree_table_pos = true;
    return m_entree_table_pos;
}

std::vector<iscript_bin_t::entree_offset_type_t*>* iscript_bin_t::entree_offsets() {
    if (f_entree_offsets)
        return m_entree_offsets;
    std::streampos _pos = m__io->pos();
    m__io->seek(entree_table_pos());
    m_entree_offsets = new std::vector<entree_offset_type_t*>();
    {
        int i = 0;
        entree_offset_type_t* _;
        do {
            _ = new entree_offset_type_t(m__io, this, m__root);
            m_entree_offsets->push_back(_);
            i++;
        } while (!(((_->iscript_id() == 65535) ? (_->offset() == 0) : (false))));
    }
    m__io->seek(_pos);
    f_entree_offsets = true;
    return m_entree_offsets;
}

std::vector<iscript_bin_t::scpe_type_t*>* iscript_bin_t::scpe() {
    if (f_scpe)
        return m_scpe;
    m_scpe = new std::vector<scpe_type_t*>();
    const int l_scpe = _root()->entree_offsets()->size();
    for (int i = 0; i < l_scpe; i++) {
        m_scpe->push_back(new scpe_type_t(i, m__io, this, m__root));
    }
    f_scpe = true;
    return m_scpe;
}
