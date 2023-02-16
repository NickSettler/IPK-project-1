/**
 * Tests for arguments parser
 *
 * @file: args_parser_tests.cpp
 * @date: 16.02.2023
 */

#include <gtest/gtest.h>

#include <utility>
#include "../src/args.h"
#include "../src/args.cpp"

namespace IPK::tests {
    namespace {
        class ArgumentsParserTests : public ::testing::Test {
        protected:
            arguments::ArgumentsParser *args_parser{};

            void Init(int argc, char **argv) {
                this->args_parser = new arguments::ArgumentsParser(argc, argv);
                this->args_parser->parse();
            }

            void Init(int argc, char **argv, std::vector<char> allowed_flags) {
                this->args_parser = new arguments::ArgumentsParser(argc, argv, std::move(allowed_flags));
                this->args_parser->parse();
            }

            void TearDown() override { delete this->args_parser; }

            void CheckArgument(char flag, const std::string &value) {
                EXPECT_EQ(true, this->args_parser->has_flag(flag));
                EXPECT_EQ(value, this->args_parser->get_value(flag));
            }

            void CheckArguments(const std::vector<arguments::program_arg_t> &args) {
                EXPECT_EQ(args.size(), this->args_parser->get_args()->size());

                for (auto &arg: args) { CheckArgument(arg.flag, arg.value); }
            }
        };

        TEST_F(ArgumentsParserTests, OneHostArgument) {
            int argc = 3;
            char *argv[] = {(char *) "client", (char *) "-h", (char *) "1.2.3.4"};

            Init(argc, argv);

            CheckArguments({{.flag = 'h', .value = "1.2.3.4"}});
        }

        TEST_F(ArgumentsParserTests, OnePortArgument) {
            int argc = 3;
            char *argv[] = {(char *) "client", (char *) "-p", (char *) "1234"};

            Init(argc, argv);

            CheckArguments({{.flag = 'p', .value = "1234"}});
        }

        TEST_F(ArgumentsParserTests, OneModeArgument) {
            int argc = 3;
            char *argv[] = {(char *) "client", (char *) "-m", (char *) "tcp"};

            Init(argc, argv);

            CheckArguments({{.flag = 'm', .value = "tcp"}});
        }

        TEST_F(ArgumentsParserTests, HostAndPortArguments) {
            int argc = 5;
            char *argv[] = {(char *) "client", (char *) "-h", (char *) "1.2.3.4", (char *) "-p", (char *) "1234"};

            Init(argc, argv);

            CheckArguments({{.flag = 'h', .value = "1.2.3.4"}, {.flag = 'p', .value = "1234"}});
        }

        TEST_F(ArgumentsParserTests, HostAndPortAndModeArguments) {
            int argc = 7;
            char *argv[] = {(char *) "client", (char *) "-h", (char *) "1.2.3.4", (char *) "-p",
                            (char *) "1234",   (char *) "-m", (char *) "tcp"};

            Init(argc, argv);

            CheckArguments(
                    {{.flag = 'h', .value = "1.2.3.4"}, {.flag = 'p', .value = "1234"}, {.flag = 'm', .value = "tcp"}});
        }

        TEST_F(ArgumentsParserTests, AllowedOnlyHostArgument) {
            int argc = 3;
            char *argv[] = {(char *) "client", (char *) "-h", (char *) "1.2.3.4"};

            Init(argc, argv, {'h'});

            CheckArguments({{.flag = 'h', .value = "1.2.3.4"}});
        }

        TEST_F(ArgumentsParserTests, AllowedOnlyPortArgument) {
            int argc = 3;
            char *argv[] = {(char *) "client", (char *) "-p", (char *) "1234"};

            Init(argc, argv, {'p'});

            CheckArguments({{.flag = 'p', .value = "1234"}});
        }

        TEST_F(ArgumentsParserTests, AllowedOnlyModeArgument) {
            int argc = 3;
            char *argv[] = {(char *) "client", (char *) "-m", (char *) "tcp"};

            Init(argc, argv, {'m'});

            CheckArguments({{.flag = 'm', .value = "tcp"}});
        }

        TEST_F(ArgumentsParserTests, AllowedAllArguments) {
            int argc = 7;
            char *argv[] = {(char *) "client", (char *) "-h", (char *) "1.2.3.4", (char *) "-p",
                            (char *) "1234",   (char *) "-m", (char *) "tcp"};

            Init(argc, argv, {'h', 'p', 'm'});

            CheckArguments(
                    {{.flag = 'h', .value = "1.2.3.4"}, {.flag = 'p', .value = "1234"}, {.flag = 'm', .value = "tcp"}});
        }

        TEST_F(ArgumentsParserTests, PassedUnallowedArgument) {
            int argc = 3;
            char *argv[] = {(char *) "client", (char *) "-h", (char *) "1.2.3.4"};

            EXPECT_THROW(Init(argc, argv, {}), arguments::NotAllowedArgumentException);
        }

        TEST_F(ArgumentsParserTests, CheckNonexistantArgument) {
            int argc = 3;
            char *argv[] = {(char *) "client", (char *) "-h", (char *) "1.2.3.4"};

            Init(argc, argv);

            EXPECT_EQ(false, this->args_parser->has_flag('p'));
        }
    }// namespace
}// namespace IPK::tests