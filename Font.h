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

	static unsigned char* convertImage(unsigned char* start, int *wp, int *hp);
};

bool ConvertFont(const char *mpqfile, const char* arcfile, const char* file, int pale);

#endif /* FONT_H_ */
