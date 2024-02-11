#ifndef UTIL_H
#define UTIL_H

enum debug_symbols { DERROR = '-', DSUCCESS = '+', DINFO = 'i' };

/* Clean input byte string (delete trailing \n) */
void del_trailing_n(char *str);
void print_debug(int debug, const char type, const char *str);
int register_client(int client_fd, char *username);

#endif
