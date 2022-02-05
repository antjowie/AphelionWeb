cmake_minimum_required(VERSION 3.18)

set(CMAKE_FOLDER Aphelion)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)
# target_include_directories(Core PUBLIC
#  	${CMAKE_CURRENT_SOURCE_DIR}/../../
# )

# Setup emscripten compiler if we compile to WASM
message(STATUS "Aphelion targeting system ${CMAKE_SYSTEM_NAME}")
# if($<PLATFORM_ID:Emscripten>)
# if(CMAKE_SYSTEM_NAME STREQUAL Emscripten)
# 	message(STATUS "Setting up Emscripten")
# 	# TODO: Figure out a way to set variable globally. Cache doesn't seem to work
# 	# This won't work is Aphelion is used as a dependency of a dependency
# 	set(CMAKE_EXECUTABLE_SUFFIX ".html" PARENT_SCOPE)
# 	set(USE_FLAGS "-s USE_SDL=2 -s MAX_WEBGL_VERSION=2 -s WASM=1 -s LLD_REPORT_UNDEFINED" CACHE INTERNAL "")
# 	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}" CACHE INTERNAL "")
# 	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}" CACHE INTERNAL "")
# 	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}" CACHE INTERNAL "")
# 	set_property(GLOBAL PROPERTY LINK_OPTIONS "${USE_FLAGS}")
# endif()

add_subdirectory(Src/Aphelion/Core)
add_subdirectory(Src/Aphelion/Engine)
# add_subdirectory(Src/Aphelion/ImGUI)
# add_subdirectory(Src/Aphelion/Renderer)
# add_subdirectory(Src/Aphelion/Window)

# add_subdirectory(Src/Aphelion/Print)
