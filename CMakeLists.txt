
cmake_minimum_required(VERSION 3.16)

project(PulseMux LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    simdjson
    GIT_REPOSITORY https://github.com/simdjson/simdjson.git
    GIT_TAG v3.9.0
)
FetchContent_MakeAvailable(simdjson)
include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
FetchContent_Declare(
        date
        GIT_REPOSITORY https://github.com/HowardHinnant/date.git
        GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(date)

add_library(pulsemux_lib
    src/ingest/readFile.cpp
    src/parse_validate/parseEvent.cpp
    src/parse_validate/typeConvertation.cpp
    src/parse_validate/validateDataError.cpp
    src/pipeline/bootstrap.cpp
    src/parse_validate/metricRegistry.cpp
    src/parse_validate/normalize.cpp
    src/parse_validate/checkDuplicate.cpp
    src/pipeline/router.cpp
    src/pipeline/worker.cpp
    src/windowing/windowAggregator.cpp
)

target_include_directories(pulsemux_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(pulsemux_lib PUBLIC simdjson PRIVATE date::date)

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
enable_testing()
add_subdirectory(tests)