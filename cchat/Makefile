CC = clang
CFLAGS =-Wall -g
LIBS = -lm

all: client server

server: server.o node_handler.o
	$(CC) -o server server.o node_handler.o

client: client.o node_handler.o
	$(CC) -o client client.o node_handler.o

test_ds: test_ds.o data_structure.o
	$(CC) -o test_ds test_ds.o data_structure.o $(LIBS)
clean:
	rm *.o client server test_ds
