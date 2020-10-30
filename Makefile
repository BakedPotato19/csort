CC = gcc
CFLAGS = -std=c11

test:
	$(CC) $(CFLAGS) *.c -o csort
