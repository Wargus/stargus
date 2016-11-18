#!/bin/bash

if [ -z "$STRATAGUS" ]; then
    echo "You must tell me where the stratagus binary is located by setting the STRATAGUS variable!"
    exit 1
fi

STRATAGUS="$(cd "$(dirname "$STRATAGUS")" && pwd -P)/$(basename $STRATAGUS)"

cd "`dirname "$0"`"

# Create app bundle structure
rm -rf Stargus.app
mkdir -p Stargus.app/Contents/Resources
mkdir -p Stargus.app/Contents/MacOS
mkdir -p Stargus.app/Contents/libs

# Copy launchscript and info.plist
cp Info.plist Stargus.app/Contents/

# Generate icons
mkdir stargus.iconset
sips -z 16 16     ../stargus.png --out stargus.iconset/icon_16x16.png
sips -z 32 32     ../stargus.png --out stargus.iconset/icon_16x16@2x.png
sips -z 32 32     ../stargus.png --out stargus.iconset/icon_32x32.png
sips -z 64 64     ../stargus.png --out stargus.iconset/icon_32x32@2x.png
sips -z 128 128   ../stargus.png --out stargus.iconset/icon_128x128.png
sips -z 256 256   ../stargus.png --out stargus.iconset/icon_128x128@2x.png
sips -z 256 256   ../stargus.png --out stargus.iconset/icon_256x256.png
sips -z 512 512   ../stargus.png --out stargus.iconset/icon_256x256@2x.png
sips -z 512 512   ../stargus.png --out stargus.iconset/icon_512x512.png
sips -z 1024 1024   ../stargus.png --out stargus.iconset/icon_512x512@2x.png
iconutil -c icns stargus.iconset
rm -R stargus.iconset
mv stargus.icns Stargus.app/Contents/Resources/

# Bundle resources
cp -R ../contrib ../scripts Stargus.app/Contents/MacOS/
cp -R ../scripts ../scripts Stargus.app/Contents/MacOS/
cp -R ../mpqlist.txt ../scripts Stargus.app/Contents/MacOS/

# Bundle binaries and their dependencies
rm -rf macdylibbundler
git clone https://github.com/auriamg/macdylibbundler
cd macdylibbundler
make
cd ..

cp ../build/startool Stargus.app/Contents/MacOS/
cp ../build/stargus Stargus.app/Contents/MacOS/
cp "$STRATAGUS" Stargus.app/Contents/MacOS/stratagus
cp "$(dirname "$STRATAGUS")"/../libs/* Stargus.app/Contents/libs/

macdylibbundler/dylibbundler -cd -of -b -x ./Stargus.app/Contents/MacOS/startool -d ./Stargus.app/Contents/libs/
macdylibbundler/dylibbundler -cd -of -b -x ./Stargus.app/Contents/MacOS/stargus -d ./Stargus.app/Contents/libs/
