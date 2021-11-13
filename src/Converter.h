/*
 * Converter.h
 *
 *      Author: Andreas Volz
 */

#ifndef CONVERTER_H_
#define CONVERTER_H_

// System
#include <memory>
#include <string>

// Forward declarations
class Hurricane;

class Converter
{
public:
	Converter(std::shared_ptr<Hurricane> hurricane);
	virtual ~Converter();

	virtual bool convert(const std::string &arcfile, const std::string &file) = 0;

protected:
	std::shared_ptr<Hurricane> mHurricane;
};

#endif /* ONVERTER_H_ */
