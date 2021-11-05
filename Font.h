/*
 * Font.h
 *
 *      Author: Andreas Volz
 */

#ifndef FONT_H_
#define FONT_H_

class Font
{
public:
	Font();
	virtual ~Font();

	bool convert(const char *mpqfile, const char* arcfile, const char* file, int pale);

private:
	unsigned char* convertImage(unsigned char* start, int *wp, int *hp);
};



#endif /* FONT_H_ */
