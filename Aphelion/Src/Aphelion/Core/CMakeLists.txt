cmake_minimum_required(VERSION 3.18)

option(FORCE_ASSERT false)

CPMAddPackage(gh:gabime/spdlog@1.8.2)

add_library(Core
    Core.hpp
    Engine.hpp
    Engine.cpp
    Log.hpp
    Log.cpp
)

target_link_libraries(Core PUBLIC
    spdlog::spdlog
)

add_library(Aphelion::Core ALIAS Core)

target_precompile_headers(Core
    PUBLIC
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

    # <glm/vec3.hpp>
    # <glm/mat4x4.hpp>
    # <glm/gtc/quaternion.hpp>
    # <glm/gtc/matrix_transform.hpp>
    # <glm/gtc/matrix_transform.hpp>
    # <glm/gtc/type_ptr.hpp>
    # <glm/gtx/quaternion.hpp>
    # <glm/gtx/hash.hpp>

    Log.hpp
)

target_include_directories(Core PUBLIC ../../)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(Core PUBLIC AP_DEBUG)
endif()