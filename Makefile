CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

steg: steg.o parser.o
	$(CC) $(CFLAGS) -o steg steg.o parser.o

steg.o: steg.c parser.h bmp.h
	$(CC) $(CFLAGS) -c steg.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

clean:
	rm -f steg steg.o parser.o

.PHONY: clean
