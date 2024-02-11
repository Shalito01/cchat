CC = gcc
CFLAGS = -Wall -Werror -O2
SRC=$(wildcard ./includes/*.c)

.PHONY: clean

server: $(SRC)
	$(CC) -o $@ server.c $^ $(CFLAGS)

client: $(SRC)
	$(CC) -o $@ client.c $^ $(CFLAGS)

clean:
	echo "hi"
