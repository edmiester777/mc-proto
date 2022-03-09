# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("mc-proto")

set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(
    "third-party/cpp-nbt"
)

# Include sub-projects.
add_subdirectory ("third-party/glog")
add_subdirectory ("third-party/socketpp")
add_subdirectory ("third-party/zlib")


include_directories(
    "."
    "third-party/socketpp/include"
)

add_subdirectory ("mc-proto")
add_subdirectory ("test")
