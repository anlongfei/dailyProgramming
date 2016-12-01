.PHONY:clean all
CC=gcc
CFLAGS=-Wall -g
BIN=epoll client conn
all:$(BIN)
%.o:%.c
	$(CC) $(CFLAGS) -c $< -o %@
clean:
	rm -f *.o $(BIN)
