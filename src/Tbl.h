/*
 * StatTxtTbl.h
 *
 *      Author: Andreas Volz
 */

#ifndef STAT_TXT_TBL_H_
#define STAT_TXT_TBL_H_

// Local
#include "Logger.h"
#include "kaitai/file_tbl.h"

// System
#include <memory>

class TblEntry
{
public:
	TblEntry()
	{
		shortcut_pos = -1;
		shortcut = ' ';
	}
	std::string name;
	std::string category1;
	std::string category2;
	int shortcut_pos;
	char shortcut;
};

class Tbl
{
public:
	Tbl();
	virtual ~Tbl();

	std::vector<TblEntry> convertFromStream(std::shared_ptr<kaitai::kstream> ks);

private:
	/**
	 *  @return a UTF-8 string that has to be free()d after usage
	 */
	char *iconvISO2UTF8(char *iso);

	Logger mLogger;
};

#endif /* STAT_TXT_TBL_H_ */
