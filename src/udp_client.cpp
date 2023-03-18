/**
 * UDP Client Class
 *
 * @file: udp_client.cpp
 * @date: 18.03.2023
 */

#include "udp_client.h"

namespace client {
    UDPClient::UDPClient(std::string host, int port) : client::BaseClient(std::move(host), port) {}

    UDPClient::~UDPClient() {
        close(this->client_fd);

        kill(this->receive_pid, SIGKILL);
    }

    void UDPClient::init() {
        bzero((char *) &server_address, sizeof(server_address));

        this->server_address.sin_family = AF_INET;
        this->server_address.sin_addr.s_addr = inet_addr(this->host->c_str());
        this->server_address.sin_port = htons(this->port);

        this->sock = socket(AF_INET, SOCK_DGRAM, 0);

        if (this->sock < 0) { throw SocketCreationException(); }

        this->client_fd = connect(this->sock, (struct sockaddr *) &this->server_address, sizeof(this->server_address));

        if (this->client_fd < 0) { throw ConnectionException(); }
    }

    void UDPClient::run() {
        receive_pid = fork();

        if (receive_pid == 0) {
            this->process_send();
        } else {
            this->process_receive();
        }
    }

    void UDPClient::process_receive() {
        char buffer[1024] = {0};

        while (true) {
            memset(buffer, 0, 1024);
            ssize_t n = recv(this->sock, buffer, 1024, 0);
            if (n < 0) { perror("Receive failed\n"); }

            this->notify(buffer);
        }
    }

    void UDPClient::process_send() {
        while (true) {
            std::string input;
            std::getline(std::cin, input);
            std::string send_input;

            send_input += (char) 0;
            send_input += (char) input.length();
            send_input += input;

            ssize_t send_bytes = send(this->sock, send_input.c_str(), send_input.length(), 0);
            if (send_bytes < 0) { perror("Send failed\n"); }
        }
    }
}// namespace client