all: tsvToBin appStats

tsvToBin: tsvToBin.o
	gcc -o tsvToBin tsvToBin.o

appStats: appStats.o
	gcc -o appStats appStats.o

tsvToBin.o: apps.h tsvToBin.c
	gcc -c tsvToBin.c

appStats.o: apps.h appStats.c
	gcc -c appStats.c

clean: 
	rm -f *.o *.bin tsvToBin appStats
	