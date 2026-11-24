CC = gcc
CFLAGS = -Wall -Wextra -g

all: client server

# ATM Client
client: atm.c
	$(CC) $(CFLAGS) atm.c -o client

# Bank Server
server: bank.c
	$(CC) $(CFLAGS) bank.c -o server

clean:
	rm -f client server
