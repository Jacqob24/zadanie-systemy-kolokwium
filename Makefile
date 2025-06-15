CC=gcc
CFLAGS=-Wall

all: server client main

server: server.c
	$(CC) $(CFLAGS) -c server.c

client: client.c
	$(CC) $(CFLAGS) -c client.c

main: main.c server.o client.o
	$(CC) $(CFLAGS) -o main main.c server.o client.o

clean:
	rm -f *.o main
