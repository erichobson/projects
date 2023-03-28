#include "PhotoArray.h"


// constructor
PhotoArray::PhotoArray() : size(0) {
    photos = new Photo*[MAX_ARRAY];
}


// destructor
PhotoArray::~PhotoArray() {
    for (int i = 0; i < size; i++){
        delete photos[i];
    }
    delete [] photos;
}


// getters
Photo* PhotoArray::get(const string& title) const {
    for (int i = 0; i < size; ++i){
        if (photos[i]->equals(title)) {
            return photos[i];
        }
    }
    return NULL;
}

Photo* PhotoArray::get(int index) const{
    if (index < 0 || index >= size) {
        return NULL;
    }
    return photos[index];
}

int PhotoArray::getSize() const {
    return size;
}

bool PhotoArray::isFull() const {
    return size == MAX_ARRAY;
}


// add
bool PhotoArray::add(Photo* photo) {
    if (isFull()) {
        return false;
    }
    
    photos[size++] = photo;
    return true;
}

bool PhotoArray::add(int index, Photo* photo) {
    if (isFull()) {
        return false;
    }

    if (index < 0 || index > size) {
        return false;
    }

    for (int i = size; i > index; --i) {
        photos[i] = photos[i-1];
    }

    photos[index] = photo;
    ++size;
    return true;
}


// remove
Photo* PhotoArray::remove(const string& title) {
    for (int i = 0; i < size; ++i) {
        if (photos[i]->equals(title)) {
            return remove(i);
        }
    }
    return NULL;
}

Photo* PhotoArray::remove(int index) {
    if (index < 0 || index >= size) {
        return NULL;
    }

    Photo* photo = photos[index];

    for (int i = index; i < size-1; ++i) {
        photos[i] = photos[i+1];
    }

    --size;
    return photo;
}