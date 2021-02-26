cmake_minimum_required(VERSION 3.18)

project(Aphelion)

# Setup emscripten compiler if we compile to WASM
option(WASM false CACHE)
if(WASM)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
    set_property(GLOBAL PROPERTY LINK_OPTIONS "-s WASM=1")
    # set_property(GLOBAL PROPERTY OUTPUT_NAME "index")
endif()

# Setup CPM as our dependency manager
set(CPM_DOWNLOAD_VERSION 0.31.1) 
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/CMake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/ThirdParty" CACHE FILEPATH "Test" FORCE)

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# Build all modules
add_subdirectory(Aphelion)
add_subdirectory(Sandbox/WASMGraphic)