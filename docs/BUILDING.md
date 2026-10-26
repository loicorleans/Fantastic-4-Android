# Building

This document is a starting point; exact build requirements can change as the project evolves. Follow the root `README.md`, `build.bat`, Gradle files, `CMakeLists.txt`, and `.github/workflows/build.yml` as the source of truth for the current build process.

## Requirements

- Windows environment for the repository's current `build.bat` workflow, or an environment compatible with the scripts and toolchain
- JDK 17 (the current GitHub Actions workflow uses Temurin 17)
- Android SDK, Android NDK `28.2.13676358`, and CMake `3.31.6` as specified by the current project configuration
- Git and network access to fetch project dependencies
- A legally obtained copy of the original game, supplied locally for analysis/building as required by the scripts

## Build notes

1. Clone or download the source repository.
2. Read the current workflow and build scripts before running them.
3. Keep original game files and generated/recompiled files out of the public source repository.
4. Run the project's documented analysis/build steps.
5. Save the build log and record the commit, device, and app version used for testing.
6. Install and test the resulting APK on a device; a successful compilation alone does not verify gameplay compatibility.

## GitHub Actions

The repository includes a manually triggered workflow under `.github/workflows/build.yml`. Inspect its current inputs and artifact names before using it. Do not commit game executables or disc images to a public repository. Encryption does not grant redistribution rights, and a private repository does not itself grant permission to distribute copyrighted material.

If you change the workflow to obtain local game files or secrets, keep them out of logs and artifacts, and review the security implications before enabling public contributions.
