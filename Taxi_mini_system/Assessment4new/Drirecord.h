#ifndef  _DRIRE
#define _DRIRE

#include <cstring>
#include <string>
#include <iostream>
#include "date.h"
#include "fixpoint.h"
using namespace std;

class Drirecord {
private:
	Date date;
	Fixpoint record;
public:
	Drirecord() {
		date.set(1900, 1, 1);
		record.set(0, 0);
	}// default constructor
	Drirecord(Date date, Fixpoint record) {
		this->date = date;
		this->record = record;
	}// constructor
	void set(Date date, Fixpoint record) {
		this->date = date;
		this->record = record;
	} // set the record 
	Date getdate() {
		return date;
	} // return the date of this record
	Fixpoint getmon() {
		return record;
	} // return the money of this record
	void show() {
		date.print();
		cout << "\t" << record.converFTD() << endl;
	} // print the record on the screen

};
#endif // ! _DRIRE
