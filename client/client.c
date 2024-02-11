#include "client.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  bool registered = false;
  client_t *cli = malloc(sizeof(client_t));
  cli->client_fd = -1;
  cli->username = strdup("Anonymous");

  print_prompt(registered, cli);

  return EXIT_SUCCESS;
}

void print_prompt(int is_registered, client_t *client) {
  if (client == NULL)
    return;

  printf("[%s] > ", client->username);
}
