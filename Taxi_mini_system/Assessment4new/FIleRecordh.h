#ifndef _FILERE
#define _FILERE


#include <cstring>
#include <iostream>
#include <fstream>
#include "Drirecord.h"
#include "fixpoint.h"
using namespace std;

class FileReco {
private:
	int totallines;
	string file = "";
public:
	FileReco(string file = "") {
		this->file = "driver_" + file + ".txt";
		totallines = countlines();
	}; // constructor
	int countlines()
	{
		ifstream readfile;
		int n = 0;
		char buffer[256];
		readfile.open(file, ios::in);
		while (!readfile.eof())
		{
			readfile.getline(buffer, 256, '\n');
			n++;
		}
		n--;
		readfile.close();
		return n;
	} // count the lines of this file
	void addrecord(Date date, Fixpoint money) {
		ofstream fout(file, ios::app);
		fout << date.getyear() << "\t" << date.getmonth() << "\t" << date.getday() << "\t" << money.decimalnum << "\t" << money.index << endl;
		fout.close();
		totallines++;
	} // add a record information at the end of the record file
	Drirecord* read() {
		ifstream fin(file);
		int year;
		int month;
		int day;
		long dec;
		int index;
		Drirecord* record = new Drirecord[totallines];
		Date a;
		Fixpoint b;
		for (int i = 0; i < totallines; i++) {
			fin >> year >> month >> day >> dec >> index;
			a.set(year, month, day);
			b.set(dec, index);
			record[i].set(a, b);
		}
		fin.close();
		return record;
	} // read all record information of the record file 
	Drirecord* read10() {
		if (totallines < 10) {
			return read();
		}
		else {
			Drirecord* record10 = new Drirecord[10];
			Drirecord* record = new Drirecord[totallines];
			record = read();
			int n = 0;
			for (int i = totallines - 10; i < totallines; i++) {
				record10[n].set(record[i].getdate(), record[i].getmon());
				n++;
			}
			return record10;
		}
	} // read recent 10 records information of the record file
	int serchreco(Date a) {
		int lines = countlines();
		if (lines > 0) {
			Drirecord* record = new Drirecord[totallines];
			record = read();
			int n = 0;
			for (int i = 0; i < totallines; i++) {
				Date date = record[i].getdate();
				if (date == a) {
					n++;
				}
			}
			return n;
		}
		else {
			return 0;
		}
	} // return the number of the record in one day
	int getlines() {
		return totallines;
	} // return the lines of the record file
	Drirecord* searchread(Date daya) {
		ifstream fin(file);
		int year;
		int month;
		int day;
		long dec;
		int index;
		int lines = serchreco(daya);
		if (lines > 0) {
			Drirecord* record = new Drirecord[lines];
			int n = 0;
			Date a;
			Fixpoint b;
			for (int i = 0; i < totallines; i++) {
				fin >> year >> month >> day >> dec >> index;
				a.set(year, month, day);
				if (a == daya) {
					b.set(dec, index);
					record[n].set(a, b);
					n++;
				}
			}
			fin.close();
			return record;
		}
	} // return the records information in a sepcific day
	void deletereco(Date date) {
		Drirecord* record = new Drirecord[totallines];
		record = read();
		ofstream fout(file);
		fout.close();
		int lines = totallines;
		totallines = 0;
		int n = 0;
		Date a;
		Fixpoint b;
		for (int i = 0; i < lines; i++) {
			if (record[i].getdate() == date) {
				continue;
			}
			else {
				addrecord(record[i].getdate(), record[i].getmon());
				totallines++;
			}
		}
	} // delete the records in a sepcific day in record file
	void deletereco(Date startday, Date endday) {
		Drirecord* record = new Drirecord[totallines];
		record = read();
		ofstream fout(file);
		fout.close();
		int lines = totallines;
		totallines = 0;
		int n = 0;
		Date a;
		Fixpoint b;
		for (int i = 0; i < lines; i++) {
			if (record[i].getdate() >= startday && record[i].getdate() <= endday) {
				continue;
			}
			else {
				addrecord(record[i].getdate(), record[i].getmon());
				totallines++;
			}
		}
	} // delete the records in a period 
};
#endif // !_FILERE
