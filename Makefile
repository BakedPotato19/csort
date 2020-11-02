CC = gcc
CFLAGS = -std=c11

test:
	$(CC) $(CFLAGS) -o csort *.c
