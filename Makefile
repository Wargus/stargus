
CC = g++

CROSSDIR = /usr/local/cross
STRATAGUSPATH = ../stratagus/

CFLAGS = -I/usr/local/include -Wall -Wsign-compare
LDFLAGS = -lz -lpng -lm -L/usr/local/lib

all: cleanobj startool

startool: startool.o mpq.o
	$(CC) -o $@ $^ $(LDFLAGS)

cleanobj:
	rm -f startool.o mpq.o

clean:
	rm -rf startool startool.exe startool.o data.wc2 stargus-* stargus

strip:
	strip startool
#	strip startool.exe

date = $(shell date +%y%m%d)
ver = 2.1pre2

release: release-src release-linux

release-src: clean cleanobj
	echo `find Makefile build.* contrib campaigns startool.c startool.ds* scripts maps | grep -v 'CVS' | grep -v '/\.'` > .list
	mkdir stargus-$(ver); \
	for i in `cat .list`; do echo $$i; done | cpio -pdml --quiet stargus-$(ver);\
	rm -rf `find stargus-$(ver) | grep -i cvs`; \
	tar -zcf stargus-$(ver)-src.tar.gz stargus-$(ver); \
	zip -qr stargus-$(ver)-src.zip stargus-$(ver); \
	rm -rf stargus-$(ver) .list;

release-linux: clean startool strip cleanobj
	pwd
	cp -f $(STRATAGUSPATH)stratagus .
	echo `find Makefile build.sh contrib campaigns startool scripts maps stratagus | grep -v 'CVS' | grep -v '/\.'` > .list
	mkdir stargus-$(ver); \
	for i in `cat .list`; do echo $$i; done | cpio -pdml --quiet stargus-$(ver);\
	rm -rf `find stargus-$(ver) | grep -i cvs`; \
	tar -zcf stargus-$(ver)-linux.tar.gz stargus-$(ver); \
	rm -rf stargus-$(ver) .list stratagus;
