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

add_executable(ipkcpc src/main.cpp src/args.cpp src/args.h src/base_client.cpp src/base_client.h src/tcp_client.cpp src/tcp_client.h src/observer.cpp src/observer.h src/udp_client.cpp src/udp_client.h src/utils.cpp src/utils.h src/common.h)