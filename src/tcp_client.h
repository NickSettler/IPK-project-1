/**
 * TCP client class
 *
 * @file: TcpClient.h
 * @date: 18.02.2023
 */

#ifndef IPKCPC_TCP_CLIENT_H
#define IPKCPC_TCP_CLIENT_H

#include "base_client.h"
#include "observer.h"

#include <csignal>
#include <unistd.h>
#include <utility>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

/**
 * Client namespace
 *
 * @namespace client
 */
namespace client {
    /**
     * TCP client class
     */
    class TCPClient : public client::BaseClient {
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
        TCPClient(std::string host, int port);

        /**
         * TCP client destructor
         */
        ~TCPClient();

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

#endif// IPKCPC_TCP_CLIENT_H
