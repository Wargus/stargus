[![Join the chat at https://gitter.im/Wargus](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Wargus?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[![Discord](https://img.shields.io/discord/780082494447288340?style=flat-square&logo=discord&label=discord)](https://discord.gg/dQGxaw3QfB)

### Downloads

Every release of Stargus comes with a Windows installer, a macOS `dmg` and a
Linux AppImage:

- [Latest stable release](https://github.com/Wargus/stargus/releases/latest)
- [Latest unstable build](https://github.com/Wargus/stargus/releases/tag/master-builds) — rebuilt for every push to `master`, so it is the newest development build rather than a tested release

Older releases are in the [release list](https://github.com/Wargus/stargus/releases).

### Build status

- Windows: ![Build Status](https://github.com/Wargus/stargus/actions/workflows/windows.yml/badge.svg)
- Linux: ![Build Status](https://github.com/Wargus/stargus/actions/workflows/ubuntu.yml/badge.svg)
- macOS: ![Build Status](https://github.com/Wargus/stargus/actions/workflows/macos.yml/badge.svg)

The Windows workflow builds the installer, the Linux workflow the AppImage and
the macOS workflow the `dmg`; pushing a version tag creates the release with
those artifacts, and pushes to `master` update the `master-builds` release.
`RELEASING.md` describes how a release is made.

## Installation Instructions

Download the installer for your platform. Upon first launch of Stargus, it will ask you for
your Starcraft installation to extract the data to work with Stargus.

## Build Instructions

NOTE: stratagus ( https://github.com/Wargus/stratagus ) is required.
stargus and stratagus version must match

There are two build systems.

**meson is the development build**

```
meson build
ninja -C build
./stargus
```

Take a look into meson_options.txt for possible build options.

With meson you get the development extras: the data tools (iscript,
json_transition, grptool, sauwetter, scdat2json) and the cppunit test suite in
test/module.

**CMake is the release build**

CMake only builds stargus and startool two binaries, as well as the Windows
NSIS installer.

- `third-party/` is shared and with CMake, png, zlib, bzip2 and StormLib
  come from there
- `subprojects/` are managed by meson, but the inlined stuff is consumed by CMake
  as well
- Meson does not use `third-party/`

![image](https://cloud.githubusercontent.com/assets/46235/11292960/499a7d3c-8f55-11e5-9356-62c190c57467.png)
![image](https://cloud.githubusercontent.com/assets/46235/11292993/9198675c-8f55-11e5-9f74-2f23fb207498.png)
![image](https://cloud.githubusercontent.com/assets/46235/11293018/cef6e970-8f55-11e5-8625-8bd13082b041.png)
