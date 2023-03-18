/**
 * Client for AaaS (Arithmetic as a Service) server
 *
 * @file: client.cpp
 * @date: 16.02.2023
 */

#include <string>

#include "args.h"
#include "tcp_client.h"
#include "udp_client.h"
#include "observer.h"

arguments::ArgumentsParser *args_parser;
client::TCPClient *tcp_client;
client::UDPClient *udp_client;

void delete_instances() {
    delete args_parser;
    delete tcp_client;
    delete udp_client;
}

void interrupt_signal_handler(int signal) {
    delete_instances();

    exit(signal);
}

void create_udp_client(const std::string &host, int port) {
    std::function<void(const char *)> udp_observer_callback = [](const char *message) {
        unsigned int opcode = (int) message[0];
        unsigned int status_code = (int) message[1];

        if (opcode != 1) { throw std::runtime_error("Invalid opcode"); }

        std::string output;

        output += status_code == 0 ? "OK" : "ERROR";
        output += ":";
        output += message + 3;

        printf("%s\n", output.c_str());
    };

    auto udp_observer = new events::Observer(udp_observer_callback);

    udp_client = new client::UDPClient(host, port);

    udp_client->attach(*udp_observer);

    try {
        udp_client->init();
    } catch (client::SocketCreationException &e) {
        printf("%s\n", e.what());
        delete_instances();
        std::exit(1);
    } catch (client::InvalidAddressException &e) {
        printf("%s\n", e.what());
        delete_instances();
        std::exit(1);
    }

    udp_client->run();
}

void create_tcp_client(const std::string &host, int port) {
    std::function<void(const char *)> tcp_observer_callback = [](const char *message) { printf("%s", message); };

    auto tcp_observer = new events::Observer(tcp_observer_callback);

    tcp_client = new client::TCPClient(host, port);

    tcp_client->attach(*tcp_observer);

    try {
        tcp_client->init();
    } catch (client::SocketCreationException &e) {
        printf("%s\n", e.what());
        delete_instances();
        std::exit(1);
    } catch (client::InvalidAddressException &e) {
        printf("%s\n", e.what());
        delete_instances();
        std::exit(1);
    }

    try {
        tcp_client->run();
    } catch (client::SocketTerminatedException &e) {
        delete_instances();
        std::exit(0);
    }
}

int main(int argc, char **argv) {
    signal(SIGINT, interrupt_signal_handler);

    args_parser = new arguments::ArgumentsParser(argc, argv, {'h', 'p', 'm'});

    try {
        args_parser->parse();
    } catch (arguments::NotAllowedArgumentException &e) {
        printf("%s\n", e.what());
        arguments::ArgumentsParser::print_help();
        return 1;
    }

    bool has_host = args_parser->has_flag('h');
    bool has_port = args_parser->has_flag('p');
    bool has_mode = args_parser->has_flag('m');

    if (!has_host || !has_port || !has_mode) {
        arguments::ArgumentsParser::print_help();
        return 1;
    }

    std::string host = args_parser->get_value('h');
    int port = std::stoi(args_parser->get_value('p'));

    if (args_parser->get_value('m') == "udp") { create_udp_client(host, port); }

    if (args_parser->get_value('m') == "tcp") { create_tcp_client(host, port); }

    delete_instances();

    return 0;
}