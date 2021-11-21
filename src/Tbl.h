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

class Tbl: public Converter
{
public:
	Tbl(std::shared_ptr<Hurricane> hurricane);
	virtual ~Tbl();

	virtual bool convert(const std::string &arcfile, const std::string &file);

private:
	Logger mLogger;
};

#endif /* TBL_H_ */
