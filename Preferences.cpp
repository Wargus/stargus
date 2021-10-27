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

