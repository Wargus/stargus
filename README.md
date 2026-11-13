[![Join the chat at https://gitter.im/Wargus](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/Wargus?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[![Discord](https://img.shields.io/discord/780082494447288340?style=flat-square&logo=discord&label=discord)](https://discord.gg/dQGxaw3QfB)

### Nightly builds are available:

- Windows Installer: https://github.com/Wargus/stargus/releases/tag/master-builds
- Ubuntu/Debian Packages: https://code.launchpad.net/~timfelgentreff/+archive/ubuntu/stratagus
- OS X App Bundle: https://github.com/Wargus/stratagus/wiki/osx/Stargus.app.tar.gz

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
