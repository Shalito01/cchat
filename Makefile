CC = clang
CFLAGS = -Wall -O2
OBJ = server.o
PREFIX = server
EXE = server

.PHONY: clean

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

$(PREFIX).o: server.c utils.h

clean:
	rm -rf $(EXE) $(OBJ)
