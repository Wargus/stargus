#!/bin/bash

# Stargus Install Script v0.3
# Made for Stargus 0.2 < http://stargus.sf.net >
# TODO: add auto dependancy installation
# TODO: add auto Stratagus update
# TODO: Add launch icon on desktop

if [ $1 = "--info" ]; then
	echo "This is automated install script for Stargus < http://stargus.sf.net >
	Default Install Dir: $HOME/.stargus
	Launch Script: /usr/bin/stargus"
	exit
fi

echo  "Welcome to the Stagus Installer"
echo "Introduction

	Stargus is a Starcraft Mod that allows you to play starcraft with the stratagus engine. Since Stargus uses a different engine, the game will not be an exact replica of the original Starcraft. If you want the original unchanged Starcraft experience, you will still have to run the original game.

Disclaimer

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# This program is free software; you can redistribute it and/or               #
# modify it under the terms of the GNU General Public License                 #
# as published by the Free Software Foundation; either version 2              #
# of the License, or (at your option) any later version.                      #
#                                                                             #
# This program is distributed in the hope that it will be useful,             #
# but WITHOUT ANY WARRANTY; without even the implied warranty of              #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the               #
# GNU General Public License for more details.                                #
#                                                                             #
# You should have received a copy of the GNU General Public License along     #
# with this program.  If not, see <http://www.gnu.org/licenses/>.             #
#                                                                             #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                                                                             #
# Stargus is not an official Blizzard product, it's a Starcraft modification, #
# by Starcraft fans for Starcraft fans. Starcraft is a registered trademark   #
# of Blizzard Entertainment.                                                  #
#                                                                             #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
"
echo "Press Enter to continue"
read Enter
clear 
echo "Dependencies:
	Stratagus (required) < http://www.stratagus.org/ >
	Lua (required) < http://www.lua.org/ >
	SDL (required) < http://www.libsdl.org/index.php > 
	libpng (required) < http://www.libpng.org >
	libogg/libvorbis (recommended) < http://www.xiph.org/vorbis/ >
	libmikmod (recommended) < http://mikmod.raphnet.net/ >
	libbzip2 (recommended) < http://www.bzip.org/ >

Do you have the above installed? y/n"
read dep_answer
if [ $dep_answer = "y" ]; then
	clear
	echo "what is the path to your cd drive?"
	echo "Example: /mnt/cdrom"
	read cddrive
	sudo eject $cddrive
	clear
	echo "please place your Starcraft Original cd into the cd drive"
	echo "press enter when ready"
	read Enter
	sudo mount $cddrive
	clear 
	echo "compiling stargus"
	sudo make
	mkdir $HOME/.stargus
	echo "Extracting Starcraft Data"
	./startool $cddrive $HOME/.stargus
	home=$HOME
	clear
	echo "Generating launch script"
	cp -r ./scripts $HOME/.stargus/
	cp ./contrib/fog.png $HOME/.stargus/graphics/tilesets/
	sudo echo "stratagus -d $home/.stargus/" > /usr/bin/stargus
	sudo chmod +x /usr/bin/stargus
	clear
	echo "Stargus installation complete"
	echo "to run stargus go to a shell and type "stargus" without the quotes"
	exit
fi
echo "please install the dependencies then re-run the installer"
exit



