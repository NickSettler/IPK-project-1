/**
 * Arguments parser file
 *
 * @file: args.cpp
 * @date: 16.02.2023
 */

#include "args.h"

arguments::NotAllowedArgumentException::NotAllowedArgumentException(char flag) {
    this->flag = new char[2];
    this->flag[0] = flag;
    this->flag[1] = '\0';
}
const char *arguments::NotAllowedArgumentException::what() const noexcept {
    if (this->flag == nullptr) { return (char *) "Flag is not allowed."; }

    auto *message = new std::string("Flag ");
    message->append(this->flag);
    message->append(" is not allowed.");

    return (char *) message->c_str();
}

arguments::ArgumentsParser::ArgumentsParser(int argc, char **argv) : argc(argc), argv(argv) {
    this->args = new std::vector<program_arg_t>();
}

arguments::ArgumentsParser::ArgumentsParser(int argc, char **argv, std::vector<char> allowed_flags)
    : argc(argc), argv(argv), allowed_flags(new std::vector<char>(std::move(allowed_flags))) {
    this->args = new std::vector<program_arg_t>();
}

arguments::ArgumentsParser::~ArgumentsParser() {
    this->args->clear();
    delete this->args;

    if (this->allowed_flags != nullptr) {
        this->allowed_flags->clear();
        delete this->allowed_flags;
    }
}

void arguments::ArgumentsParser::parse() {
    for (int i = 1; i < this->argc; i++) {
        if (this->argv[i][0] == '-') {
            /*
             * Check if flag is allowed. If allowed_flags is nullptr, all flags are allowed.
             * Otherwise, check if flag is in allowed_flags.
             */
            auto is_flag_allowed = this->allowed_flags == nullptr ||
                                   (this->allowed_flags != nullptr &&
                                    std::find(this->allowed_flags->begin(), this->allowed_flags->end(),
                                              this->argv[i][1]) != this->allowed_flags->end());
            if (is_flag_allowed) {
                /*
                 * Parse argument. Example:
                 * { "-h", "1.2.3.4" } -> arg: (program_arg_t){ flag: 'h', value: "1.2.3.4" }
                 * this->args = { ..., arg }
                 */
                program_arg_t arg;
                arg.flag = this->argv[i][1];
                arg.value = this->argv[i + 1];
                this->args->push_back(arg);
            } else {
                throw NotAllowedArgumentException(this->argv[i][1]);
            }
        }
    }
}

std::string arguments::ArgumentsParser::get_value(char flag) {
    for (auto &arg: *this->args) {
        if (arg.flag == flag) { return arg.value; }
    }

    return "";
}

bool arguments::ArgumentsParser::has_flag(char flag) {
    return std::any_of(this->args->begin(), this->args->end(),
                       [flag](const program_arg_t &arg) { return arg.flag == flag; });
}

std::vector<arguments::program_arg_t> *arguments::ArgumentsParser::get_args() { return this->args; }

void arguments::ArgumentsParser::print_help() {
    printf("Usage: ipkcpc -h <host> -p <port> -m <mode>\n");
    printf("Options:\n");
    printf("  -h <host>    IPv4 address of the server\n");
    printf("  -p <port>    Port number of the server\n");
    printf("  -m <mode>    Mode of the client (TCP or UDP)\n");
}
