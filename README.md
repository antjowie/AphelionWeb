# Aphelion Web [![Build](https://github.com/antjowie/AphelionWeb/actions/workflows/cmake.yml/badge.svg)](https://github.com/antjowie/AphelionWeb/actions/workflows/cmake.yml)

A game engine targeting the web (and desktop) using Emscripten.

> The current goal is to create a 2D multiplayer highscore game (such as Flappy bird).
## Building the project
I use CMake and am a firm believer that building a project should be as simple as possible:

```md
git clone https://github.com/antjowie/AphelionWeb
cd AphelionWeb
cmake -S . -B build
cmake --build build
```
### CMake options
| Option                 | Description                                             |
| ---------------------- | ------------------------------------------------------- |
| APHELION_HOT_RELOAD    | On Windows, add support for hot reloading. Disables PCH |
| APHELION_FORCE_ASSERTS | Include asserts even when building for release          |
| BUILD_SHARED_LIBS      | Build Aphelion as a shared lib, or a static lib         |
### Contributing to the project
> Requires Python

If you want to contribute to the project. Be sure to run `Script/DevelopmentSetup.bat`. This sets up tools such as pre-commit keeping the code base consistent.
### Targeting the web
> NOTE: Needs verification

You need to set up [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) first.

> TODO: I could also download Emscripten in the project which I may do. Setting it up takes a while though. I first have to figure out how to set the toolchain file. Task for future me
> Make sure Emscripten is in your PATH. Then do the following:

```md
git clone https://github.com/antjowie/AphelionWeb
cd AphelionWeb
emcmake cmake -S . -B build
cmake --build build
```

This will emit an `.html` in the binary directory. Serve this via a http server and you can test your project

```md
emrun yourAppName.html
```
