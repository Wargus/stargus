/*
 * Units.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Units.h"
#include "Hurricane.h"

// System
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Units::Units(std::shared_ptr<Hurricane> hurricane) :
	Converter(hurricane),
	mLogger("startool.Units")
{



}

Units::~Units()
{

}

bool Units::convert(const std::string &arcfile, const std::string &file)
{
	shared_ptr<DataChunk> data = mHurricane->extractDataChunk(arcfile);
	if (data)
	{
		//std::ifstream ifs(arcfile, std::ifstream::binary);
		//kaitai::kstream ks(&ifs);

		// TODO: for now just create from complete string instead of istream. Maybe change the complete
		// reader to stream based concept...
		std::string str( reinterpret_cast<char const*>(data->getDataPointer()), data->getSize() ) ;
		kaitai::kstream ks(str);

		units_dat_t unit = units_dat_t(false, false, false, &ks);

		std::vector<uint8_t>* gidvec = unit.graphics();

		for(vector<uint8_t>::iterator git = gidvec->begin(); git != gidvec->end(); git++)
		{
			uint8_t gt = *git;
			printf("graphicid=%d\n", gt);
		}
	}


	return true;
}
