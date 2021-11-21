/*
 * Weapons.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Weapons.h"
#include "kaitai/weapons_dat.h"

// System
#include "Hurricane.h"

using namespace std;

Weapons::Weapons(std::shared_ptr<Hurricane> hurricane) :
	Converter(hurricane)
{

}

Weapons::~Weapons()
{

}

bool Weapons::convert(const std::string &arcfile, const std::string &file)
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

		weapons_dat_t g = weapons_dat_t(&ks);

		std::vector<uint16_t>* gidvec = g.weapon_label();

		for(vector<uint16_t>::iterator git = gidvec->begin(); git != gidvec->end(); git++)
		{
			uint8_t gt = *git;
			printf("weapon_label=%d\n", gt);
		}
	}


	return true;
}
