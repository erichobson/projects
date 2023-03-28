#ifndef ALBUM_H
#define ALBUM_H

#include "PhotoArray.h"


class Album {

    public:
        // constructor
        Album(const string&, const string&);

        // copy constructor
        Album(Album&);

        // destructor
        ~Album();

        // getters
        string getTitle() const;
        Photo* getPhoto(const string&) const;
        Photo* getPhoto(int) const;
        int size() const;

        // add
        bool addPhoto(Photo*);
        bool addPhoto(int, Photo*);

        // remove
        Photo* removePhoto(const string&) const;
        Photo* removePhoto(int) const;

        // other
        bool equals(const string&) const;
        bool lessThan(const Album&) const;

        // print
        void print() const;
        void display() const;

    private:
        // variables
        PhotoArray* photos;
        string title;
        string description;
};
#endif