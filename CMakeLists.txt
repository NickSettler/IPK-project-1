cmake_minimum_required(VERSION 3.23)
project(ipkcpc)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()

add_executable(
        AllTests
        tests/main.cpp
        tests/args_parser_tests.cpp)

target_link_libraries(
        AllTests
        PRIVATE
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(AllTests)

add_executable(ipkcpc src/client.cpp src/client.h src/args.cpp src/args.h)