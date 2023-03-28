#include "PhotoGram.h"


// constructor
PhotoGram::PhotoGram() {
    albumArray = new AlbumArray();
}


// destructor
PhotoGram::~PhotoGram() {
    for (int i = 0; i < albumArray->size(); ++i) {
        Album *album = albumArray->get(i);
        delete album;
    }
    delete albumArray;
}


// add
bool PhotoGram::addAlbum(const string& title, const string& description) {
    if(albumArray->isFull()) {
        cout << "[PhotoGram::addAlbum] ERROR: albumArray is full" << endl;
        return false;
    }

    Album* album = new Album(title, description);
    return albumArray->add(album);
}

bool PhotoGram::addPhoto(const string& albumTitle, const Photo& photo) {
    Album* album = albumArray->get(albumTitle);
    if (album == NULL) {
        cout << "[PhotoGram::addPhoto] ERROR: " << albumTitle << " does not exist" << endl;
        return false;
    }

    Photo* photoPtr = new Photo();
    *photoPtr = photo;
    return album->addPhoto(photoPtr);
}


// remove
bool PhotoGram::removeAlbum(const string& albumTitle) {
    Album* album = albumArray->get(albumTitle);

    if (album == NULL) {
        cout << "[PhotoGram::removeAlbum] ERROR: " << albumTitle << " does not exist" << endl;
        return false;
    }

    albumArray->remove(albumTitle);
    delete album;
    return true;
}

bool PhotoGram::removePhoto(const string& albumTitle, const string& photoTitle) {
    Album* album = albumArray->get(albumTitle);

    if (album == NULL) {
        cout << "[PhotoGram::removePhoto] ERROR: " << albumTitle << " does not exist" << endl;
        return false;
    }

    Photo* photo = album->removePhoto(photoTitle);
    if (photo == NULL) {
        cout << "[PhotoGram::removePhoto] ERROR: photo " << photoTitle << " in " << albumTitle << " does not exist" << endl;
        return false;
    }

    delete photo;
    return true;
}


// get
Album* PhotoGram::downloadAlbum(const string& albumTitle) const{
    Album *album = albumArray->get(albumTitle);

    if (album == NULL) {
        cout << "[PhotoGram::downloadAlbum] ERROR: " << albumTitle << " does not exist" << endl;
        return NULL;
    }

    return album;
}

Photo* PhotoGram::downloadPhoto(const string& albumTitle, const string& photoTitle) const {
    Album* album = albumArray->get(albumTitle);

    if (album == NULL) {
        cout << "[PhotoGram::downloadPhoto] ERROR: " << albumTitle << " does not exist" << endl;
        return NULL;
    }

    Photo* photo = album->getPhoto(photoTitle);
    if (photo == NULL) {
        cout << "[PhotoGram::downloadPhoto] ERROR: photo " << photoTitle << " in " << albumTitle << " does not exist" << endl;
        return NULL;
    }

    return photo;
}


// print
void PhotoGram::printAlbums() const {
    for (int i = 0; i < albumArray->size(); i++) {
        albumArray->get(i)->print();
    }
}

void PhotoGram::displayAlbums() const {
    for (int i = 0; i < albumArray->size(); i++) {
        albumArray->get(i)->display();
    }
}