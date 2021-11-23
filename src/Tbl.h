/*
 * Tbl.h
 *
 *      Author: Andreas Volz
 */

#ifndef TBL_H_
#define TBL_H_

// Local
#include "kaitai/file_tbl.h"
#include "Converter.h"
#include "Logger.h"

// Forward declarations
class Hurricane;

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

class Tbl: public Converter
{
public:
	Tbl(std::shared_ptr<Hurricane> hurricane);
	virtual ~Tbl();

	virtual bool convert(const std::string &arcfile, const std::string &file);

private:
	/**
	 *  @return a UTF-8 string that has to be free()d after usage
	 */
	char *iconvISO2UTF8(char *iso);

	Logger mLogger;
};

#endif /* TBL_H_ */
