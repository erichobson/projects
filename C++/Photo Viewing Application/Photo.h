#ifndef PHOTO_H
#define PHOTO_H

#include "Date.h"


class Photo {
		
	public:
        // constructors
        Photo();
        Photo(const string& title, const Date& date, const string& content);

        // other
        bool equals(const string&) const;

        // print
        void print() const;
        void display() const;

    private:
        // variables
        string title;
        string content;
        Date date;
};
#endif