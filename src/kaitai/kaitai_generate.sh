#!/bin/bash

KSY_FILES="units_dat weapons_dat file_tbl flingy_dat sprites_dat images_dat sfxdata_dat"

echo "Clean old generated source files..."
for item in $KSY_FILES
do
  rm -f $item.cpp $item.h
  KSY=$item.ksy
  echo "Generating source from: $KSY"
  kaitai-struct-compiler $KSY -t cpp_stl
done

