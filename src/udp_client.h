/**
 * UDP Client Class
 *
 * @file: udp_client.h
 * @date: 18.03.2023
 */

#ifndef IPKCPC_UDP_CLIENT_H
#define IPKCPC_UDP_CLIENT_H

#include "base_client.h"

#include <iostream>
#include <csignal>
#include <string>
#include <arpa/inet.h>

namespace client {
    /**
     * TCP client class
     */
    class UDPClient : public client::BaseClient {
    private:
        /** @var client_fd Connection file descriptor of the client */
        int client_fd = 0;

        /** @var receive_pid PID of the receive process */
        int receive_pid = 0;

        /**
         * Internal receive process
         */
        [[noreturn]] void process_receive();

        /**
         * Internal send process
         */
        [[noreturn]] void process_send();

    public:
        /**
         * TCP client constructor
         *
         * @param host Host of the server
         * @param port Port of the server
         */
        UDPClient(std::string host, int port);

        /**
         * TCP client destructor
         */
        ~UDPClient();

        /**
         * Initialize the client
         *
         * @throws SocketCreationException if the socket creation failed
         * @throws ConnectionException if the connection to the server failed
         */
        void init() override;

        /**
         * Run the client
         */
        void run() override;
    };
}// namespace client

#endif// IPKCPC_UDP_CLIENT_H
