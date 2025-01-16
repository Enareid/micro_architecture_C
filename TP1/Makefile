CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = decode.o instructions.o

all: simulateur

simulateur: $(OBJ)
	$(CC) $(CFLAGS) -o simulateur $(OBJ)

decode.o: decode.c instructions.h
	$(CC) $(CFLAGS) -c decode.c

instructions.o: instructions.c instructions.h
	$(CC) $(CFLAGS) -c instructions.c

clean:
	rm -f $(OBJ) simulateur
