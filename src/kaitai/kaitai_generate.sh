#!/bin/bash

## TODO: think about to generate this with build system on-the-fly.
## But for now we re-generate by need and commit the files to repo

kaitai-struct-compiler units_dat.ksy -t cpp_stl
