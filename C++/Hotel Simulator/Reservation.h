#ifndef RESERVATION_H
#define RESERVATION_H

#include <iostream>
#include <string>

#include "Date.h"

using namespace std;


class Reservation {
	public:
        // constructor
        Reservation(string, Date&, int);

        // functions
        void setDuration(int);
        bool overlaps(Reservation&);
        bool lessThan(Reservation&);
        bool lessThan(Date&);

        // print
        void print();

    private: 
        //variables
        string customerName;
        Date checkIn;
        int duration;
};
#endif