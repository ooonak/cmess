bazz.o: bazz.c bazz.h
	gcc -c bazz.c

anint.o: anint.c bazz.h
	gcc -c anint.c

anint: anint.o bazz.o bazz.h
	gcc anint.o bazz.o -o anint
