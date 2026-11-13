# Releasing Stargus

Stargus is released in lockstep with the Stratagus engine: a release of version
`X.Y.Z` is tagged `vX.Y.Z` here and in
[`Wargus/stratagus`](https://github.com/Wargus/stratagus), and the workflows
here build against the engine tag with the matching name, falling back to the
engine `master` branch when there is no such tag. Tag the engine first, so that
the artifacts built here are built against the engine that is being released.
See `RELEASING.md` in the engine repository for the engine part of the release,
including its documentation and changelog.

## Release artifacts

| artifact | workflow |
| --- | --- |
| Windows installer | [`windows.yml`](.github/workflows/windows.yml) |
| macOS `dmg` | [`macos.yml`](.github/workflows/macos.yml) |
| Linux AppImage | [`ubuntu.yml`](.github/workflows/ubuntu.yml) |

A push to `master`, a tag, a manual "Run workflow", or a push to the engine
`master` (which announces it with the "Downstream builds" workflow of
[`Wargus/stratagus`](https://github.com/Wargus/stratagus)) makes all three
build, and
the Launchpad packages and the `release.py` version bumper they came with are
gone. Each of the three workflows uploads its artifact to the release for the
tag it ran for, creating that release if none of them has yet, and pushes to
`master` upload to the [master-builds
release](https://github.com/Wargus/stargus/releases/tag/master-builds) instead.

The Windows and Linux artifacts are built with CMake rather than meson, as it
is the build system that takes its libraries from `third-party/`, which is what
makes the bundle independent of whatever happens to be installed on the build
host. The AppImage can be built locally the same way the Linux workflow does:

```sh
git clone --recursive https://github.com/Wargus/stratagus ../stratagus
tools/build_appimage.sh ../stratagus
```

## Tagging a release

`X.Y.Z` below is the version being released, and `vX.Y.Z` the tag.

1. Increase the version in:

   | file | |
   | --- | --- |
   | `scripts/stratagus.lua` | `stargus.Version`, which the game shows in the UI |
   | `stargus.nsi` | `VERSION` of the installer, and its `COPYRIGHT` years |
   | `stargus.rc` | `VERSION`, and `VIVERSION` of the same version with commas |
   | `src/startool.h` | `VERSION` of the extractor tool, and the years in its usage text |
   | `mac/Info.plist` | `CFBundleShortVersionString` of the app bundle |

2. Write the release notes in `doc/changelog`.

3. Add the changelog entry for the new version with `dch -v X.Y.Z-1` and close
   it with `dch -r`; move the years in `debian/copyright` if needed. Note that
   this changelog has not been kept up to date in the past, so it may need
   catching up rather than a single new entry.

4. Commit and merge to `master`: `git commit -a -m "Release version X.Y.Z"`.

5. Once the engine has been tagged `vX.Y.Z`, tag and push here. The three
   workflows then build the artifacts and put them on the release.

   ```sh
   git tag vX.Y.Z
   git push origin master --tags
   ```

   With the artifacts up, write the notes for the release, e.g. with
   `gh release edit vX.Y.Z --verify-tag --notes-file notes.md`.

6. Update the download links for the stable versions in the website repository.
