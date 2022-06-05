#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// System


// Project
#include "PcxTest.h"
#include "platform.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(PcxTest);

void PcxTest::setUp()
{

}

void PcxTest::tearDown()
{

}

void PcxTest::test1_SaveIndexedPalettePNG()
{
  string test_data_dir = "test/module/data/";
  string load_pcx_name = "PcxTest_red_zergb.pcx";
  string save_pal_name = "red_zergb.pal";
  string save_png_name = "red_zergb.png";

  shared_ptr<Breeze> breeze = make_shared<Breeze>(test_data_dir);

  Pcx pcx1(breeze, load_pcx_name);
  pcx1.savePNG(save_png_name);
  std::shared_ptr<Palette> pal = pcx1.getPalette();
  pal->createDataChunk()->write(save_pal_name);

  CPPUNIT_ASSERT(compareFiles(save_pal_name, test_data_dir + "/PcxTest_" + save_pal_name));
  CPPUNIT_ASSERT(compareFiles(save_png_name, test_data_dir + "/PcxTest_" + save_png_name));

  fs::remove(save_pal_name.c_str());
  fs::remove(save_png_name.c_str());
}

void PcxTest::test2_mapIndexPalette()
{
  string test_data_dir = "test/module/data/";
  string load_pcx_name = "PcxTest_ticon.pcx";


  shared_ptr<Breeze> breeze = make_shared<Breeze>(test_data_dir);

  Pcx pcx1(breeze);

  for(unsigned int index = 0; index < 6; index++)
  {
    string save_pal_name = string("ticon_") + to_string(index) + ".pal";
    string save_png_name = string("ticon_") + to_string(index) + ".png";

    pcx1.load(load_pcx_name);
    pcx1.mapIndexPalette(8, 1, index);
    pcx1.savePNG(save_png_name);
    std::shared_ptr<Palette> pal = pcx1.getPalette();
    pal->createDataChunk()->write(save_pal_name);

    CPPUNIT_ASSERT(compareFiles(save_pal_name, test_data_dir + "/PcxTest_" + save_pal_name));
    CPPUNIT_ASSERT(compareFiles(save_png_name, test_data_dir + "/PcxTest_" + save_png_name));

    fs::remove(save_pal_name.c_str());
    fs::remove(save_png_name.c_str());
  }
}

