/*
 * Grp.h
 *
 *      Author: Andreas Volz
 */

#ifndef GRP_H_
#define GRP_H_

/**
 * Put the code for decoding of Gfu and Gfx in Gfu parent as workaround.
 * Reason seems to be a workaround for "Hardcoded support for worker with resource repairing"
 * TODO: Find a better solution and move to to Gfx/Gfu class
 */
class Grp
{
public:
	Grp();
	virtual ~Grp();

protected:
	/**
	**  Convert graphics into image.
	*/
	unsigned char* ConvertGraphic(int gfx, unsigned char* bp, int *wp, int *hp,
		unsigned char* bp2, int start2);

	/**
	**  Decode a entry(frame) into image.
	*/
	void DecodeGfxEntry(int index, unsigned char* start,
			unsigned char* image, int ix, int iy, int iadd);

	/**
	**  Decode a entry(frame) into image.
	*/
	void DecodeGfuEntry(int index, unsigned char* start,
		unsigned char* image, int ix, int iy, int iadd);

	void ConvertPal3(unsigned char* image, int w, int h);

private:


};

#endif /* GRP_H_ */
