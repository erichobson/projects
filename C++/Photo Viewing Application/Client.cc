#include "Client.h"


// constructor
Client::Client() {
    albums = new AlbumArray();
}


// destructor
Client::~Client() {
    for (int i = 0; i < albums->size(); ++i){
        Album* album = albums->get(i);
        delete album;
    }
    delete albums;
}


// getter
bool Client::downloadAlbum(PhotoGram* pg, const string& albumTitle) const {
    Album* album = pg->downloadAlbum(albumTitle);
    if (album == NULL) {
        // error handled in PhotoGram downloadAlbum()
        return false;
    }

    if (albums->isFull()) {
        cout << "[Client::downloadAlbum] ERROR: albums is full" << endl;
        return false;
    }

    Album* copy = new Album(*album);
    albums->add(copy);

    return true;
}


// print
bool Client::displayOnlinePhoto(PhotoGram* pg, const string& albumTitle, const string& photoTitle) const {
    Photo* photo = pg->downloadPhoto(albumTitle, photoTitle);

    if (photo == NULL) {
        // error handled in PhotoGram downloadPhoto
        return false;
    }

    photo->display();
    return true;
}

bool Client::displayLocalPhoto(const string& albumTitle, const string& photoTitle) const {
    Album* album = albums->get(albumTitle);

    if (album == NULL) {
        cout << "[Client::displayLocalPhoto] ERROR: " << albumTitle << " does not exist" << endl;
        return false;
    }

    Photo* photo = album->getPhoto(photoTitle);
    if (photo == NULL) {
        cout << "[Client::displayLocalPhoto] ERROR: photo " << photoTitle << " in " << albumTitle << " does not exist" << endl;
        return false;
    }

    photo->display();
    return true;
}

void Client::printLocalAlbums() const {
    for (int i = 0; i < albums->size(); i++){
        albums->get(i)->print();
    }
}

void Client::displayLocalAlbums() const {
    for (int i = 0; i < albums->size(); i++){
        albums->get(i)->display();
    }
}

