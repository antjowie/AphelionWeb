cmake_minimum_required(VERSION 3.18)

add_library(Window
    Window.hpp

    $<$<PLATFORM_ID:Emscripten>:
        Platform/Web/WebWindow.cpp
        Platform/Web/WebWindow.hpp
    >
)

add_library(Aphelion::Window ALIAS Window)
target_include_directories(Window PRIVATE ./)
target_link_libraries(Window PUBLIC Aphelion::Core)
