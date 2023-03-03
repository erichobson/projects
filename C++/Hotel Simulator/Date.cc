#include "Date.h"


// constructors
Date::Date(int y, int m, int d) {
	setDate(y,m,d);
}

Date::Date(Date& d) {
    setDate(d.year, d.month, d.day);
}


//setters
void Date::setDay(int d) {
	int max = getMaxDay();
	if (d>max) d=max;
	if (d<1) d=1;
	day = d;
}

void Date::setMonth(int m) {
	if (m > 12) m = 12;
	if (m < 1) m = 1;
	month = m;
}

void Date::setYear(int y) {
	if (y < 1901) y = 1901;
	year = y;
}


void Date::setDate(int y, int m, int d) {
	setMonth(m);
	setDay(d);
	setYear(y);
}

void Date::setDate(Date& d) {
	setDate(d.year, d.month, d.day);
}

void Date::incDate() {
	day += 1;
	if (day > getMaxDay()) {
		day = 1;
		month += 1;
	}

	if (month > 12) {
		month = 1;
		year += 1;
	}
}


//getters
int Date::getDay(){ return day; }
int Date::getMonth(){ return month; }
int Date::getYear(){ return year; }
string Date::getMonthName(){
	string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", 			"November", "December"};
	string smonths[12]={"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul","Aug", "Sep", "Oct", "Nov", "Dec"};
	
	return months[month-1];
}

//other
void Date::print() {
	cout << getMonthName()<<" "<<getDay()<<", "<<getYear()<<endl;
}

// equals(): returns true if this date is the same as d
bool Date::equals(Date& d) {
    return (day == d.day && month == d.month && year == d.year);
}

// lessThan(): returns true if this date is less than d
bool Date::lessThan(Date& d) {
    if (year < d.year) 
        return true;
    else if (year == d.year && month < d.month) 
        return true;
    else if (year == d.year && month == d.month && day < d.day)
        return true;
    else
        return false;
}

// addDays(): adds n days to this date using incDate()
void Date::addDays(int n) {
    for (int i=0; i<n; ++i)
        incDate();
}

int Date::getMaxDay() {
	switch(getMonth()) {
		case 4:
		case 6:
		case 9:
		case 11: 			return 30;
		case 2:				return 28;
		default:			return 31;
	}
}