cmake_minimum_required(VERSION 3.16)

add_executable(TestGame
	Src/TestGame.cpp
)

target_precompile_headers(TestGame REUSE_FROM Aphelion::Core)
target_include_directories(TestGame PUBLIC /Src/)

message(STATUS "Suffix: ${CMAKE_EXECUTABLE_SUFFIX}")

target_link_libraries(TestGame PRIVATE
    Aphelion::Core
    Aphelion::Engine
    Aphelion::Window
)

add_custom_command(TARGET TestGame POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:TestGame> $<TARGET_FILE_DIR:TestGame>
  COMMAND_EXPAND_LISTS
)
