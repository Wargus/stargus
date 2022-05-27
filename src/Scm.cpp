//       _________ __                 __
//      /   _____//  |_____________ _/  |______     ____  __ __  ______
//      \_____  \\   __\_  __ \__  \\   __\__  \   / ___\|  |  \/  ___/
//      /        \|  |  |  | \// __ \|  |  / __ \_/ /_/  >  |  /\___ |
//     /_______  /|__|  |__|  (____  /__| (____  /\___  /|____//____  >
//             \/                  \/          \//_____/            \/
//  ______________________                           ______________________
//                        T H E   W A R   B E G I N S
//         Stratagus - A free fantasy real time strategy game engine
//
/**@name Scm.cpp - The scm. */
//
//      (c) Copyright 2002-2007 by Jimmy Salmon
//
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; version 2 dated June, 1991.
//
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//      02111-1307, USA.
//
//	$Id$
//@{
// Lcoal
#include "Scm.h"
#include "Chk.h"
#include "Hurricane.h"
#include "endian.h"
#include "FileUtil.h"
#include "Storm.h"
#include "platform.h"

// System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <string>

using namespace std;

Scm::Scm(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane)
{

}

Scm::~Scm()
{

}

bool Scm::convert(const std::string &arcfile, const std::vector<std::string> &unitNames, Storage storage)
{
  bool result = true;

  string scm_path = storage.getFullPath() + "scm";

  result = mHurricane->extractFile(arcfile, scm_path);
  if (result)
  {
    // call the Chk converter with temp file...
    shared_ptr<Storm> storm = make_shared<Storm>(scm_path);
    Chk chk(storm);
    chk.setUnitNames(unitNames);
    result = chk.convert("staredit\\scenario.chk", storage.getFullPath());

    // delete the temporary .chk file -> below don't access 'breeze' any more!
    platform::unlink(scm_path);
  }

  return result;
}
