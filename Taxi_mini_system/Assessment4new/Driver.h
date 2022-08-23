#ifndef _DRIVER
#define _DRIVER


#include "FIleRecordh.h"
#include "FileOp.h"
#include <cstring>
#include <iostream>
#include "person.h"
using namespace std;

class Driver :public Person {
private:
	string accountfile = "user_account_data.txt"; //the account file;
	string repunfile = user.getid(); //the reward and punishment file;
	string smallcar = "small_car.txt";
	string middlecar = "middle_car.txt";
	string bigcar = "big_car.txt";
public:
	Driver();// default constructor
	Driver(account a); // constructor
	void addDriver(); // register a new driver
	bool checkin(); // check the id and the password for login 
	void changepassword(string a); // change the password 
	void showtheinfo(); // read the reward and punishment records (recent added 10)
	account getuser() {
		return user;
	}// return the account of the driver
	void borrow(Date today, int type) {
		string file = "";
		switch (type)
		{
		case 1:
			file = "small_car.txt";
			break;
		case 2:
			file = "middle_car.txt";
			break;
		case 3:
			file = "big_car.txt";
			break;
		default:
			break;
		}
		carid idopen(file);
		string licensenum = "";
		if (idopen.ifallocc() > 0) {
			licensenum = idopen.find();
			pricecal priceopen(licensenum);
			idopen.borrow(licensenum, user.getid());
			priceopen.addborrow(today, user.getid());
			cout << licensenum << " has been successfully borrowed." << endl;
		}
		else {
			cout << "Sorry, all cars have been occupied." << endl;
		}
	} // borrow a car for a driver with different car types
	void borrow(Date today, int type, string user2) {
		string file = "";
		switch (type)
		{
		case 1:
			file = "small_car.txt";
			break;
		case 2:
			file = "middle_car.txt";
			break;
		case 3:
			file = "big_car.txt";
			break;
		default:
			break;
		}
		carid idopen(file);
		string licensenum = "";
		if (idopen.ifallocc() > 0) {
			licensenum = idopen.find();
			pricecal priceopen(licensenum);
			idopen.borrow(licensenum, user.getid(), user2);
			priceopen.addborrow(today, user.getid(), user2);
			cout << licensenum << " has been successfully borrowed." << endl;
		}
		else {
			cout << "Sorry, all cars have been occupied." << endl;
		}
	} // borrow a car for two registed drivers with different car types
	void returncar(Date today, string id) {
		string file = "";
		double carpri = 0;
		int type = type_of_car(id);
		switch (type)
		{
		case 1:
			file = smallcar;
			carpri = 150;
			break;
		case 2:
			file = middlecar;
			carpri = 200;
			break;
		case 3:
			file = bigcar;
			carpri = 250;
			break;
		default:
			break;
		}
		carid idopen(file);
		idopen.returncar(id);
		pricecal calpri(id);
		calpri.addreturn(today);
		double price = calpri.pricecalculate(carpri, today);
		cout << "You should pay: " << price << endl;
		system("pause");
	}// return a car with car id and its type
	int numcars() {
		carid idopen(smallcar);
		int lines = idopen.findcar(user.getid());
		idopen.set(middlecar);
		lines = lines + idopen.findcar(user.getid());
		idopen.set(bigcar);
		lines = lines + idopen.findcar(user.getid());
		return lines;
	} // return the all cars in all types that borrowed by the user
	void borrowedcars() {
		carid idopen(smallcar);
		int lines = idopen.findcar(user.getid());
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user.getid());
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << "\t" << "Small car" << endl;
			}
		}
		idopen.set(middlecar);
		lines = idopen.findcar(user.getid());
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user.getid());
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << "\t" << "Middle car" << endl;
			}
		}
		idopen.set(bigcar);
		lines = idopen.findcar(user.getid());
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user.getid());
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << "\t" << "Big car" << endl;
			}
		}
	}// print all cars information that borrowed by the user
	bool checkid(string id) {
		FileOp driveracc(accountfile);
		return driveracc.checkacc(id);
	} // check the id if it already existed for loging in 
	int type_of_car(string id) {
		carid idopen(smallcar);
		if (idopen.checkid(id)) {
			return 1;
		}
		idopen.set(middlecar);
		if (idopen.checkid(id)) {
			return 2;
		}
		idopen.set(bigcar);
		if (idopen.checkid(id)) {
			return 3;
		}
		return 0;
	} // return the type of the car with its car id
	bool ifoccupy(string id) { //true for occupied
		int type = type_of_car(id);
		string file = "";
		switch (type)
		{
		case 1:
			file = smallcar;
			break;
		case 2:
			file = middlecar;
			break;
		case 3:
			file = bigcar;
			break;
		default:
			break;
		}
		if (type != 0) {
			carid idopen(file);
			return idopen.getoccupy(id);
		}
		else {
			return false;
		}

	}// find the occupied information with the car id
};
Driver::Driver() {
	user.sets("", "");
}
Driver::Driver(account a) {
	user = a;
}

bool Driver::checkin() {
	FileOp driveracc(accountfile);
	return driveracc.checkin(user);
}

void Driver::addDriver() {
	FileOp driveracc(accountfile);
	bool success = false;
	string id = "";
	string password = "";
	while (!success) {
		cout << "Please enter the account id: ";
		cin >> id;
		if (driveracc.checkacc(id)) {
			cout << "The account id has already existed, please try again." << endl;
			system("pause");
			system("cls");
			continue;
		}
		else {
			cout << "Please enter the password: ";
			cin >> password;
			account a(id, password);
			driveracc.addaccount(a);
			ofstream fout("driver_" + id + ".txt");
			fout.close();
			this->user = a;
			success = true;
		}
	}
}

void Driver::changepassword(string a) {
	string id = user.getid();
	this->user.sets(id, a);
	FileOp opfile(accountfile);
	opfile.changepassword(user);
}

void Driver::showtheinfo() {
	FileReco reco(user.getid());
	int lines = reco.countlines();
	if (lines == 0) {
		cout << "No records" << endl;
	}
	else {
		Drirecord* reandpun = new Drirecord[lines];
		reandpun = reco.read10();
		for (int i = 0; i < 10; i++) {
			reandpun[i].show();
		}
	}

}


#endif // !_DRIVER