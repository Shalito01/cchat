#ifndef SERVER_H
#define SERVER_H

struct Set {
  char *username;

  struct Set *next;
  struct Set *prev;
};

unsigned hash_function(char *s);
struct Set *lookup(struct Set **table, char *s);
struct Set *add(struct Set **table, char *name);

#endif
