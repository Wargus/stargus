/*
 * Pcx.h
 *
 *      Author: Andreas Volz
 */

#ifndef PCX_H_
#define PCX_H_

// System
#include <memory>

// Forward declarations
class Hurricane;

class Pcx
{
public:
	Pcx(std::shared_ptr<Hurricane> hurricane);
	virtual ~Pcx();

	bool convert(const char *arcfile, const char *file);

private:
	void convertToRawImage(unsigned char *pcx, unsigned char **raw,
			unsigned char **pal, int *w, int *h);

	std::shared_ptr<Hurricane> mHurricane;
};



#endif /* PCX_H_ */
