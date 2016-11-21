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

```
mkdir build
cd build
cmake -DSTRATAGUS=stratagus -DSTRATAGUS_INCLUDE_DIR=${PATH_TO_STRATAGUS_SRC}/gameheaders ../
make
./stargus
```

![image](https://cloud.githubusercontent.com/assets/46235/11292960/499a7d3c-8f55-11e5-9356-62c190c57467.png)
![image](https://cloud.githubusercontent.com/assets/46235/11292993/9198675c-8f55-11e5-9f74-2f23fb207498.png)
![image](https://cloud.githubusercontent.com/assets/46235/11293018/cef6e970-8f55-11e5-8625-8bd13082b041.png)
