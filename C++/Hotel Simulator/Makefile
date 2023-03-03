all: Date.o Reservation.o Room.o Hotel.o main.o main

main: main.o Reservation.o Date.o Room.o Hotel.o
	g++ -o main main.o Reservation.o Date.o Room.o Hotel.o

main.o: main.cc Reservation.h Date.h Room.h Hotel.h
	g++ -c main.cc

Room.o: Room.cc Room.h
	g++ -c Room.cc

Date.o:	Date.cc Date.h
	g++ -c Date.cc

Reservation.o: Reservation.cc Reservation.h
	g++ -c Reservation.cc

Hotel.o: Hotel.cc Hotel.h
	g++ -c Hotel.cc

clean: 
	rm -f *.o main