/*
 * scm.h
 *
 *  Created on: 28.10.2021
 *      Author: andreas
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


#ifdef DEBUG
#define DebugLevel1(x) printf(x)
#define DebugLevel2(x) printf(x)
#define _C_ ,
#else
#define DebugLevel1(x)
#define DebugLevel2(x)
#define _C_
#endif



void ConvertChk(const char *newname, unsigned char *chkdata, int chklen);
void ConvertScm(const char *mpqfile);

#endif /* SCM_H_ */
