# Fantastic Four for Android

An independent Android porting project for the original Xbox version of *Fantastic Four* (Activision; title ID `4156001A`, XDK 5849).

The project recompiles Xbox x86 code to C++ using [XboxXBE-Recomp](https://github.com/TGP482/XboxXBE-Recomp) and targets Android ARM64, with a Vulkan renderer and SDL3-based host. This repository contains project code and tooling; it does not include the original game executable, disc image, or game assets.

> **Development status: playable, but experimental.** The game has been launched and played on an Android device, including a MediaTek Helio G80 device. Full-game completion testing has not been completed, and frame-rate stability/performance optimization remain ongoing. Results may differ by device and game scene.

## Current status

- [x] Game launches and can be played on a tested Android device
- [x] Android ARM64 target
- [x] Vulkan-based rendering path
- [ ] Complete playthrough from beginning to ending
- [ ] Verify all missions, transitions, and save/load behavior
- [ ] Establish repeatable FPS and frame-time measurements
- [ ] Improve frame pacing and performance on lower/mid-range devices
- [ ] Test compatibility across more Android devices

Items above describe the current development status and are not a guarantee that every feature works correctly.

## Requirements

- Android 10 (API 29) or later, subject to the current app configuration
- ARM64 (`arm64-v8a`) device
- A legally obtained copy of the original game, provided by the user
- For development/building: a compatible JDK, Android SDK/NDK, CMake, Gradle, and the dependencies documented by the project

The MediaTek Helio G80 is one of the current test targets. Its performance has not yet been fully characterized with repeatable benchmark measurements.

## Using the app

The app expects the user to supply their own game files. Follow the in-app importer/instructions and use the game's own legally obtained disc image or extracted files in the format supported by the current build. Do not download game files from this repository or from untrusted sources.

## Building

Build scripts and GitHub Actions are provided as development aids. See [`docs/BUILDING.md`](docs/BUILDING.md) before starting a build. A successful build does not by itself mean the game is fully compatible or stable during gameplay.

## Performance and compatibility

See:

- [`docs/COMPATIBILITY.md`](docs/COMPATIBILITY.md) for device and Android test results
- [`docs/PERFORMANCE.md`](docs/PERFORMANCE.md) for FPS/frame-time measurements
- [`docs/KNOWN_ISSUES.md`](docs/KNOWN_ISSUES.md) for current limitations
- [`docs/TESTING.md`](docs/TESTING.md) for a repeatable test checklist

Only add measured values to these documents. Do not report an FPS target as achieved unless it has been measured during a repeatable test.

## Contributing

Bug reports and technical contributions are welcome. Please include device model, Android version, the game scene/mission, reproduction steps, and logs where possible. See [`CONTRIBUTING.md`](CONTRIBUTING.md).

## Credits and third-party software

The Android host is based on work from [Black-Android](https://github.com/RanggaCasper/Black-Android) and the [Shaolin Monks for Android](https://github.com/RanggaCasper/ShaolinMonks-Android) project. Xbox recompilation/runtime support is provided by [XboxXBE-Recomp](https://github.com/TGP482/XboxXBE-Recomp). The project also uses SDL and other third-party components; see [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md) and the bundled `sdk/` notices for details.

## Legal notice

This is an independent, unofficial project and is not affiliated with, endorsed by, or sponsored by the original game's publisher or rights holders. *Fantastic Four*, related characters, and game assets belong to their respective rights holders. This repository does not grant permission to redistribute the original game or its assets. Users are responsible for complying with applicable law and third-party licenses.
