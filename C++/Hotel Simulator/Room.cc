#include "Room.h"


// constructor
Room::Room(int roomNumber, string bedType, int capacity, bool hasFridge){
    this->roomNumber = roomNumber;
    this->bedType = bedType;
    this->capacity = capacity;
    this->hasFridge = hasFridge;
    numReservations = 0;
}

// destructor
Room::~Room(){
    for (int i = 0; i < numReservations; ++i){
        delete reservations[i];
    }
}

// getters
int Room::getRoomNumber(){
    return roomNumber;
}

// functions
// isMatch(): returns true if the room matches the given criteria
bool Room::isMatch(string bedType, int capacity, bool hasFridge) {
    if (this->bedType == bedType && this->capacity >= capacity && (hasFridge == false || (this->hasFridge == hasFridge && hasFridge == true))) {
        return true;
    } else {
        return false;
    }
}

// lessThan(): returns true if the room number is less than the given room number
bool Room::lessThan(Room& r) {
    if (roomNumber < r.roomNumber) {
        return true;
    } else {
        return false;
    }
}

// addReservation(): adds a reservation to the room after successful checks
bool Room::addReservation(string name, Date& checkIn, int duration) {
    if (numReservations >= MAX_RES) return false;

    Reservation *r = new Reservation(name, checkIn, duration);

    for (int i = 0; i < numReservations; ++i) {
        if (r->overlaps(*reservations[i])) {
            delete r;
            return false;
        }
    }

    for (int i = 0; i < numReservations; ++i) {
        if (r->lessThan(*reservations[i])) {
            for (int j = numReservations; j > i; --j) {
                reservations[j] = reservations[j-1];
            }
            reservations[i] = r;
            ++numReservations;
            return true;
        }
    }
    reservations[numReservations] = r;
    ++numReservations;
    return true;
}

// updateReservations(): removes the reservations of a room before the given date
void Room::updateReservations(Date &currentDate) {
    for (int i = 0; i < numReservations; ++i) {
        if (reservations[i]->lessThan(currentDate)) {
            delete reservations[i];
            for (int j = i; j < numReservations-1; ++j) {
                reservations[j] = reservations[j+1];
            }
            --i;
            --numReservations;
        }
    }
}

// print
// printReservations(): prints the reservations of a room along with room metadata
void Room::printReservations() {
    cout << endl;
    cout << "------------------------" << endl;
    cout << "Reservations:" << endl;
    print();

    for (int i = 0; i < numReservations; ++i) {
        cout << endl;
        reservations[i]->print();
    }

    if (numReservations == 0) {
        cout << "     0 reservations     " << endl;
    } else {
        cout << endl;
    }

    cout << "------------------------" << endl;
    cout << endl;
}

// print(): prints the metadata of a room
void Room::print() {
    cout << "------------------------" << endl;
    cout << "Room: " << roomNumber << endl;
    cout << "Bed Type: " << bedType << endl;
    cout << "Capacity: " << capacity << endl;
    cout << "Has Fridge: " << std::boolalpha << hasFridge << endl;
    cout << "------------------------" << endl;
}