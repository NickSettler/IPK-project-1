/*
 * IPK
 *
 * Demonstration of a basic TCP server.
 *
 * Ondrej Rysavy (rysavy@fit.vutbr.cz)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define WELCOME_MSG "Hi, type anything. To end type 'bye.' at a separate line.\n"
#define BUFSIZE 1024

int welcome_socket;

void sigterm_handler(int signum) {
    printf("INFO: SIGTERM received. Exiting...\n");
    close(welcome_socket);
    exit(EXIT_SUCCESS);
}

int main(int argc, const char *argv[]) {
    signal(SIGTERM, sigterm_handler);
    signal(SIGINT, sigterm_handler);
    signal(SIGKILL, sigterm_handler);

    int rc;
    struct sockaddr_in6 sa;
    struct sockaddr_in6 sa_client;
    char str[INET6_ADDRSTRLEN];
    char buff[BUFSIZE];
    int port_number;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    port_number = atoi(argv[1]);

    socklen_t sa_client_len = sizeof(sa_client);
    if ((welcome_socket = socket(PF_INET6, SOCK_STREAM, 0)) < 0) {
        perror("ERROR: socket");
        exit(EXIT_FAILURE);
    }

    memset(&sa, 0, sizeof(sa));
    sa.sin6_family = AF_INET6;
    sa.sin6_addr = in6addr_any;
    sa.sin6_port = htons(port_number);

    if ((rc = bind(welcome_socket, (struct sockaddr *) &sa, sizeof(sa))) < 0) {
        perror("ERROR: bind");
        exit(EXIT_FAILURE);
    }
    if ((rc = listen(welcome_socket, 1)) < 0) {
        perror("ERROR: listen");
        exit(EXIT_FAILURE);
    }
    while (1) {
        int comm_socket = accept(welcome_socket, (struct sockaddr *) &sa_client, &sa_client_len);
        if (comm_socket > 0) {
            if (inet_ntop(AF_INET6, &sa_client.sin6_addr, str, sizeof(str))) {
                printf("INFO: New connection:\n");
                printf("INFO: Client address is %s\n", str);
                printf("INFO: Client port is %d\n", ntohs(sa_client.sin6_port));
            }

            send(comm_socket, WELCOME_MSG, strlen(WELCOME_MSG), 0);

            ssize_t res = 0;
            for (;;) {
                memset(buff, 0, BUFSIZE);
                res = recv(comm_socket, buff, 1024, 0);
                printf("%lu\n", res);
                //                sleep(2);
                if (res > 0) {
                    buff[res] = '\0';
                    printf("Received: %s\n", buff);
                    printf("Sending: %s\n", buff);
                    send(comm_socket, buff, strlen(buff), 0);
                    buff[4] = '\0';
                    if (strcmp(buff, "bye.") == 0) {
                        printf("INFO: Closing connection to %s.\n", str);
                        close(comm_socket);
                        break;
                    }
                } else if (res == 0) {
                    printf("INFO: %s closed connection.\n", str);
                    close(comm_socket);
                    break;
                }
            }
        } else {
            perror("ERROR: accept");
        }
    }
}