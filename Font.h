/*
 * Font.h
 *
 *      Author: Andreas Volz
 */

#ifndef FONT_H_
#define FONT_H_

// Local
#include "Logger.h"

// System
#include <memory>

// Forward declarations
class Hurricane;

class Font
{
public:
	Font(std::shared_ptr<Hurricane> hurricane);
	virtual ~Font();

	bool convert(const std::string &arcfile, const std::string &file, int pale);

private:
	unsigned char* convertImage(unsigned char* start, int *wp, int *hp);
	unsigned char* convertImage2(unsigned char* start, int *wp, int *hp);

	Logger mLogger;

	std::shared_ptr<Hurricane> mHurricane;
};



#endif /* FONT_H_ */
