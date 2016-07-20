#include <iostream>
#include <cstdio>
#include <ctime>

#ifndef __MY_DATE__
#define __MY_DATE__

class Date {
public:
    Date(int y, int m, int d) 
        : year(y), month(m), day(d) 
    {}
    Date():year(0),month(0),day(0){}

    bool operator > (const Date&);
    bool operator < (const Date&);
    bool operator == (const Date&);

    void print();
private:
    int year;
    int month;
    int day;
};

inline bool
Date::operator > (const Date& d) {
    if (this->year != d.year) return this->year > d.year;
    if (this->month != d.month) return this->month > d.month;
    return this->day > d.day;
}

inline bool 
Date::operator < (const Date& d) {
    if(this->year != d.year) return this->year < d.year;
    if(this->month != d.month) return this->month < d.month;
    return this->day < d.day;
}

inline bool 
Date::operator == (const Date& d) {
    return this->year == d.year && this->month == d.month && this->day == d.day; 
}

inline void
Date::print() {
    std::cout << this->year << "-" << this->month << "-" << this->day << std::endl;
}
// judge the year is leap or not
inline bool 
isLeapYear(int year) {
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}

// randomDate generates a random Date object according to certain year range
Date randomDate(int minYear, int maxYear) {
    int range = maxYear - minYear + 1;
    int y = rand() % range + minYear;
    int m = rand() % 12 + 1;
    switch(m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return Date(y, m, rand()%31+1);
        case 4:
        case 6:
        case 9: 
        case 11:
            return Date(y, m, rand()%30+1);
        case 2:
            if (isLeapYear(y)) return Date(y, m, rand()%29+1);
            else               return Date(y, m, rand()%28+1);
    }
    return Date(0, 0, 0);
}

Date* CreatePoints() {
    int dateCount = 10;
    int minYear = 0, maxYear = 3000;
    Date *arr = new Date[dateCount];

    srand(time(NULL)); 
    for (int i = 0;i < dateCount; i++) {
        arr[i] = randomDate(minYear, maxYear);
    }
    return arr;
}

// Sort uses insert sort, warning:results are unstable
void Sort(Date arr[], int num) {
    if (num == 0) return;

    int i, j;
    Date temp;
    for(j = 1; j < num; j++) {
        temp = arr[j]; // store the value in a temporay object
        for(i = j; i > 0 && arr[i-1] > temp; i--) {
            arr[i] = arr[i-1];
        }
        arr[i] = temp;
    }
}

#endif
