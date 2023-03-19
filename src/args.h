/**
 * Arguments parser file
 *
 * @file: args.h
 * @date: 16.02.2023
 */

#ifndef IPKCPC_ARGS_H
#define IPKCPC_ARGS_H

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

/**
 * Arguments namespace
 *
 * @namespace arguments
 */
namespace arguments {
    /**
     * Program argument type
     *
     * @typedef program_arg_t
     * @struct program_arg
     * @var program_arg::flag
     * Flag of the argument
     * @var program_arg::value
     * Value of the argument
     */
    typedef struct program_arg {
        char flag;
        std::string value;
    } program_arg_t;

    /**
     * Not allowed argument exception class
     *
     * @class NotAllowedArgumentException
     */
    class NotAllowedArgumentException : public std::exception {

    private:
        /** @var flag Flag of the argument */
        char *flag = nullptr;

    public:
        /**
         * NotAllowedArgumentException constructor
         *
         * @param flag Flag of the argument
         */
        explicit NotAllowedArgumentException(char flag);

        /**
         * Cause of the exception
         */
        [[nodiscard]] const char *what() const noexcept override;
    };

    /**
     * Arguments parser class
     *
     * @class ArgumentsParser
     */
    class ArgumentsParser {
    private:
        /** @var argc Program argument count */
        int argc;
        /** @var argv Program arguments array */
        char **argv;
        /** @var allowed_flags Allowed flags */
        std::vector<char> *allowed_flags = nullptr;

        /** @var args Vector of parsed arguments */
        std::vector<program_arg_t> *args;

    public:
        /**
         * ArgumentsParser constructor without allowed flags
         * Allowed flags are set to default (nullptr), so all flags are allowed
         *
         * @param argc Program argument count
         * @param argv Program arguments array
         */
        ArgumentsParser(int argc, char **argv);

        /**
         * ArgumentsParser constructor with allowed flags
         * Allowed flags are set to passed vector of allowed flags, so only flags from this vector are allowed
         *
         * @param argc Program argument count
         * @param argv Program arguments array
         * @param allowed_flags Vector of allowed flags
         */
        ArgumentsParser(int argc, char **argv, std::vector<char> allowed_flags);

        /**
         * ArgumentsParser destructor
         */
        ~ArgumentsParser();

        /**
         * Parse arguments
         */
        void parse();

        /**
         * Get value of the argument with specified flag
         *
         * @param flag Flag of the argument
         * @return Value of the argument
         */
        std::string get_value(char flag);

        /**
         * Check if argument with specified flag exists
         *
         * @param flag Flag of the argument
         * @return True if argument with specified flag exists, false otherwise
         */
        bool has_flag(char flag);

        /**
         * Get vector of parsed arguments
         * @return Vector of parsed arguments
         */
        std::vector<program_arg_t> *get_args();

        /**
         * Print help. This method is called when unknown flag is passed to the program
         */
        static void print_help();
    };
}// namespace arguments

#endif// IPKCPC_ARGS_H
