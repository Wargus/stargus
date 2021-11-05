/*
 * Pcx.h
 *
 *      Author: Andreas Volz
 */

#ifndef PCX_H_
#define PCX_H_

class Pcx
{
public:
	Pcx();
	virtual ~Pcx();

	bool convert(const char *mpqfile, const char *arcfile, const char *file);

private:
	void convertToRawImage(unsigned char *pcx, unsigned char **raw,
			unsigned char **pal, int *w, int *h);
};



#endif /* PCX_H_ */
