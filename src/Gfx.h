/*
 * Gfx.h
 *
 *      Author: Andreas Volz
 */

#ifndef GFX_H_
#define GFX_H_

// C++
#include <string>

// Local
#include <Converter.h>
#include "Grp.h"

class Gfx: public Grp, Converter
{
public:
	Gfx(std::shared_ptr<Hurricane> hurricane);
	virtual ~Gfx();

	/**
	**  Convert a graphic to my format.
	*/
	bool convert(const std::string &arcfile, const std::string &file, int pale);
	bool convert(const std::string &arcfile, const std::string &file);

private:

};

#endif /* GFX_H_ */
