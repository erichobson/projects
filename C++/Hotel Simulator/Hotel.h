#ifndef HOTEL_H
#define HOTEL_H

#include <iostream>
#include <string>

#include "Room.h"

using namespace std;


class Hotel {
	public:
        // constructor
        Hotel();
        
        // destructor
        ~Hotel();

        // functions
        bool addRoom(int, string, int, bool);
        bool deleteRoom(int);
        bool getRoom(int, Room**);
        bool addReservation(string, string, int, bool, Date &, int);
        void updateReservations(Date &);

        // print
        void print();
        void printReservations();

    private:
        // variables
        Room* rooms[MAX_ROOMS];
        int numRooms;
};
#endif