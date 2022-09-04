/*
 * DatTest.cpp
 *
 *      Author: Andreas Volz
 */

// project
#include "dat/DataHub.h"
#include "dat/CSVExporter.h"
#include "Breeze.h"
#include "FileUtil.h"
#include "Logger.h"

// system

using namespace std;

static Logger logger("startool.DatTest");

int main(int argc, char **argv)
{
#ifdef HAVE_LOG4CXX
  if (FileExists("logging.prop"))
  {
    log4cxx::PropertyConfigurator::configure("logging.prop");
  }
  else
  {
    logger.off();
  }
#endif // HAVE_LOG4CXX

  shared_ptr<Breeze> storm = make_shared<Breeze>("/home/andreas/Downloads/Games/DOS/Starcraft/Original_Backup/starcraft_install.exe_MPQ_stardat.mpq/");
  //shared_ptr<Breeze> storm = make_shared<Breeze>("/home/andreas/Downloads/Games/DOS/Starcraft/Original_Backup/broodwar_install.exe_MPQ_broodat.mpq/");
  dat::DataHub datahub(storm);

  dat::CSVExporter csvexporter(datahub);

  csvexporter.print();

  return 0;
}

