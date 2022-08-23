#ifndef  _CARID
#define _CARID
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct  vehicles
{
	string id;
	bool occupy;
	string user1;
	string user2;
}; // construct a type 

class carid {
private:
	string file = "";
	int totallines;
public:
	carid(string file = "") {
		this->file = file;
		totallines = countlines(file);
	} // constructor
	void set(string file) {
		this->file = file;
		totallines = countlines(file);
	} // set the file object
	int countlines(string file)
	{
		ifstream readfile;
		int n = 0;
		string x;
		readfile.open(file, ios::in);
		while (!readfile.eof())
		{
			getline(readfile, x);
			n++;
		}
		n--;
		readfile.close();
		return n;
	} // count the total lines of the fi
	void add(string licence) {
		ofstream fout(file, ios::app);
		fout << licence << "\t" << 0 << "\t" << "None" << "\t" << "None" << endl;
		fout.close();
		ofstream outf("car_" + licence + ".txt");
		outf.close();
		totallines++;
	} // add a car information with the licence of this car
	vehicles* read() {
		vehicles* info = new vehicles[totallines];
		ifstream fin(file);
		for (int i = 0; i < totallines; i++) {
			fin >> info[i].id >> info[i].occupy >> info[i].user1 >> info[i].user2;
		}
		fin.close();
		return info;
	} // read the all cars information and return with a array in vehicales 
	bool checkid(string id) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		for (int i = 0; i < totallines; i++) {
			if (allid[i].id == id) {
				return true;
			}
		}
		return false;
	} // check the id if it exists 
	int ifallocc() {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		int num = 0;
		for (int i = 0; i < totallines; i++) {
			if (allid[i].occupy == 0) {
				num++;
			}
		}
		return num;
	} // return the number of the all available cars
	string* findall() {
		int lines = ifallocc();
		string* cars = new string[lines];
		vehicles* allid = new vehicles[totallines];
		allid = read();
		int n = 0;
		for (int i = 0; i < totallines; i++) {
			if (allid[i].occupy == 0) {
				cars[n] = allid[i].id;
				n++;
			}
		}
		return cars;
	} // return the liences of all available cars
	void deleteid(string id) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		ofstream fout(file);
		for (int i = 0; i < totallines; i++) {
			if (allid[i].id == id) {
				continue;
			}
			else {
				fout << allid[i].id << "\t" << allid[i].occupy << "\t" << allid[i].user1 << "\t" << allid[i].user2 << endl;
			}
		}
		fout.close();
		totallines--;
	} // delete the car with its id
	string find() {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		for (int i = 0; i < totallines; i++) {
			if (allid[i].occupy == 0) {
				return allid[i].id;
			}
		}
		return "";
	}// return a available car 
	void borrow(string id, string user) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		ofstream fout(file);
		for (int i = 0; i < totallines; i++) {
			if (allid[i].id == id) {
				fout << allid[i].id << "\t" << 1 << "\t" << user << "\t" << "None" << endl;
			}
			else {
				fout << allid[i].id << "\t" << allid[i].occupy << "\t" << allid[i].user1 << "\t" << allid[i].user2 << endl;
			}
		}
		fout.close();
	}// update the borrow infomation with 1 user
	void borrow(string id, string user1, string user2) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		ofstream fout(file);
		for (int i = 0; i < totallines; i++) {
			if (allid[i].id == id) {
				fout << allid[i].id << "\t" << 1 << "\t" << user1 << "\t" << user2 << endl;
			}
			else {
				fout << allid[i].id << "\t" << allid[i].occupy << "\t" << allid[i].user1 << "\t" << allid[i].user2 << endl;
			}
		}
		fout.close();
	}// update the borrow infomation with 2 users
	void returncar(string id) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		ofstream fout(file);
		for (int i = 0; i < totallines; i++) {
			if (allid[i].id == id) {
				fout << allid[i].id << "\t" << 0 << "\t" << "None" << "\t" << "None" << endl;
			}
			else {
				fout << allid[i].id << "\t" << allid[i].occupy << "\t" << allid[i].user1 << "\t" << allid[i].user2 << endl;
			}
		}
		fout.close();
	}// update the return infomation
	bool getoccupy(string id) { //true for occupied, false for available
		vehicles* allid = new vehicles[totallines];
		allid = read();
		for (int i = 0; i < totallines; i++) {
			if (allid[i].id == id) {
				if (allid[i].occupy == 0) {
					return false;
				}
				else {
					return true;
				}
			}
		}
	}// return the occupy information of a car with its car id
	string getuser1(string id) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		bool iffind = false;
		for (int i = 0; i < totallines; i++) {
			if (allid[i].id == id) {
				iffind = true;
				return allid[i].user1;
			}
		}
		if (!iffind) {
			cout << "not find!" << endl;
			return "";
		}
	}// return the user1 of a car with its car id
	string getuser2(string id) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		bool iffind = false;
		for (int i = 0; i < totallines; i++) {
			if (allid[i].id == id) {
				iffind = true;
				return allid[i].user2;
			}
		}
		if (!iffind) {
			cout << "not find!" << endl;
			return "";
		}
	}// return the user2 of a car with its car id
	int findcar(string user1, string user2) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		int n = 0;
		for (int i = 0; i < totallines; i++) {
			if ((allid[i].user1 == user1 && allid[i].user2 == user2) || (allid[i].user2 == user1 && allid[i].user1 == user2)) {
				n++;
			}
		}
		return n;
	}// find the number of the cars which borrowed with both two users.
	int findcar(string user1) {
		vehicles* allid = new vehicles[totallines];
		allid = read();
		int n = 0;
		for (int i = 0; i < totallines; i++) {
			if ((allid[i].user1 == user1) || (allid[i].user2 == user1)) {
				n++;
			}
		}
		return n;
	}// find the number of the cars which borrowed by a user
	string* carsborrowed(string user1) {
		string* carsid = new string[findcar(user1)];
		vehicles* allid = new vehicles[totallines];
		allid = read();
		int n = 0;
		for (int i = 0; i < totallines; i++) {
			if ((allid[i].user1 == user1) || (allid[i].user2 == user1)) {
				carsid[n] = allid[i].id;
				n++;
			}
		}
		return carsid;
	}// find the cars' ids that borrowed by the user
	string* carsborrowed(string user1, string user2) {
		string* carsid = new string[findcar(user1)];
		vehicles* allid = new vehicles[totallines];
		allid = read();
		int n = 0;
		for (int i = 0; i < totallines; i++) {
			if ((allid[i].user1 == user1 && allid[i].user2 == user2) || (allid[i].user2 == user1 && allid[i].user1 == user2)) {
				carsid[n] = allid[i].id;
				n++;
			}
		}
		return carsid;
	}// find the cars' ids that borrowed with both two users

};

#endif // ! _CARID