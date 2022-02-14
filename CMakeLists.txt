cmake_minimum_required(VERSION 3.21)

project(Aphelion)

# https://docs.microsoft.com/en-us/visualstudio/debugger/supported-code-changes-cpp?view=vs-2022
# https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-170#edit-and-continue-for-cmake-projects
option(APHELION_HOT_RELOAD "Support for hot reload in all configs" OFF)
if(APHELION_HOT_RELOAD)
    if(MSVC)
        add_link_options(/INCREMENTAL)
        add_compile_options(/ZI)
        # /ZI seems to be incompatible with reusing precompiled headers
        set(CMAKE_DISABLE_PRECOMPILE_HEADERS ON)
    else()
        message(WARNING "Hot reload is only supported for MSVC")
        set(APHELION_HOT_RELOAD OFF)
    endif()
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Setup CPM as our dependency manager
set(CPM_DOWNLOAD_VERSION 0.34.3)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/CMake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
set(CPM_SOURCE_CACHE "${CMAKE_SOURCE_DIR}/ThirdParty" CACHE FILEPATH "" FORCE)

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake")
    file(DOWNLOAD https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake ${CPM_DOWNLOAD_LOCATION})
endif()

include(${CPM_DOWNLOAD_LOCATION})

# Build all modules
add_subdirectory(Aphelion)
add_subdirectory(Sandbox/TestGame)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT TestGame)
