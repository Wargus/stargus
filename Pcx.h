/*
 * Pcx.h
 *
 *  Created on: 02.11.2021
 *      Author: Andreas Volz
 */

#ifndef PCX_H_
#define PCX_H_

void ConvertPcxToRaw(unsigned char *pcx, unsigned char **raw,
		unsigned char **pal, int *w, int *h);

#endif /* PCX_H_ */
