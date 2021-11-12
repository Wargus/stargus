/*
 * scm.h
 *
 *      Author: Andreas Volz
 */
#ifndef SCM_H_
#define SCM_H_

// Local
#include "Chk.h"

// System
#include <cstring>
#include <vector>
#include <string>
#include <memory>

// Forward declarations
class Hurricane;


/**
 * Map Container
 *
 * The .scm is MPQ encoded and will be decoded to a .ckk and then further processed by Chk class
 * At the end .scm is only useful with Storm
 */
class Scm
{
public:
	Scm(std::shared_ptr<Hurricane> hurricane);
	virtual ~Scm();

	bool convert(const std::string &arcfile, const std::string &file);

private:
	//void load(const char *mpqfile, const char *dir);

	std::shared_ptr<Hurricane> mHurricane;
};





#endif /* SCM_H_ */
