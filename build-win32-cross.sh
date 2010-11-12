#!/bin/sh
make clean
make startool.exe scmconvert.exe CC=i686-w64-mingw32-gcc CXX=i686-w64-mingw32-g++ ARCH32="" LDFLAGS+=-static
i686-w64-mingw32-strip startool.exe scmconvert.exe
make stargus.exe CC=x86_64-w64-mingw32-gcc CXX=x86_64-w64-mingw32-g++ WINDRES=x86_64-w64-mingw32-windres ARCH32="" LDFLAGS+=-static
x86_64-w64-mingw32-strip stargus.exe
make win32-installer NSISFLAGS=-DAMD64
make clean win32 win32-strip win32-pack win32-installer CC=i686-w64-mingw32-gcc CXX=i686-w64-mingw32-g++ WINDRES=i686-w64-mingw32-windres STRIP=i686-w64-mingw32-strip LDFLAGS+=-static
