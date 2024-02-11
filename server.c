#include "includes/server.h"
#include "includes/utils.h"
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
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

#define SRV_PORT 8080
#define DEBUG 1
#define HSIZE 512

static struct Set *users_set[HSIZE];

/*
 *  Main Server
 */
int main(int argc, char **argv) {
  int socket_fd, client, c_status;
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

  print_debug(DEBUG, (char)DSUCCESS, "Server listening on ::8080");

  int pid;
  while (1) {
    client = accept(socket_fd, (struct sockaddr *)&server, &addrlen);

    if (client < 0)
      perror("[-] Client connection error");

    pid = fork();

    if (pid < 0) {
      perror("[-] ERROR in new process creation!");
    }

    if (pid == 0) {
      /*
          Child Process
      */
      print_debug(DEBUG, (char)DSUCCESS, "Accepted client connection!");
      c_status = recv(client, buf, BUFFER, 0);
      if (c_status < 0) {
        perror("[-] ERROR: Failed to read from client!");
      }
      del_trailing_n(buf);

      // print_debug(DEBUG, "Received input from client!");
      print_debug(DEBUG, (char)DINFO, buf);

      close(client);
      memset(buf, 0x00, BUFFER);
    } else {
      /*
          Parent Process
      */
      close(client);
    }
  }

  free(buf);
  return EXIT_SUCCESS;
}

unsigned hash_function(char *s) {
  unsigned hashval;
  for (hashval = 0; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HSIZE;
}

struct Set *lookup(struct Set **table, char *s) {
  struct Set *np;
  for (np = table[hash_function(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->username) == 0)
      return np; /* found */
  return NULL;   /* not found */
}

struct Set *add(struct Set **table, char *name) {
  struct Set *np;
  unsigned hashval;

  if ((np = lookup(table, name)) == NULL) { /* not found */
    np = (struct Set *)malloc(sizeof(*np));

    if (np == NULL || (np->username = strdup(name)) == NULL)
      return NULL;

    hashval = hash_function(name);
    np->next = users_set[hashval];
    users_set[hashval] = np;
  } else /* already there */
    return NULL;

  return np;
}
