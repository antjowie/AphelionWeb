cmake_minimum_required(VERSION 3.16)

add_executable(TestGame
	"Src/TestGame.cpp"
)

target_include_directories(TestGame PUBLIC /Src/)
target_precompile_headers(TestGame PRIVATE ${APHELION_PCH})
message(STATUS "Suffix: ${CMAKE_EXECUTABLE_SUFFIX}")

# TODO Have a better way of copying over Dlls instead of adding every library
target_add_dependency(TestGame Aphelion::Core)
target_add_dependency(TestGame Aphelion::Engine)
target_add_dependency(TestGame Aphelion::Window)
target_add_dependency(TestGame glfw)
