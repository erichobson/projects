#ifndef ALBUMARRAY_H
#define ALBUMARRAY_H

#include "Album.h"


class AlbumArray {

    public:
        // constructor
        AlbumArray();

        // destructor
        ~AlbumArray();

        // getters
        Album* get(const string&) const;
        Album* get(int) const;
        int size() const;
        bool isFull() const;

        // add
        bool add(Album*);

        // remove
        Album* remove(const string&);
        Album* remove(int);

    private:
        // variables
        Album** albums;
        int albumSize;
};
#endif