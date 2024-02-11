CC = clang
CFLAGS = -Wall -Werror -O2
EXE = server
SRC=$(wildcard *.c)

.PHONY: clean

$(EXE): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf $(EXE) $(OBJ)
