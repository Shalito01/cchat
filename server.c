#include "utils.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

extern int errno;

/*
 *   Max queue length specifiable by listen
 */
/* #define SOMAXCONN 10 */
/*
 * Use TCP Protocol
 */
#define PROTO 0

#define BUFFER 1024
#define SRV_PORT 8080
#define DEBUG 1

/*
 *  Main Server
 */
int main(int argc, char **argv) {
    int socket_fd, client;
    char *buf = calloc(BUFFER, sizeof(char));
    struct sockaddr_in server;
    socklen_t addrlen = sizeof(server);

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, PROTO)) == -1) {
        perror("[-] SOCKET");
        exit(errno);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SRV_PORT);

    if (bind(socket_fd, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("[-] BIND");
        exit(errno);
    }

    if (listen(socket_fd, SOMAXCONN) == -1) {
        perror("[-] LISTEN");
        exit(errno);
    }

    print_debug(DEBUG, "Server listening on ::8080");

    if ((client = accept(socket_fd, (struct sockaddr *)&server, &addrlen)) ==
            -1) {
        perror("[-] ACCEPT");
        exit(errno);
    }
    print_debug(DEBUG, "Accepted client connection!");

    while (client != -1) {
        if (recv(client, buf, BUFFER, 0) != -1) {
            /*
             * Clean input from trailing \n\r
             */
            remove_trailing(buf);

            print_debug(DEBUG, "Received input from client!");
            print_debug(DEBUG, buf);

            if (strcmp(buf, "exit") == 0) {
                close(socket_fd);
                close(client);
                break;
            }

            memset(buf, 0x00, BUFFER);
        }
    }

    free(buf);
    return EXIT_SUCCESS;
}
