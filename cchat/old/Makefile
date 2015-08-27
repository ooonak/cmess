CC = clang
CFLAGS =-Wall -g

all: test_ds

test_ds: test_ds.o data_structure.o
	$(CC) -o test_ds test_ds.o data_structure.o
clean:
	rm *.o test_ds
