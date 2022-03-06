cmake_minimum_required (VERSION 3.8)

enable_testing()

add_executable (connect
    "connect.cpp")
target_link_libraries (connect
    mc-proto)

add_executable (tests
    "test.cpp")
target_link_libraries (tests
    mc-proto
    gtest_main)

set(EXE_COMPILE_DEFINITIONS
    -DWIN32_LEAN_AND_MEAN)

if (WIN32)
    target_compile_definitions(connect PUBLIC ${EXE_COMPILE_DEFINITIONS})
    target_compile_definitions(tests PUBLIC ${EXE_COMPILE_DEFINITIONS})
endif ()

include(GoogleTest)
gtest_discover_tests(tests)