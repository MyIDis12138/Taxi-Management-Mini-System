#ifndef _PRICECAL
#define _PRICECAL
#include "date.h"
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

struct prical
{
	string id1;
	string id2;
	Date startday;
	Date endday;
}; // define a type to store the payments records

class pricecal {
private:
	string file = "";
	int totalline;
public:
	pricecal(string file) {
		this->file = "car_" + file + ".txt";
		totalline = countlines(this->file);
	} // constructor
	prical* read() {
		prical* allre = new prical[totalline];
		int syear;
		int smonth;
		int sday;
		int eyear;
		int emonth;
		int eday;
		string user1 = "";
		string user2 = "";
		ifstream fin(file);
		for (int i = 0; i < totalline; i++) {
			fin >> user1 >> user2 >> syear >> smonth >> sday >> eyear >> emonth >> eday;
			Date starts(syear, smonth, sday);
			Date ends(eyear, emonth, eday);
			allre[i].id1 = user1;
			allre[i].id2 = user2;
			allre[i].startday = starts;
			allre[i].endday = ends;
		}
		fin.close();
		return allre;
	} // read the payments records
	void showrecord(double price) {
		int syear;
		int smonth;
		int sday;
		int eyear;
		int emonth;
		int eday;
		double calpri = 0;
		string user1 = "";
		string user2 = "";
		ifstream fin(file);
		for (int i = 0; i < totalline; i++) {
			fin >> user1 >> user2 >> syear >> smonth >> sday >> eyear >> emonth >> eday;
			Date starts(syear, smonth, sday);
			Date ends(eyear, emonth, eday);
			cout << "Start day: ";
			starts.print();
			cout << "\t" << "End day: ";
			ends.print();
			cout << "\t" << "User: " << user1;
			if (user2 != "None") {
				cout << "\t" << "User 2: " << user2 << endl;
			}
			calpri = (ends - starts + 1) * price;
			cout << "\t" << "Price: " << calpri << endl;
		}
		fin.close();
	} // print all payments records informtion and calculate the price with the time and the pricer per day
	int countlines(string file)
	{
		ifstream readfile(this->file);
		int n = 0;
		string x;
		int syear;
		int smonth;
		int sday;
		int eyear;
		int emonth;
		int eday;
		string user1 = "";
		string user2 = "";
		while (!readfile.eof())
		{
			readfile >> user1 >> user2 >> syear >> smonth >> sday >> eyear >> emonth >> eday;
			n++;
		}
		n--;
		readfile.close();
		return n;
	} // count the lines of the file 
	double pricecalculate(double price, Date endday) {
		prical* allre = new prical[totalline];
		allre = read();
		for (int i = 0; i < totalline; i++) {
			if (allre[i].endday == endday) {
				return (endday - allre[i].startday + 1) * price;
			}
		}
		return 0;
	} // calculate the price with the end day 
	void addborrow(Date startday, string user1, string user2) {
		ofstream fout(file, ios::app);
		fout << user1 << "\t" << user2 << "\t" << startday.getyear() << "\t" << startday.getmonth() << "\t" << startday.getday() << "\t" << 9999 << "\t" << 99 << "\t" << "99" << endl;
		fout.close();
		totalline++;
	} // add a borrow record with one user to the price record file
	void addreturn(Date endday) {
		prical* allre = new prical[totalline];
		allre = read();
		ofstream fout(file);
		for (int i = 0; i < totalline - 1; i++) {
			fout << allre[i].id1 << "\t" << allre[i].id2 << "\t" << allre[i].startday.getyear() << "\t" << allre[i].startday.getmonth() << "\t" << allre[i].startday.getday() << "\t" << allre[i].endday.getyear() << "\t" << allre[i].endday.getmonth() << "\t" << allre[i].endday.getday() << endl;
		}
		fout << allre[totalline - 1].id1 << "\t" << allre[totalline - 1].id2 << "\t" << allre[totalline - 1].startday.getyear() << "\t" << allre[totalline - 1].startday.getmonth() << "\t" << allre[totalline - 1].startday.getday() << "\t" << endday.getyear() << "\t" << endday.getmonth() << "\t" << endday.getday() << endl;
		fout.close();
	}// complete a record to the price record file
	void addborrow(Date startday, string user1) {
		ofstream fout(file, ios::app);
		fout << user1 << "\t" << "None" << "\t" << startday.getyear() << "\t" << startday.getmonth() << "\t" << startday.getday() << "\t" << 9999 << "\t" << 99 << "\t" << "99" << endl;
		fout.close();
		totalline++;
	} // add a borrow record with two users to the price record file
	int getlines() {
		return totalline;
	} // get the lines of the record file
};

#endif // !_PRICECAL