cmake_minimum_required(VERSION 3.18)

add_executable(TestGame
	"Src/TestGame.cpp"
)

target_include_directories(TestGame PUBLIC /Src/)
message(STATUS "Suffix: ${CMAKE_EXECUTABLE_SUFFIX}")
target_precompile_headers(TestGame REUSE_FROM Aphelion::Core)


target_link_libraries(TestGame PRIVATE
	# Print
	Aphelion::Engine
	# Aphelion::Core
)
