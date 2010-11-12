#
#    Makefile
#    Copyright (C) 2010  Pali Rohár <pali.rohar@gmail.com>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 2 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#

STRIP := strip
UPX := upx
WINDRES := windres
NSIS := makensis

CFLAGS := -O2 -W -Wall -fsigned-char
CXXFLAGS := $(CFLAGS) -Wno-write-strings
LDFLAGS :=
GTKFLAGS := $(shell pkg-config --cflags --libs gtk+-2.0)
UPXFLAGS := -9
NSISFLAGS :=

ARCH32 = -m32

all: startool stargus scmconvert

win32: startool.exe stargus.exe scmconvert.exe

clean:
	$(RM) startool startool.exe startool.o stargus stargus.exe starextract stargus.rc.o stargus.o mpq.o scm.o scm-s.o scmconvert scmconvert.exe

startool.o: startool.cpp
	$(CXX) -c $^ $(CXXFLAGS) $(ARCH32) -o $@

mpq.o: mpq.cpp
	$(CXX) -c $^ $(CXXFLAGS) $(ARCH32) -o $@

scm.o: scm.cpp
	$(CXX) -c $^ $(CXXFLAGS) $(ARCH32) -o $@

startool startool.exe: startool.o mpq.o scm.o
	$(CXX) $^ $(LDFLAGS) -lz -lpng $(ARCH32) -o $@

scm-s.o: scm.cpp
	$(CXX) -c $^ $(CXXFLAGS) $(ARCH32) -DSTAND_ALONE -o $@

scmconvert scmconvert.exe: mpq.o scm-s.o
	$(CXX) $^ $(LDFLAGS) $(ARCH32) -o $@

stargus: stargus.c
	$(CC) $^ $(GTKFLAGS) $(LDFLAGS) -o $@

%.rc.o: %.rc
	$(WINDRES) $^ -O coff -o $@

stargus.exe: stargus.o stargus.rc.o
	$(CC) $^ $(LDFLAGS) -mwindows -o $@

starextract: starextract.c
	$(CC) $^ $(CFLAGS) $(GTKFLAGS) $(LDFLAGS) -o $@

strip: startool stargus scmconvert
	$(STRIP) $^

win32-strip: startool.exe stargus.exe scmconvert.exe
	$(STRIP) $^

pack: startool stargus scmconvert
	$(UPX) $(UPXFLAGS) $^

win32-pack: startool.exe stargus.exe scmconvert.exe
	$(UPX) $(UPXFLAGS) $^

win32-installer: startool.exe stargus.exe scmconvert.exe stargus.nsi
	$(NSIS) $(NSISFLAGS) stargus.nsi
