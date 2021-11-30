/*
 * DataHub.cpp
 *
 *      Author: Andreas Volz
 */

// Local
#include <StatTxtTbl.h>
#include "DataHub.h"
#include "Hurricane.h"
#include "StringUtil.h"

// System
#include <iostream>
#include <fstream>
#include <string>


using namespace std;

DataHub::DataHub(std::shared_ptr<Hurricane> hurricane) :
	Converter(hurricane),
	mLogger("startool.DataHub")
{

}

DataHub::~DataHub()
{

}

std::shared_ptr<kaitai::kstream> DataHub::getKaitaiStream(const std::string &file)
{
	shared_ptr<DataChunk> data = mHurricane->extractDataChunk(file);
	if (data)
	{
		//std::ifstream ifs(arcfile, std::ifstream::binary);
		//kaitai::kstream ks(&ifs);

		// TODO: for now just create from complete string instead of istream. Maybe change the complete
		// reader to stream based concept...
		std::string str( reinterpret_cast<char const*>(data->getDataPointer()), data->getSize() ) ;
		shared_ptr<kaitai::kstream> ks = make_shared<kaitai::kstream>(str);
		return ks;
	}

	// TODO: hm, better create an exception
	return nullptr;
}

bool DataHub::convert(const std::string &arcfile, const std::string &file)
{
	string sc_arr_units_dat = "arr\\units.dat";
	string sc_arr_weapons_dat = "arr\\weapons.dat";
	string sc_arr_flingy_dat = "arr\\flingy.dat";
	string sc_rez_stat_txt_tbl ="rez\\stat_txt.tbl";

	// Units
	shared_ptr<kaitai::kstream> units_ks = getKaitaiStream(sc_arr_units_dat);
	units_dat_t units = units_dat_t(false, false, false, units_ks.get());
	std::vector<uint8_t>* graphics_vec = units.graphics();
	std::vector<uint8_t>* ground_weapon_vec = units.ground_weapon();
	std::vector<units_dat_t::staredit_group_flags_type_t*>* se_group_flags_vec = units.staredit_group_flags();

	// Weapons
	shared_ptr<kaitai::kstream> weapons_ks = getKaitaiStream(sc_arr_weapons_dat);
	// give 100 here, but more flexible would be to check what is biggest weapon id and give it here
	weapons_dat_t weapons = weapons_dat_t(100, weapons_ks.get());
	std::vector<uint16_t>* weapon_label_vec = weapons.label();
	std::vector<uint16_t>* weapon_error_message_vec = weapons.error_message();

	// Flingy
	shared_ptr<kaitai::kstream> flingy_ks = getKaitaiStream(sc_arr_flingy_dat);
	flingy_dat_t flingy = flingy_dat_t(false, false, flingy_ks.get());
	std::vector<uint16_t>* flingy_vec = flingy.sprite();

	// Stat Txt
	StatTxtTbl stat_txt;
	shared_ptr<kaitai::kstream> stat_txt_ks = getKaitaiStream(sc_rez_stat_txt_tbl);
	std::vector<TblEntry> stat_txt_vec = stat_txt.convertFromStream(stat_txt_ks);

	unsigned int i = 0;
	for(vector<TblEntry>::iterator it = stat_txt_vec.begin(); it != stat_txt_vec.end(); it++)
	{
		TblEntry tbl = *it;

		string err = "[" + toString(i) + ":";
		err += tbl.name + "," + tbl.category1 + "," + tbl.category2 + "]" + " sc=" + tbl.shortcut + " sc_pos:";
		cout << err << endl;

		i++;
	}

	// Loop over all units and linked properties from other files
	for(unsigned int i = 0; i < graphics_vec->size(); i++)
	{
		uint8_t graphic_id = graphics_vec->at(i);
		printf("[%d] graphicid=%d\t ", i, graphic_id);

		units_dat_t::staredit_group_flags_type_t *se_group_flags = se_group_flags_vec->at(i);
		bool zerg = se_group_flags->zerg();
		bool terran = se_group_flags->terran();
		bool protoss = se_group_flags->protoss();

		zerg ? printf("zerg") : false;
		terran ? printf("terran") : false;
		protoss ? printf("protoss") : false;

		printf("\t");

		TblEntry tblEntry = stat_txt_vec.at(i);
		cout << tblEntry.name;

		uint16_t sprite_id = flingy_vec->at(graphic_id);
		printf(" sprite:%d ", sprite_id);

		uint16_t weapon_id = ground_weapon_vec->at(i);
		printf("  weapon:%d ", weapon_id);

		cout << endl;
	}

	for(unsigned int i = 0; i < weapon_label_vec->size(); i++)
	{
		uint16_t label_id = weapon_label_vec->at(i);
		printf("[%d] weapon=%d\t", i, label_id);

		TblEntry tblEntry_label = stat_txt_vec.at(label_id);
		cout << " weapon=" << tblEntry_label.name;

		uint16_t error_id = weapon_error_message_vec->at(i);
		printf(" error=%d\t", error_id);

				TblEntry tblEntry_error = stat_txt_vec.at(error_id);
		cout << " error=" << tblEntry_error.name;

		cout << endl;
	}

	return true;
}
