CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

steg: steg.o parser.o decode.o
	$(CC) $(CFLAGS) -o steg steg.o parser.o decode.o

steg.o: steg.c parser.h bmp.h decode.h
	$(CC) $(CFLAGS) -c steg.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

decode.o: decode.c decode.h bmp.h
	$(CC) $(CFLAGS) -c decode.c

clean:
	rm -f steg steg.o parser.o

.PHONY: clean
