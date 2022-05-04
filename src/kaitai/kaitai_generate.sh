#!/bin/bash

KSY_FILES="units_dat weapons_dat file_tbl flingy_dat sprites_dat images_dat sfxdata_dat portdata_dat upgrades_dat orders_dat techdata_dat mapdata_dat"

## where to store the docs
mkdir -p ../../doc/kaitai

echo "Clean old generated source files..."
for item in $KSY_FILES
do
  rm -f $item.cpp $item.h
  KSY=$item.ksy
  DOT=$item.dot
  SVG=$item.svg
  echo "Generating source and documentation from: $KSY"
  kaitai-struct-compiler $KSY -t cpp_stl
  kaitai-struct-compiler $KSY -t graphviz
  dot $DOT -Tsvg > ../../doc/kaitai/$SVG
done

