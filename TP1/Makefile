CC = gcc
CFLAGS = -Wall -Wextra -g
OBJ = decode.o instructions.o cpu.o 

all: simulateur

assembly: output

simulateur: $(OBJ)
	$(CC) $(CFLAGS) -o simulateur $(OBJ)

decode.o: decode.c instructions.h
	$(CC) $(CFLAGS) -c decode.c

instructions.o: instructions.c instructions.h
	$(CC) $(CFLAGS) -c instructions.c

cpu.o: cpu.c cpu.h
	$(CC) $(CFLAGS) -c cpu.c	

output.o: output.s 
	as -a --gstabs -o output.o output.s

output: output.o
	ld -o output output.o

clean:
	rm -f $(OBJ) simulateur output.*
