/**
 * Base client superclass fot TCP and UDP clients
 *
 * @file: base_client.h
 * @date: 18.02.2023
 */

#ifndef IPKCPC_BASE_CLIENT_H
#define IPKCPC_BASE_CLIENT_H

#include "common.h"
#include "observer.h"

#include <utility>
#include <unistd.h>
#include <exception>
#include <cstring>
#include <string>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <winsock.h>
#else
#include <netinet/in.h>
#endif

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

    class BaseClient : public events::Subject {
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
