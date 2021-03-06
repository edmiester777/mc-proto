cmake_minimum_required (VERSION 3.8)

enable_testing()

set (NBT_TEST_FILES
    "nbt/bytetag.cpp"
    "nbt/shorttag.cpp"
    "nbt/inttag.cpp"
    "nbt/longtag.cpp"
    "nbt/floattag.cpp"
    "nbt/doubletag.cpp"
    "nbt/stringtag.cpp"
    "nbt/bytearraytag.cpp"
    "nbt/intarraytag.cpp"
    "nbt/longarraytag.cpp"
    "nbt/listtag.cpp"
    "nbt/compoundtag.cpp"
    "nbt/nbt.cpp"
)
add_executable (nbttest ${NBT_TEST_FILES})
target_link_libraries(nbttest 
    mc-proto 
    gtest_main 
    gtest)

add_executable (connect
    "connect.cpp")
target_link_libraries (connect
    mc-proto)

add_executable (alltests
    ${NBT_TEST_FILES})
target_link_libraries (alltests
    mc-proto
    gtest_main 
    gtest)

set(EXE_COMPILE_DEFINITIONS
    -DWIN32_LEAN_AND_MEAN
    -D_CMAKE_PROJECT_PATH="${CMAKE_SOURCE_DIR}")

if (WIN32)
    target_compile_definitions(connect PUBLIC ${EXE_COMPILE_DEFINITIONS})
    target_compile_definitions(nbttest PUBLIC ${EXE_COMPILE_DEFINITIONS})
    target_compile_definitions(alltests PUBLIC ${EXE_COMPILE_DEFINITIONS})

    set_target_properties(connect PROPERTIES
        VS_DEBUGGER_COMMAND_ARGUMENTS "--v=1" # enable verbosity
    )
endif ()

include(GoogleTest)
gtest_discover_tests(nbttest)
gtest_discover_tests(alltests)