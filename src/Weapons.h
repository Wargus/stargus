/*
 * Weapons.h
 *
 *      Author: Andreas Volz
 */

#ifndef WEAPONS_H_
#define WEAPONS_H_

// Local
#include <Converter.h>

class Weapons  : public Converter
{
public:
	Weapons(std::shared_ptr<Hurricane> hurricane);
	virtual ~Weapons();

	virtual bool convert(const std::string &arcfile, const std::string &file);
};

#endif /* WEAPONS_H_ */
