cmake_minimum_required(VERSION 3.18)

project(Aphelion)

# Can't build shared library. Causes a lot of errors. Can't create a vector of unique pointers???
# Since building this project to a shared lib is no priority of mine, I will ignore it for now...
# option(BUILD_SHARED_LIBS false CACHE)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setup CPM as our dependency manager
set(CPM_DOWNLOAD_VERSION 0.31.1) 
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/CMake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/ThirdParty" CACHE FILEPATH "" FORCE)

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# Build all modules
add_subdirectory(Aphelion)
add_subdirectory(Sandbox/WASMGraphic)