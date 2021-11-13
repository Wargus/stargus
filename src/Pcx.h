/*
 * Pcx.h
 *
 *      Author: Andreas Volz
 */

#ifndef PCX_H_
#define PCX_H_

// Local
#include <Converter.h>

// System
#include <memory>

// Forward declarations
class Hurricane;

class Pcx : public Converter
{
public:
	Pcx(std::shared_ptr<Hurricane> hurricane);
	virtual ~Pcx();

	/**
	 *  Convert a pcx graphic to PNG format
	 *
	 *  @param arcfile File identifier in the MPQ file
	 *  @param file Place to save the file on the drive (relative)
	 */
	bool convert(const std::string &arcfile, const std::string &file);

private:
	/**
	 *  Convert 8 bit pcx file to raw image
	 */
	void convertToRawImage(unsigned char *pcx, unsigned char **raw,
			unsigned char **pal, int *w, int *h);

};



#endif /* PCX_H_ */
