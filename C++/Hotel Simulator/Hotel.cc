#include "Hotel.h"


// constructor
Hotel::Hotel() {
    numRooms = 0;
}

// destructor
Hotel::~Hotel() {
    for (int i=0; i<numRooms; ++i) {
        delete rooms[i];
    }
}

// functions
// addRoom(): adds a room to the hotel after successful checks and adjusts array accordingly
bool Hotel::addRoom(int roomNumber, string bedType, int capacity, bool hasFridge) {
    if (numRooms >= MAX_ROOMS) return false;
    
    for (int i=0; i<numRooms; ++i) {
        if (rooms[i]->getRoomNumber() == roomNumber) return false;
    }

    Room *newRoom = new Room(roomNumber, bedType, capacity, hasFridge);

    for (int i = 0; i < numRooms; ++i) {
        if (newRoom->lessThan(*rooms[i])) {
            for (int j = numRooms; j > i; --j) {
                rooms[j] = rooms[j-1];
            }
            rooms[i] = newRoom;
            ++numRooms;
            return true;
        }
    }
    rooms[numRooms] = newRoom;
    ++numRooms;
    return true;
}

// deleteRoom(): deletes a room from the hotel and adjusts array accordingly
bool Hotel::deleteRoom(int roomNumber) {
    for (int i=0; i<numRooms; ++i){
        if (rooms[i]->getRoomNumber() == roomNumber) {
            delete rooms[i];
            for (int j=i; j<numRooms-1; ++j) {
                rooms[j] = rooms[j+1];
            }
            --numRooms;
            return true;
        }
    }
    return false;
}

// getRoom(): returns a pointer to the room with the given room number
bool Hotel::getRoom(int roomNumber, Room **room) {
    for (int i=0; i<numRooms; ++i){
        if (rooms[i]->getRoomNumber() == roomNumber) {
            *room = rooms[i];
            return true;
        }
    }
    return false;
}

// addReservation(): adds a reservation to the hotel after successful checks
bool Hotel::addReservation(string name, string bedType, int capacity, bool hasFridge, Date &startDate, int numDays) {
    for (int i=0; i<numRooms; ++i) {
        if (rooms[i]->isMatch(bedType, capacity, hasFridge)) {
            if (rooms[i]->addReservation(name, startDate, numDays)) {
                return true;
            }
        }
    }
    return false; 
}

// updateReservations(): iterates through all the rooms and updates their reservations
void Hotel::updateReservations(Date &date) {
    for (int i=0; i<numRooms; ++i) {
        rooms[i]->updateReservations(date);
    }
}

// print
// print(): prints the hotel's rooms
void Hotel::print() {
    cout << endl << endl;
    cout << "------------------------" << endl;
    cout << "------------------------" << endl;
    cout << "Hotel with " << numRooms << " rooms:" << endl;
    for (int i=0; i<numRooms; ++i) {
        rooms[i]->print();
    }
    cout << "------------------------" << endl;
}

// printReservations(): prints the hotel's rooms and their reservations
void Hotel::printReservations() {
    cout << endl << endl;
    cout << "------------------------" << endl;
    cout << "------------------------" << endl;
    cout << "Printing Hotel rooms\nand reservations:" << endl;
    for (int i = 0; i < numRooms; ++i)
    {
        rooms[i]->printReservations();
    }
    cout << "------------------------" << endl;
}   