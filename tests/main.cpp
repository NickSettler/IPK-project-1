/**
 * Init Google Test and run all tests
 *
 * @file: main.cpp
 * @date: 16.02.2023
 */

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
