#!/bin/bash

## TODO: think about to generate this with build system on-the-fly.
## But for now we re-generate by need and commit the files to repo

kaitai-struct-compiler units_dat.ksy -t cpp_stl
kaitai-struct-compiler weapons_dat.ksy -t cpp_stl
kaitai-struct-compiler file_tbl.ksy -t cpp_stl
