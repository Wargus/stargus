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

CC = gcc
CXX = g++
WINDRES = windres

CFLAGS = -O2 -W -Wall -fsigned-char
CXXFLAGS = $(CFLAGS) -Wno-write-strings -m32
LDFLAGS = -lz -lpng -lm -m32
GTKFLAGS = $(shell pkg-config --cflags --libs gtk+-2.0)

all: startool stargus

win32: startool.exe stargus.exe

clean:
	rm -rf startool startool.exe startool.o stargus stargus.exe stargus.rc.o stargus.o mpq.o scm.o

startool startool.exe: startool.o mpq.o scm.o
	$(CXX) $^ $(LDFLAGS) -o $@

stargus: stargus.c
	$(CC) $^ $(GTKFLAGS) -o $@

%.rc.o: %.rc
	$(WINDRES) $^ -O coff -o $@

stargus.exe: stargus.o stargus.rc.o
	$(CC) $^ -mwindows -o $@
