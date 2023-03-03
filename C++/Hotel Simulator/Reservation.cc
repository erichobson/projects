#include "Reservation.h"


// constructor
Reservation::Reservation(string name, Date& checkIn, int duration): checkIn(checkIn) {
    customerName = name;
    setDuration(duration);
}


// functions
// setDuration(): sets the duration of the reservation
void Reservation::setDuration(int d) {
    if (d < 1)
        d = 1;
    duration = d;
}

// overlaps(): returns true if the reservation overlaps with the given reservation
bool Reservation::overlaps(Reservation& r) {
    if (checkIn.lessThan(r.checkIn)){
        Date checkOut = checkIn;
        checkOut.addDays(duration);
        if (checkOut.lessThan(r.checkIn) || checkOut.equals(r.checkIn)) {
            return false;
        } else {
            return true;
        }
    } else {
        Date checkOut = r.checkIn;
        checkOut.addDays(r.duration);
        if (checkOut.lessThan(checkIn) || checkOut.equals(checkIn)) {
            return false;
        } else {
            return true;
        }
    }
}

// lessThan(): returns true if the check-in date is less than the given reservation check-in date
bool Reservation::lessThan(Reservation& res) {
    if (checkIn.lessThan(res.checkIn)) {
        return true;
    } else {
        return false;
    }
}

// lessThan(): returns true if the check-in date is less than the given date
bool Reservation::lessThan(Date& d) {
    if (checkIn.lessThan(d)) {
        return true;
    } else {
        return false;
    }
}

// print(): prints the date of the reservation and associated customer name and duration
void Reservation::print() {
    checkIn.print();
    cout << customerName << " for " << duration << " days." << endl;
}