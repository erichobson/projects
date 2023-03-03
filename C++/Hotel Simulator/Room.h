#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>

#include "Reservation.h"
#include "Date.h"
#include "defs.h"

using namespace std;


class Room {
	public:
        // constructor
        Room(int, string, int, bool);

        // destructor
        ~Room();

        // getters
        int getRoomNumber();

        // functions
        bool isMatch(string, int, bool);
        bool lessThan(Room&);
        bool addReservation(string, Date&, int);
        void updateReservations(Date &currentDate);

        // print
        void printReservations();
        void print();
        
    private: 
        // variables
        int roomNumber;
        string bedType;
        int capacity;
        bool hasFridge;
        Reservation* reservations[MAX_RES];
        int numReservations;
};
#endif