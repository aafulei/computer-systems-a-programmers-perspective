CC = gcc
CFLAGS = -O2 -Wall -I ..

all: adder adder2

adder: adder.c
	$(CC) $(CFLAGS) -o adder adder.c

adder2: adder2.c
	$(CC) $(CFLAGS) -o adder2 adder2.c

clean:
	rm -f adder adder2 *~
