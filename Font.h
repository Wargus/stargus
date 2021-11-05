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



#endif /* FONT_H_ */
