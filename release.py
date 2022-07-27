#!/usr/bin/env ruby

import atexit
import os
import pprint
import sys


STRINGS = {
  "version": "3.3.0",
  "homepage": "https://github.com/wargus/stargus",
  "license": "GPL v2",
  "copyright": "(c) 2002-2022 by the Stratagus Project",
}


FILES = [
    "src/startool.h",
    "stargus.rc",
    "stargus.nsi",
    "mac/Info.plist",
    "scripts/stratagus.lua",
    "debian/copyright",
    __file__
]


updates = []


for arg in sys.argv[1:]:
    if arg.startswith("--"):
      updates.append(arg.replace("--", ""))
    else:
      updates[-1] = (updates[-1], arg)


updates = dict(updates)


if not updates:
  print('You can update the following STRINGS by passing --key "new-value"')
  pprint.pprint(STRINGS)
  exit()


if updates.get("version"):
  STRINGS["viversion"] = STRINGS["version"].replace(".", ",")
  updates["viversion"] = updates["version"].replace(".", ",")


for filename in FILES:
    with open(filename, "r") as f:
        content = f.read()
    for k,v in updates.items():
        content = content.replace(STRINGS[k], v)
    with open(filename, "w") as f:
        f.write(content)


if updates.get("version"):
    cmds = [
        f'dch -v{updates["version"]}-1',
        "gbp dch",
        "dch -r",
        "git add --patch",
        f'git commit -m "Release {updates["version"]}"',
        f'git tag v{updates["version"]}'
    ]
    idx = 0

    @atexit.register
    def atexit_func():
        if idx < len(cmds):
            print("Not running the following commands:", "\n".join(cmds[idx:]))

    for cmd in cmds:
        print(f"Running {cmd} (abort by interrupting the process)")
        input()
        os.system(cmd)
        idx += 1
