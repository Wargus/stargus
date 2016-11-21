### Nightly builds are available:

- Windows Installer: https://github.com/Wargus/stargus/releases/tag/master-builds
- Ubuntu/Debian Packages: https://code.launchpad.net/~timfelgentreff/+archive/ubuntu/stratagus
- OS X App Bundle: https://github.com/Wargus/stratagus/wiki/osx/Stargus.app.tar.gz

Installation Instructions
=========================

NOTE: stratagus ( http://stratagus.org ) is required.
stargus and stratagus version must match

1. compile: mkdir build && cd build && cmake ../ && make

2. extract data: './startool /path/to/cd_or_install_dir /path/to/outputdir'
	eg:
	./startool d:/ data.sg
	./startool /cdrom data.sg

3. copy files:
	cp -r scripts data.sg
	cp contrib/fog.png data.sg/graphics/tilesets

4. start stratagus: '/path/to/stratagus -d /path/to/outputdir'
	eg:	
	./stratagus -d data.sg

![image](https://cloud.githubusercontent.com/assets/46235/11292960/499a7d3c-8f55-11e5-9356-62c190c57467.png)
![image](https://cloud.githubusercontent.com/assets/46235/11292993/9198675c-8f55-11e5-9f74-2f23fb207498.png)
![image](https://cloud.githubusercontent.com/assets/46235/11293018/cef6e970-8f55-11e5-8625-8bd13082b041.png)
