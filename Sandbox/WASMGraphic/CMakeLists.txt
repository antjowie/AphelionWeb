cmake_minimum_required(VERSION 3.18)

add_executable(WASMGraphic
    Src/Entry.cpp
    Src/Util.cpp
    Src/Util.cpp
)

target_include_directories(WASMGraphic PUBLIC /Src/)
message(STATUS "Suffix: ${CMAKE_EXECUTABLE_SUFFIX}")
# This command breaks IntelliSense on my installation so I guess I'll do without
# target_precompile_headers(WASMGraphic REUSE_FROM Aphelion::Core)

target_link_libraries(WASMGraphic PRIVATE
    Aphelion::Core
    Aphelion::Window
    Aphelion::Renderer
)