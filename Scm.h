/*
 * scm.h
 *
 *      Author: Andreas Volz
 */
#ifndef SCM_H_
#define SCM_H_

#include "Chk.h"

// C++
#include <cstring>
#include <vector>
#include <string>

/*----------------------------------------------------------------------------
--	Definitions
----------------------------------------------------------------------------*/

class Scm
{
public:
	Scm();
	virtual ~Scm();

	void convert(const char *mpqfile);

private:
	void load(const char *mpqfile, const char *dir);

	Chk chk;
};





#endif /* SCM_H_ */
