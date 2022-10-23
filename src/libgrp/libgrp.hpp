#ifndef libgrp_H
#define libgrp_H
/*! \mainpage General Information
 *  GRP Format Motivation
 *  =====================
 *  It was necessary to minimize memory use because we endeavored to make Blizzard games\n
 *  playable on low-spec systems. Consequently the GRP format needed to be highly compressed\n
 *  to maximize the number of frames we could fit in memory. - Patrick Wyatt
 *
 *  libgrp Motivation
 *  ================
 *  1. Extensive Documentation
 *  2. Cross Platform (Windows, Mac OSX, Linux)
 *  3. C++ (Use of OOP Techniques)\n
 *  While some libraries may offer 1 or 2 of these
 *  aspects, none were are to fulfill all of the requirments. This is
 *  not to imply that the implementation of any of these libraries were
 *  incorrect (in fact many techniques are pulled from them); the goal
 *  was to make the expirence easier to maintain and utilize in other applications.
 *
 *  CMake Build Options
 *  ===================
 *  There are three parameters that can be modified.\n
 *  1. VERBOSE - The amount of information outputted to the console
 *      while processing GRP files and ColorPalettes.\n
 *      DEFAULT = 0 Range = [1 - 5]\n
 *      To set add the cmake flag "-DVERBOSE=[DesiredValue]"\n\n
 *  2. UNITTESTS - Compile the Boost Unit tests inluded with libgrp.
 *      This will require that the Boost Library with the Unit Test Framework Module
 *      be compiled and installed.\n To enable unit tests
 *      Add the cmake flag "-DUNITTESTS=on"\n\n
 *  3. SAMPLECODE - To compile the sample code.\n
 *      Add the cmake flag "-DSAMPLECODE=on"\n
 *
 *  Sample Code
 *  ===========
 *  Sample code can be found from the root directory folder\n
 *  "SampleSource/"
 *
 *  Credits
 *  =======
 *  1. Bradley Clemetson\n
 *      @ http://codeprogrammers.net
 *  2. grplib Developers (botik32, infbonzay)\n
 *      @ http://sourceforge.net/projects/grplib/
 *  3. grpapi Developer (ShadowFlare)\n
 *      @ http://sfsrealm.hopto.org/
 *
 *  Special Thanks
 *  ==============
 *  1. Author of the GRP Format (Patrick Wyatt)\n
 *      @ http://www.codeofhonor.com/blog/
 */

#include "GRPImage/GRPImage.hpp"
#include "Exceptions/GRPImage/GRPImageException.hpp"

#include "GRPFrame/GRPFrame.hpp"
#include "Exceptions/GRPException.hpp"

#endif
