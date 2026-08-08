CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

steg: steg.o parser.o decode.o encode.o
	$(CC) $(CFLAGS) -o steg steg.o parser.o decode.o encode.o

steg.o: steg.c parser.h bmp.h decode.h encode.h
	$(CC) $(CFLAGS) -c steg.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

decode.o: decode.c decode.h bmp.h
	$(CC) $(CFLAGS) -c decode.c

encode.o: encode.c encode.h bmp.h
	$(CC) $(CFLAGS) -c encode.c


clean:
	rm -f steg steg.o parser.o decode.o

.PHONY: clean
