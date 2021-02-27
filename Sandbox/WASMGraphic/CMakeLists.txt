cmake_minimum_required(VERSION 3.18)

add_executable(WASMGraphic
    Src/Entry.cpp
)

target_include_directories(WASMGraphic PUBLIC /Src/)

# target_precompile_headers(WASMGraphic REUSE_FROM Aphelion::Core)

target_link_libraries(WASMGraphic PRIVATE
    Aphelion::Core
)