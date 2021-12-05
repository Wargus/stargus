/*
 * DataHub.h
 *
 *      Author: Andreas Volz
 */

#ifndef DATAHUB_H_
#define DATAHUB_H_

// Local
#include "kaitai/kaitaistream.h"
#include "Logger.h"
#include "Converter.h"

class DataHub : public Converter
{
public:
	DataHub(std::shared_ptr<Hurricane> hurricane);
	virtual ~DataHub();

	virtual bool convert(const std::string &arcfile, const std::string &file);



private:
	Logger mLogger;

	std::shared_ptr<kaitai::kstream> getKaitaiStream(const std::string &file);

	static bool portdataCompare(int val1, int val2);

	void printCSV();
};

#endif /* DATAHUB_H_ */
