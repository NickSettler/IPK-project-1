/**
 * Base client superclass fot TCP and UDP clients
 *
 * @file: base_client.cpp
 * @date: 18.02.2023
 */

#include "base_client.h"

namespace client {
    const char *SocketCreationException::what() const noexcept { return "Socket creation failed"; }

    const char *InvalidAddressException::what() const noexcept { return "Invalid address / Address not supported"; }

    const char *ConnectionException::what() const noexcept { return "Connection failed"; }

    BaseClient::BaseClient(std::string host, int port) : host(new std::string(std::move(host))), port(port) {
        memset(&server_address, 0, sizeof(server_address));
    }

    BaseClient::~BaseClient() {
        delete this->host;

        if (this->sock != 0) { close(this->sock); }
    }
}// namespace client