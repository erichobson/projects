#include "AlbumArray.h"


// constructor
AlbumArray::AlbumArray() : albumSize(0) {
    albums = new Album*[MAX_ARRAY];
}


// destructor
AlbumArray::~AlbumArray() {
    delete [] albums;
}


// getters
Album* AlbumArray::get(const string& title) const {
    for (int i = 0; i < albumSize; i++)
    {
        if (albums[i]->equals(title)) {
            return albums[i];
        }
    }
    return NULL;
}

Album* AlbumArray::get(int index) const {
    if (index < 0 || index >= albumSize) {
        return NULL;
    }
    return albums[index];
}

int AlbumArray::size() const {
    return albumSize;
}

bool AlbumArray::isFull() const {
    return albumSize == MAX_ARRAY;
}


// add
bool AlbumArray::add(Album* album) {
    if (isFull()) {
        return false;
    }

    if (albumSize == 0) {
        albums[albumSize++] = album;
        return true;
    }

    int indexToAdd = -1;
    for (int i = 0; i < albumSize; ++i) {
        if (album->lessThan(*albums[i])) {
            indexToAdd = i;
            break;
        }
    }

    if (indexToAdd == -1) {
        albums[albumSize++] = album;
        return true;
    }

    for (int j = albumSize; j > indexToAdd; --j) {
        albums[j] = albums[j-1];
    }

    albums[indexToAdd] = album;
    ++albumSize;
    return true;
}


// remove
Album* AlbumArray::remove(const string& title) {
    for (int i = 0; i < albumSize; i++){
        if (albums[i]->equals(title)) {
            Album* album = albums[i];
            for (int j = i; j < albumSize; j++){
                albums[j] = albums[j+1];
            }
            albumSize--;
            return album;
        }
    }
    return NULL;
}

Album* AlbumArray::remove(int index) {
    if (index < 0 || index >= albumSize) {
        return NULL;
    }
    Album* album = albums[index];
    for (int i = index; i < albumSize; i++){
        albums[i] = albums[i+1];
    }
    albumSize--;
    return album;
}