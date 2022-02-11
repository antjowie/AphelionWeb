cmake_minimum_required(VERSION 3.16)

set(CMAKE_FOLDER Aphelion)

# Setup emscripten compiler if we compile to WASM
message(
    "\n"
    "--- Aphelion settings start ---\n"
    "System: ${CMAKE_SYSTEM_NAME}\n"
    "Hot reload support: ${APHELION_HOT_RELOAD}\n"
    "Building DLL: ${BUILD_SHARED_LIBS}\n"
    "--- Aphelion settings end ---\n"
    )
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

if(BUILD_SHARED_LIBS)
    add_compile_definitions(AP_BUILD_DLL)
    add_compile_options($<$<NOT:$<PLATFORM_ID:Windows>>:-fPIC>)
endif()

add_subdirectory(Src/Aphelion/Core)
add_subdirectory(Src/Aphelion/Engine)
add_subdirectory(Src/Aphelion/ImGUI)
# add_subdirectory(Src/Aphelion/Renderer)
add_subdirectory(Src/Aphelion/Window)

remove_definitions(AP_BUILD_DLL)
# TODO we probably want to remove shared lib compile option
# remove_compile_options()
