/*
 * Hurricane.h
 *
 *      Author: Andreas Volz
 */

#ifndef HURRICANE_H_
#define HURRICANE_H_

#include <string>

class Hurricane
{
public:
	Hurricane();
	Hurricane(const std::string &archiveName);
	virtual ~Hurricane();

protected:
	std::string mArchiveName;
};

#endif /* HURRICANE_H_ */
