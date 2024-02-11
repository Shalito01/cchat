#ifndef CLIENT_H
#define CLIENT_H

typedef struct Client {
  char *username;
  int client_fd;
} client_t;

void print_prompt(int is_registered, client_t *client);

#endif
