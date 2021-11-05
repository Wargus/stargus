/*
 * Grp.h
 *
 *      Author: Andreas Volz
 */

#ifndef GRP_H_
#define GRP_H_

class Grp
{
public:
	Grp();
	virtual ~Grp();

	bool ConvertWidgets(const char *mpqfile, const char* arcfile, const char* file, int pale);

	bool ConvertGfx(const char *mpqfile, const char* arcfile, const char* file, int pale);

	bool ConvertGfu(const char *mpqfile, const char* arcfile, const char* file, int pale);


private:
	void SaveImage(char *name, unsigned char *image, unsigned char *palp, int id, int w, int h);

	void SaveButton(char *name, unsigned char *image, unsigned char *palp, int size, int id);

	void DecodeGfxEntry(int index, unsigned char* start,
		unsigned char* image, int ix, int iy, int iadd);

	void DecodeGfuEntry(int index, unsigned char* start,
		unsigned char* image, int ix, int iy, int iadd);

	unsigned char* ConvertGraphic(int gfx, unsigned char* bp, int *wp, int *hp,
		unsigned char* bp2, int start2);

	void ConvertPal3(unsigned char* image, int w, int h);

};

#endif /* GRP_H_ */
