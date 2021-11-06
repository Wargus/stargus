/*
 * Widget.h
 *
 *      Author: Andreas Volz
 */

#ifndef WIDGETS_H_
#define WIDGETS_H_

#include "Grp.h"

class Widgets: public Grp
{
public:
	Widgets();
	virtual ~Widgets();

	/**
	 * Convert a widget from data container as several PNG files
	 */
	bool convert(const char *mpqfile, const char* arcfile, const char* file, int pale);

private:
	/**
	 * Save Image part of a Widget as PNG file
	 */
	void SaveImage(char *name, unsigned char *image, unsigned char *palp, int id, int w, int h);

	/**
	 * Save Button part of a Widget as PNG
	 */
	void SaveButton(char *name, unsigned char *image, unsigned char *palp, int size, int id);


};

#endif /* WIDGETS_H_ */
