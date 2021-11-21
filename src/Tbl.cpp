/*
 * Tbl.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include "Tbl.h"
#include "Hurricane.h"

// System
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Tbl::Tbl(std::shared_ptr<Hurricane> hurricane) :
	Converter(hurricane),
	mLogger("startool.Tbl")
{

}

Tbl::~Tbl()
{

}

bool Tbl::convert(const std::string &arcfile, const std::string &file)
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

		file_tbl_t g = file_tbl_t(&ks);

		std::vector<file_tbl_t::tbl_entry_t*>* gidvec = g.tbl_entries();

		for(vector<file_tbl_t::tbl_entry_t*>::iterator git = gidvec->begin(); git != gidvec->end(); git++)
		{
			file_tbl_t::tbl_entry_t *gt = *git;

			cout << "entry: " << gt->entry() << endl;

		//	printf("graphicid=%d\n", gt);
		}
	}


	return true;
}
