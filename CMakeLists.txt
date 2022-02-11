cmake_minimum_required(VERSION 3.16)

project(Aphelion)

# https://docs.microsoft.com/en-us/visualstudio/debugger/supported-code-changes-cpp?view=vs-2022
option(APHELION_HOT_RELOAD "Support for hot reload in all configs" ON)
if(APHELION_HOT_RELOAD)
    if(MSVC)
        add_link_options(/INCREMENTAL)
        add_compile_options(/ZI)
    else()
        message(WARNING "Hot reload is only supported for MSVC")
        set(APHELION_HOT_RELOAD OFF)
    endif()

endif()


# Can't build shared library. Causes a lot of errors. Can't create a vector of unique pointers???
# Since building this project to a shared lib is no priority of mine, I will ignore it for now...
option(BUILD_SHARED_LIBS false)
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

# Sets up an Aphelion system as a dependecy for a target
function(target_add_dependency CurrTarget Dependency)
target_link_libraries(${CurrTarget} PRIVATE ${Dependency})

if(BUILD_SHARED_LIBS)
add_custom_command(TARGET ${CurrTarget} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:${Dependency}>
	"${CMAKE_CURRENT_BINARY_DIR}"
)
endif()
endfunction()

# Setup sources for PCH
set(APHELION_PCH
    <iostream>
    <memory>
    <utility>
    <algorithm>
    <functional>
    <string>
    <sstream>
    <array>
    <vector>
    <unordered_map>
    <unordered_set>
    <type_traits>
    <chrono>
)

# Build all modules
add_subdirectory(Aphelion)
add_subdirectory(Sandbox/TestGame)
