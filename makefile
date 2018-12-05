CC=clang
EXE=avltree
VERS=-std=c99
CFLAGS=-Wall -Werror 
OBJ=avltree.o
CFILES=avltree.c

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ) : $(CFILES)
	$(CC) $(VERS) -c $(CFILES)

clean:
	rm -f $(OBJ) $(EXE)