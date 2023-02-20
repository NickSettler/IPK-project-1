/**
 * Base client superclass fot TCP and UDP clients
 *
 * @file: base_client.h
 * @date: 18.02.2023
 */

#ifndef IPKCPC_BASE_CLIENT_H
#define IPKCPC_BASE_CLIENT_H

#include <exception>
#include <string>
#include <netinet/in.h>

namespace client {
    class SocketCreationException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class InvalidAddressException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class ConnectionException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override;
    };

    class BaseClient {
    protected:
        /** @var host Host of the server */
        std::string *host;
        /** @var port Port of the server */
        int port;

        int sock = 0;

        sockaddr_in server_address{};

    public:
        BaseClient(std::string host, int port);

        ~BaseClient();

        virtual void init() = 0;

        virtual void run() = 0;
    };
}// namespace client

#endif// IPKCPC_BASE_CLIENT_H
