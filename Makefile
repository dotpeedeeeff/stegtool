CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11

steg: steg.o parser.o decode.o encode.o helper.o
	$(CC) $(CFLAGS) -o steg steg.o parser.o decode.o encode.o helper.o

steg.o: steg.c parser.h bmp.h decode.h encode.h helper.h
	$(CC) $(CFLAGS) -c steg.c

parser.o: parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

decode.o: decode.c decode.h bmp.h
	$(CC) $(CFLAGS) -c decode.c

encode.o: encode.c encode.h bmp.h
	$(CC) $(CFLAGS) -c encode.c

helper.o: helper.c helper.h bmp.h parser.h
	$(CC) $(CFLAGS) -c helper.c


clean:
	rm -f steg steg.o parser.o decode.o helper.o encode.o

.PHONY: clean
