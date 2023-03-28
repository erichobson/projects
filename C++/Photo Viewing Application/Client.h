#ifndef CLIENT_H
#define CLIENT_H

#include "AlbumArray.h"
#include "PhotoGram.h"


class Client {
    public:
        // constructor
        Client();

        // destructor
        ~Client();

        // getter
        bool downloadAlbum(PhotoGram*, const string&) const;

        // print
        bool displayOnlinePhoto(PhotoGram*, const string&, const string&) const;
        bool displayLocalPhoto(const string&, const string&) const;

        void printLocalAlbums() const;
        void displayLocalAlbums() const;

    private:
        // variables
        AlbumArray* albums;
};
#endif