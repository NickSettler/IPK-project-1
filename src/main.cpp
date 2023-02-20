/**
 * Client for AaaS (Arithmetic as a Service) server
 *
 * @file: client.cpp
 * @date: 16.02.2023
 */

#include "args.h"
#include "tcp_client.h"
#include "observer.h"

arguments::ArgumentsParser *args_parser;
client::TCPClient *tcp_client;

void interrupt_signal_handler(int signal) {
    printf("Interrupt signal received. Exiting...\n");

    delete args_parser;
    delete tcp_client;

    exit(signal);
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

    std::string host = args_parser->get_value('h');
    int port = std::stoi(args_parser->get_value('p'));

    std::function<void(const std::string &)> tcp_observer_callback = [](const std::string &message) {
        printf("Message received: %s\n", message.c_str());
    };

    auto tcp_observer = new events::Observer(tcp_observer_callback);

    tcp_client = new client::TCPClient(host, port);

    tcp_client->attach(*tcp_observer);

    try {
        tcp_client->init();
    } catch (client::SocketCreationException &e) {
        printf("%s\n", e.what());
        return 1;
    } catch (client::InvalidAddressException &e) {
        printf("%s\n", e.what());
        return 1;
    }

    tcp_client->run();

    delete args_parser;
    delete tcp_client;

    return 0;
}