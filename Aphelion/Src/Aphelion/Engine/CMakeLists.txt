cmake_minimum_required(VERSION 3.18)

add_library(Engine
    $<$<PLATFORM_ID:Windows,Linux>:
        Platform/Desktop/DesktopEngine.cpp
    >

    $<$<PLATFORM_ID:Emscripten>:
        Platform/Web/WebEngine.cpp
    >

    Engine.cpp
    Engine.h
)
add_library(Aphelion::Engine ALIAS Engine)

target_precompile_headers(Engine PRIVATE ${APHELION_PCH})

target_link_libraries(Engine
PUBLIC
    Aphelion::Core
    Aphelion::Window
    Aphelion::ImGui
)
