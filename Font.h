/*
 * Font.h
 *
 *      Author: Andreas Volz
 */

#ifndef FONT_H_
#define FONT_H_

// System
#include <memory>

// Forward declarations
class Hurricane;

class Font
{
public:
	Font(std::shared_ptr<Hurricane> hurricane);
	virtual ~Font();

	bool convert(const std::string &arcfile, const char* file, int pale);

private:
	unsigned char* convertImage(unsigned char* start, int *wp, int *hp);

	std::shared_ptr<Hurricane> mHurricane;
};



#endif /* FONT_H_ */
