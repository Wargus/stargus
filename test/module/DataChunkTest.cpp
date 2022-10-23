#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

// System


// Project
#include "DataChunkTest.h"
#include "platform.h"

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(DataChunkTest);

void DataChunkTest::setUp()
{

}

void DataChunkTest::tearDown()
{

}

void DataChunkTest::test1_addData()
{
  DataChunk dc;
  int LENGTH = 5;

  unsigned char rawdata[LENGTH];
  rawdata[0] = 0x1;
  rawdata[1] = 0x2;
  rawdata[2] = 0x3;
  rawdata[3] = 0x4;
  rawdata[4] = 0x5;

  dc.addData(rawdata, LENGTH);

  CPPUNIT_ASSERT(dc.at(0) == 0x1);
  CPPUNIT_ASSERT(dc.at(1) == 0x2);
  CPPUNIT_ASSERT(dc.at(2) == 0x3);
  CPPUNIT_ASSERT(dc.at(3) == 0x4);
  CPPUNIT_ASSERT(dc.at(4) == 0x5);
}

void DataChunkTest::test2_createFromExistingHeap()
{
  int LENGTH = 5;

  unsigned char *rawdata = new unsigned char(LENGTH);
  rawdata[0] = 0x1;
  rawdata[1] = 0x2;
  rawdata[2] = 0x3;
  rawdata[3] = 0x4;
  rawdata[4] = 0x5;

  DataChunk dc(&rawdata, LENGTH);

  unsigned char *retdata = dc.getDataPointer();

  CPPUNIT_ASSERT(retdata[0] == 0x1);
  CPPUNIT_ASSERT(retdata[1] == 0x2);
  CPPUNIT_ASSERT(retdata[2] == 0x3);
  CPPUNIT_ASSERT(retdata[3] == 0x4);
  CPPUNIT_ASSERT(retdata[4] == 0x5);
}

void DataChunkTest::test3_vectorReturn()
{
  DataChunk dc;
  int LENGTH = 5;

  unsigned char rawdata[LENGTH];
  rawdata[0] = 0x1;
  rawdata[1] = 0x2;
  rawdata[2] = 0x3;
  rawdata[3] = 0x4;
  rawdata[4] = 0x5;

  dc.addData(rawdata, LENGTH);

  std::vector<unsigned char> datavec = dc.getUCharVector();

  CPPUNIT_ASSERT(datavec.at(0) == 0x1);
  CPPUNIT_ASSERT(datavec.at(1) == 0x2);
  CPPUNIT_ASSERT(datavec.at(2) == 0x3);
  CPPUNIT_ASSERT(datavec.at(3) == 0x4);
  CPPUNIT_ASSERT(datavec.at(4) == 0x5);
}

void DataChunkTest::test4_write_compare()
{
  DataChunk dc;
  int LENGTH = 5;
  string savename = "datachunk.txt";

  unsigned char rawdata[LENGTH];
  rawdata[0] = 0x1;
  rawdata[1] = 0x2;
  rawdata[2] = 0x3;
  rawdata[3] = 0x4;
  rawdata[4] = 0x5;

  dc.addData(rawdata, LENGTH);

  dc.write(savename);

  string line;
  string filecontent;
  ifstream readfile(savename);
  if (readfile.is_open())
  {
    while (getline(readfile, line))
    {
      filecontent += line;
    }
    readfile.close();
  }

  CPPUNIT_ASSERT(filecontent.at(0) == 0x1);
  CPPUNIT_ASSERT(filecontent.at(1) == 0x2);
  CPPUNIT_ASSERT(filecontent.at(2) == 0x3);
  CPPUNIT_ASSERT(filecontent.at(3) == 0x4);
  CPPUNIT_ASSERT(filecontent.at(4) == 0x5);

  fs::remove(savename);
}

void DataChunkTest::test5_read_write_compare()
{
  DataChunk dc;
  int LENGTH = 5;
  string savename = "datachunk.txt";

  unsigned char rawdata[LENGTH];
  rawdata[0] = 0x1;
  rawdata[1] = 0x2;
  rawdata[2] = 0x3;
  rawdata[3] = 0x4;
  rawdata[4] = 0x5;

  dc.addData(rawdata, LENGTH);

  dc.write(savename);

  string line;
  string filecontent;

  DataChunk dc_read;
  dc_read.read(savename);

  CPPUNIT_ASSERT(dc_read.at(0) == rawdata[0]);
  CPPUNIT_ASSERT(dc_read.at(1) == rawdata[1]);
  CPPUNIT_ASSERT(dc_read.at(2) == rawdata[2]);
  CPPUNIT_ASSERT(dc_read.at(3) == rawdata[3]);
  CPPUNIT_ASSERT(dc_read.at(4) == rawdata[4]);

  fs::remove(savename);
}
