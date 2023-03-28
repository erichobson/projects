#ifndef PHOTOGRAM_H
#define PHOTOGRAM_H

#include "AlbumArray.h"


class PhotoGram {
    public:
        // constructor
        PhotoGram();

        // destructor
        ~PhotoGram();

        // add
        bool addAlbum(const string&, const string&);
        bool addPhoto(const string&, const Photo&);

        // remove
        bool removeAlbum(const string&);
        bool removePhoto(const string&, const string&);

        // get
        Album* downloadAlbum(const string&) const;
        Photo* downloadPhoto(const string&, const string&) const;

        // print
        void printAlbums() const;
        void displayAlbums() const;

    private:
        // variables
        AlbumArray *albumArray;
};
#endif