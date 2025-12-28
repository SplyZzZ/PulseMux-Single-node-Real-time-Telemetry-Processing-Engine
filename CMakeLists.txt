
cmake_minimum_required(VERSION 3.16)

project(PulseMux LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG v3.9.0
)
FetchContent_MakeAvailable(simdjson)


add_library(pulsemux_lib
    src/ingest/readFile.cpp
    src/parse_validate/parseEvent.cpp
    src/parse_validate/typeConvertation.cpp
    src/parse_validate/validateData.cpp
)

target_include_directories(pulsemux_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(pulsemux_lib PUBLIC simdjson)

add_executable(pulsemux
    apps/main.cpp
)

target_link_libraries(pulsemux PRIVATE pulsemux_lib)

if (MSVC)
    target_compile_options(pulsemux_lib PRIVATE /W4)
    target_compile_options(pulsemux PRIVATE /W4)
else()
    target_compile_options(pulsemux_lib PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(pulsemux PRIVATE -Wall -Wextra -Wpedantic)
endif()