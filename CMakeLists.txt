cmake_minimum_required(VERSION 3.16)

project(PulseMux VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG v3.9.0
)

FetchContent_MakeAvailable(simdjson)

add_executable(PulseMux_app
    apps/main.cpp
)

target_compile_features(PulseMux_app PRIVATE cxx_std_20)

target_link_libraries(PulseMux_app
    PRIVATE simdjson
)
