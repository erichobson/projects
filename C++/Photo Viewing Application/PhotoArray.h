#ifndef PHOTOARRAY_H
#define PHOTOARRAY_H

#include "Photo.h"
#include "defs.h"


class PhotoArray {

    public:
        // constructor
        PhotoArray();

        // destructor
        ~PhotoArray();

        // getters
        Photo* get(const string&) const;
        Photo* get(int) const;
        int getSize() const;
        bool isFull() const;

        // add
        bool add(Photo*);
        bool add(int, Photo*);

        // remove
        Photo* remove(const string&);
        Photo* remove(int);

    private:
        // variables
        Photo** photos;
        int size;
};
#endif