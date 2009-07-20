
const char ** WeaponTypes = {"unknown", "explosive", "concussive", "normal", "spell"};

#pragma pack(1)

struct WeaponType
{
	unsigned short label;
	unsigned short sprite;
	unsigned short spell;
	unsigned short flag;
	unsigned short range;
	unsigned short upgrade_type;
	unsigned short type;
	unsigned short mbehavior;
	unsigned short mtype;
	unsigned short explosion;
	unsigned short splash;
	unsigned short damage;
	unsigned short bonus;
	unsigned short cool;
	unsigned short factor;
	unsigned short pos1;
	unsigned short pos2;
	unsigned short msg;
	unsigned short icon;
};

#pragma pop()
