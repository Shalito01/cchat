#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void del_trailing_n(char *str) {
  if (str == NULL)
    return;

  str[strcspn(str, "\n")] = 0;
}

void print_debug(int debug, const char type, const char *str) {
  if (debug) {
    printf("[%c] %s\n", type, str);
  }
}
