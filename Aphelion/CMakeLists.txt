cmake_minimum_required(VERSION 3.18)

set(CMAKE_FOLDER Aphelion)

# Setup emscripten compiler if we compile to WASM
message(STATUS "Aphelion targeting system ${CMAKE_SYSTEM_NAME}")
# if($<PLATFORM_ID:Emscripten>)
if(CMAKE_SYSTEM_NAME STREQUAL Emscripten)
    message(STATUS "Setting up Emscripten")
    # TODO: Figure out a way to set variable globally. Cache doesn't seem to work
    # This won't work is Aphelion is used as a dependency of a dependency
    set(CMAKE_EXECUTABLE_SUFFIX ".html" PARENT_SCOPE)
    set_property(GLOBAL PROPERTY LINK_OPTIONS "-s WASM=1")
endif()

add_subdirectory(Src/Aphelion/Core)
add_subdirectory(Src/Aphelion/Renderer)