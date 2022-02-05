cmake_minimum_required(VERSION 3.18)

add_library(Print "Print.h" "Print.cpp")
target_include_directories(Print PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/.)

target_link_libraries(Print PRIVATE
	# Print
	#Aphelion::Engine
	Aphelion::Core
)
