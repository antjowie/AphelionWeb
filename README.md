# Aphelion Web
A multimedia library targeting the web (and desktop) using Emscripten. My goal is to create a simple 2D game (such as Flappy bird) in C++.
After that, I also want to have it networked so that you can play it with friends. 

By making this, I want to learn about: 
- Utilizing the CMake build system to actually target multiple platforms.
- Learning about desiging systems to support multiple platforms. The web comes with it's own limitations
- Gaining experience to create cross platform applications. 
- Using networking to create a battle royale type game (not shooter, more tetris like).

I want to create this project since being able to have your C++ code run on the browser seemed like a really cool thing to me. I also want to learn a bit more about networking, so making a very simple game with an additional focus on the networking is sure to have some interesting challenges.

## Building the project
I use CMake as a build system and made sure to make building the project as simple as possible meaning:
```md 
git clone https://github.com/antjowie/AphelionWeb
cd AphelionWeb
cmake -S . -B build
cmake --build build
```
Depending on your CMake Generator this is supposed to compile for every desktop platform. I only implemented and tested Windows though. If you want to target the web however. Addition steps need to be taken.

### Targetting the web
You need to set up [Emscripten](https://emscripten.org/docs/getting_started/downloads.html) first.
> TODO: I could also download Emscripten in the project which I may do. Setting it up takes a while though. I first have to figure out how to set the toolchain file. Task for future me
Make sure Emscripten is in your PATH. Then do the following:
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

## Setting up local environment
Personally, I use VSCode to work on this project. Visual Studio IntelliSense for some reason fails and doesnt wan't to use the compile_commands.json. I use the [C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) and [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) extension. 

To set up CMake Tools do the following:
```md
execute command: CMake:Edit user-local CMake kit.
Add the following:
{
    "name": "Emscripten",
    "toolchainFile": "`Path\\To\\emsdk`\\emsdk\\upstream\\emscripten\\cmake\\Modules\\Platform\\Emscripten.cmake"
},
```
Then you can select that kit, giving you IntelliSense support.