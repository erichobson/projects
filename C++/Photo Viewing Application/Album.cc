#include "Album.h"


// constructor
Album::Album(const string& title, const string& description)
    : title(title), description(description) {
    photos = new PhotoArray[MAX_ARRAY];
}


// copy constructor
Album::Album(Album& album) : Album(album.title, album.description) {
    for (int i = 0; i < album.size(); ++i){
        Photo* photo = new Photo();
        *photo = *album.getPhoto(i);
        photos->add(photo);
    }
}


// destructor
Album::~Album() {
    delete[] photos;
}


// getters
string Album::getTitle() const {
    return title;
}

Photo* Album::getPhoto(const string& title) const {
    return photos->get(title);
}

Photo* Album::getPhoto(int index) const {
    return photos->get(index);
}

int Album::size() const {
    return photos->getSize();
}


// add
bool Album::addPhoto(Photo* photo){
    if (photos->isFull())
        return false;

    photos->add(photo);
    return true;
}

bool Album::addPhoto(int index, Photo* photo) {
    if (photos->isFull())
        return false;

    if (index < 0 || index > photos->getSize())
        return false;

    photos->add(index, photo);
    return true;
}


// remove
Photo* Album::removePhoto(const string& title) const {
    return photos->remove(title);
}

Photo* Album::removePhoto(int index) const {
    return photos->remove(index);
}


// other
bool Album::equals(const string &title) const {
    return this->title == title;
}

bool Album::lessThan(const Album& alb) const {
    return title < alb.title;
}


// print
void Album::print() const {
    cout << "Album: " << title << endl;
    cout << "Description: " << description << endl;
}

void Album::display() const {
    print();
    cout << "Photos: " << endl;
    for (int i = 0; i < photos->getSize(); i++)
        photos->get(i)->display();
}