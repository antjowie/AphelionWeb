cmake_minimum_required(VERSION 3.18)

add_executable(TestGame
	"Src/TestGame.cpp"
)

target_include_directories(TestGame PUBLIC /Src/)
target_precompile_headers(TestGame PRIVATE ${APHELION_PCH})
message(STATUS "Suffix: ${CMAKE_EXECUTABLE_SUFFIX}")

target_add_dependency(TestGame Aphelion::Core)
target_add_dependency(TestGame Aphelion::Engine)
