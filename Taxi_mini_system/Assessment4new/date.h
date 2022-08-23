#ifndef _DATE
#define _DATE
#include <cstring>
#include <iostream>
using namespace std;


// these three functions to cut the year, month and day
int yearcut(int year) {
	if (year > 9999 || year < 1000) {
		return 1900;
	}
	else {
		return year;
	}
}

int monthcut(int month) {
	if (month > 12 || month < 1) {
		return 1;
	}
	else {
		return month;
	}
}

int daycut(int day) {
	if (day > 31 || day < 1) {
		return 1;
	}
	else {
		return day;
	}
}

class Date {
private:
	int year;
	int month;
	int day;
public:
	Date(int year = 1900, int month = 1, int day = 1) {
		year = yearcut(year);
		month = monthcut(month);
		day = daycut(day);
		this->year = year;
		this->month = month;
		this->day = day;
	}// constructor
	void set(int year, int month, int day) {
		this->year = year;
		this->month = month;
		this->day = day;
	}// set the date
	void print() {
		cout << year << "/" << month << "/" << day;
	}// print the date on the screen
	int getyear() {
		return year;
	}// return the year of the date
	int getmonth() {
		return month;
	}// return the month of the date
	int getday() {
		return day;
	}// return the day of the date
	bool operator == (Date a) {
		return (a.getyear() == year && a.getmonth() == month && a.getday() == day);
	}// operator overloading ==
	bool operator > (Date a) {
		if (year > a.getyear()) {
			return true;
		}
		else if (year == a.getyear()) {
			if (month > a.getmonth()) {
				return true;
			}
			else if (month == a.getmonth()) {
				if (day > a.getday()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}// operator overloading >
	bool operator < (Date a) {
		if (year < a.getyear()) {
			return true;
		}
		else if (year == a.getyear()) {
			if (month < a.getmonth()) {
				return true;
			}
			else if (month == a.getmonth()) {
				if (day < a.getday()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}// operator overloading <
	bool operator >= (Date a) {
		if (year > a.getyear()) {
			return true;
		}
		else if (year == a.getyear()) {
			if (month > a.getmonth()) {
				return true;
			}
			else if (month == a.getmonth()) {
				if (day >= a.getday()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}// operator overloading >=
	bool operator <= (Date a) {
		if (year < a.getyear()) {
			return true;
		}
		else if (year == a.getyear()) {
			if (month < a.getmonth()) {
				return true;
			}
			else if (month == a.getmonth()) {
				if (day <= a.getday()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}// operator overloading <=
	int operator - (Date a) {
		return (year - a.year) * 365 + (month - a.month) * 30 + (day - a.day);
	}// operator overloading -
};

#endif // !_DATE
