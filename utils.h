#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

void remove_trailing(char *str) {
  if (str == NULL)
    return;

  char *c = strchr(str, '\n');
  if (c != NULL)
    *c = '\0';
}

void print_debug(int debug, const char *str) {
    if(debug) {
        printf("[+] %s\n", str);
    }
}
