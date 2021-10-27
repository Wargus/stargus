#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

/* STD */
#include <iostream>

#include "Preferences.h"

using namespace std;

Preferences& Preferences::getInstance()
{
  static Preferences instance;
  return instance;
}

void Preferences::init ()
{
	mVideoExtraction = false;
}

void Preferences::setVideoExtraction(bool video)
{
	mVideoExtraction = video;
}

bool Preferences::getVideoExtraction()
{
	return mVideoExtraction;
}

void Preferences::setArchiveDir(const std::string &dir)
{
	mArchiveDir = dir;
}

const std::string Preferences::getArchiveDir()
{
	return mArchiveDir;
}

void Preferences::setDataDir(const std::string &dir)
{
	mDataDir = dir;
}

const std::string Preferences::getDataDir()
{
	return mDataDir;
}
