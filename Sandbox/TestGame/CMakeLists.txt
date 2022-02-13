cmake_minimum_required(VERSION 3.21)

add_executable(TestGame
	Src/TestGame.cpp
)

# target_precompile_headers(TestGame REUSE_FROM Core)
target_include_directories(TestGame PUBLIC /Src/)

message(STATUS "Suffix: ${CMAKE_EXECUTABLE_SUFFIX}")

target_link_libraries(TestGame PRIVATE
    Aphelion::Core
    Aphelion::Engine
    Aphelion::Window
)

setup_project(TestGame)
