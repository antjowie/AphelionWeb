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

if(BUILD_SHARED_LIBS AND CMAKE_SYSTEM_NAME STREQUAL Windows)
add_custom_command(TARGET TestGame POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:TestGame> $<TARGET_FILE_DIR:TestGame>
  COMMAND_EXPAND_LISTS
)
endif()
