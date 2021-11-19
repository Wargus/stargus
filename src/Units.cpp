/*
 * Units.cpp
 *
 *  Created on: 20.11.2021
 *      Author: andreas
 */

// Local
#include "Units.h"

// System
#include <iostream>
#include <fstream>

using namespace std;

Units::Units()
{

	std::ifstream ifs("/home/andreas/src/git/stargus/kaitai/units.dat", std::ifstream::binary);
	kaitai::kstream ks(&ifs);
	units_dat_t g = units_dat_t(&ks);

	std::vector<uint8_t>* gidvec = g.graphic_id();

	for(vector<uint8_t>::iterator git = gidvec->begin(); git != gidvec->end(); git++)
	{
		uint8_t gt = *git;
		printf("graphicid=%d\n", gt);
	}

}

Units::~Units()
{

}

