CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = decode.o instructions.o cpu.o

all: simulateur

simulateur: $(OBJ)
	$(CC) $(CFLAGS) -o simulateur $(OBJ)

decode.o: decode.c instructions.h
	$(CC) $(CFLAGS) -c decode.c

instructions.o: instructions.c instructions.h
	$(CC) $(CFLAGS) -c instructions.c

cpu.o: cpu.c cpu.h
	$(CC) $(CFLAGS) -c cpu.c	

clean:
	rm -f $(OBJ) simulateur
