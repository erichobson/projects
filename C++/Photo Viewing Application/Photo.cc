#include "Photo.h"


// constructors
Photo::Photo() : Photo("Title", Date(1,1,2000), "Content")
{ }

Photo::Photo(const string &title, const Date &date, const string &content)
    : title(title), date(date), content(content)
{ }


// other
bool Photo::equals(const string &title) const{
    return this->title == title;
}


// print
void Photo::print() const {
    cout << "Title: " << title << endl;
    cout << "Date: " ;
    date.print();
    cout << endl;
}

void Photo::display() const {
    print();
    cout << "Content: " << content << endl; 
}
