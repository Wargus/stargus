/*
 * Units.h
 *
 *      Author: Andreas Volz
 */

#ifndef UNITS_H_
#define UNITS_H_

// Local
#include "kaitai/units_dat.h"
#include "Logger.h"
#include "Converter.h"

// System
#include <memory>

// Forward declarations
class Hurricane;

class Units : public Converter
{
public:
	Units(std::shared_ptr<Hurricane> hurricane);
	virtual ~Units();

	virtual bool convert(const std::string &arcfile, const std::string &file);

private:
	Logger mLogger;
};

#endif /* UNITS_H_ */
