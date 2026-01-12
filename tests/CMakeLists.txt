add_executable(pulsemux_tests
        ingest/readFile.cpp

        parse_validate/checkDuplicate.cpp
        parse_validate/metricRegistry.cpp
        parse_validate/normalize.cpp
        parse_validate/parseEvent.cpp
        parse_validate/typeConvertation.cpp
        parse_validate/validateDataError.cpp

        pipeline/bootstrap.cpp
        pipeline/router.cpp
        pipeline/worker.cpp

        windowing/windowAggregator.cpp
)

target_link_libraries(pulsemux_tests
        PRIVATE
        pulsemux_lib
        GTest::gtest
        GTest::gtest_main
)

add_test(NAME pulsemux_tests COMMAND pulsemux_tests)
