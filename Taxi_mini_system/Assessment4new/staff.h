#ifndef  _STAFF
#define _STAFF
#include "FileOp.h"
#include "FIleRecordh.h"
#include <cstring>
#include <iostream>
#include "carid.h"
#include "pricecal.h"
#include "person.h"
using namespace std;

class staff :public Person {
protected:
	string driacc = "user_account_data.txt";
	string staffacc = "staff_accout_data.txt";
	string smallcar = "small_car.txt";
	string middlecar = "middle_car.txt";
	string bigcar = "big_car.txt";
	int drilines = countlines(driacc);
	int stalines = countlines(staffacc);
public:
	staff(account user) {
		this->user = user;
	}
	staff() {
		user.sets("", "");
	}
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
	}
	void showalldriveracc() {
		FileOp a(driacc);
		account* accounts = new account[drilines];
		accounts = a.read();
		for (int i = 0; i < drilines; i++) {
			accounts[i].print();
		}
	}//find all drivers' accounts;
	account geruser() {
		return user;
	}
	void deletedri(string a) {
		FileOp opfile(driacc);
		opfile.deleteaccount(a);
	}// delete a account;
	string finfpassword(string id) {
		FileOp opflie(driacc);
		int lines = opflie.countlines(driacc);
		account* drivers = new account[lines];
		drivers = opflie.read();
		for (int i = 0; i < lines; i++) {
			if (drivers[i].getid() == id) {
				return drivers[i].getpassword();
			}
		}
	}
	void changepassword_dri(account a) {
		FileOp opfile(driacc);
		opfile.changepassword(a);
	}
	void changepassword_staff(string a) {
		string id = user.getid();
		this->user.sets(id, a);
		FileOp opfile(staffacc);
		opfile.changepassword(user);
	}
	bool checkin() {
		FileOp opfile(staffacc);
		return opfile.checkin(user);
	}
	void addaccount(account a) {
		FileOp opfile(driacc);
		opfile.addaccount(a);
		string files = "driver_" + a.getid() + ".txt";
		ofstream fout(files);
		fout.close();
	}// register a driver account
	void deleterecord(string id, Date day) {
		FileReco a(id);
		int lines = a.serchreco(day);
		if (lines > 0) {
			a.deletereco(day);
		}
		else {
			cout << "No records find" << endl;
		}
	}
	void deleterecord(string id, Date sday, Date eday) {
		FileReco a(id);
		int lines = a.serchreco(sday);
		int lines2 = a.serchreco(eday);
		if (lines * lines2 > 0) {
			a.deletereco(sday, eday);
		}
		else {
			cout << "Error date" << endl;
		}
	}
	void drirecordshow10(string id) {
		FileReco a(id);
		int lines = a.countlines();
		if (lines >= 10) {
			Drirecord* records = new Drirecord[10];
			records = a.read10();
			for (int i = 0; i < 10; i++) {
				records[i].show();
			}
		}
		else {
			drirecordsall(id);
		}
	}
	void drirecordsall(string id) {
		FileReco a(id);
		int lines = a.getlines();
		if (lines > 0) {
			Drirecord* records = new Drirecord[lines];
			records = a.read();
			for (int i = 0; i < lines; i++) {
				records[i].show();
			}
		}
		else {
			cout << "No records" << endl;
		}

	}
	void search_day_rec(string id, Date day) {
		FileReco a(id);
		int lines = a.serchreco(day);
		if (lines > 0) {
			Drirecord* records = new Drirecord[lines];
			records = a.searchread(day);
			for (int i = 0; i < lines; i++) {
				records[i].show();
			}
		}
		else {
			cout << "No records find" << endl;
		}
	}
	void addrecord(string id, Date day, Fixpoint money) {
		FileReco recordopen(id);
		recordopen.addrecord(day, money);
	}
	bool checkacc_dri(string id) {
		FileOp opfile(driacc);
		return opfile.checkacc(id);
	}

	void allcars(int type) {
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
		carid idopne(file);
		int lines = idopne.countlines(file);
		if (lines > 0) {
			vehicles* carsinfo = new vehicles[lines];
			carsinfo = idopne.read();
			for (int i = 0; i < lines; i++) {
				cout << carsinfo[i].id << "\t" << carsinfo[i].occupy << "\t" << carsinfo[i].user1 << "\t" << carsinfo[i].user2 << endl;
			}
		}
		else {
			cout << "No cars find" << endl;
		}

	}
	void addcar(string id, int type) {
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
		carid idopen(file);
		idopen.add(id);
	}
	void deletecar(string id) {
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
		carid idopen(file);
		idopen.deleteid(id);
	}
	void priceinfo(string id) {
		int type = type_of_car(id);
		pricecal idopen(id);
		if (idopen.countlines(id) > 0) {
			double price = 0;
			switch (type)
			{
			case 1:
				price = 150.0;
				break;
			case 2:
				price = 200.0;
				break;
			case 3:
				price = 250.0;
				break;
			default:
				break;
			}
			idopen.showrecord(price);
		}
		else {
			cout << "No records." << endl;
		}
	}
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
	}
	void findusers(string id) {
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
		carid idopen(file);
		cout << "User1: " << idopen.getuser1(id) << "\t" << "User2: " << idopen.getuser2(id);
	}
	void carsborrowed(string user) {
		carid idopen(smallcar);
		int lines = idopen.findcar(user);
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user);
			cout << "Small cars borrowed: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No small car borrowed." << endl;
		}
		idopen.set(middlecar);
		lines = idopen.findcar(user);
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user);
			cout << "Middle cars borrowed: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No middle car borrowed." << endl;
		}
		idopen.set(bigcar);
		lines = idopen.findcar(user);
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user);
			cout << "Big cars borrowed: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No big car borrowed." << endl;
		}
	}
	void carsborrowed(string user1, string user2) {
		carid idopen(smallcar);
		int lines = idopen.findcar(user1, user2);
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user1, user2);
			cout << "Small cars borrowed: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No small car borrowed." << endl;
		}
		idopen.set(middlecar);
		lines = idopen.findcar(user1, user2);
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user1, user2);
			cout << "Middle cars borrowed: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No middle car borrowed." << endl;
		}
		idopen.set(bigcar);
		lines = idopen.findcar(user1, user2);
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.carsborrowed(user1, user2);
			cout << "Big cars borrowed: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No big car borrowed." << endl;
		}
	}
	void avaliablecars() {
		carid idopen(smallcar);
		int lines = idopen.ifallocc();
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.findall();
			cout << "Small cars available: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No small cars available." << endl;
		}
		idopen.set(middlecar);
		lines = idopen.ifallocc();
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.findall();
			cout << "Middle cars available: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No middle cars available." << endl;
		}
		idopen.set(bigcar);
		lines = idopen.ifallocc();
		if (lines > 0) {
			string* cars = new string[lines];
			cars = idopen.findall();
			cout << "Big cars available: " << endl;
			for (int i = 0; i < lines; i++) {
				cout << cars[i] << endl;
			}
		}
		else {
			cout << "No big cars available." << endl;
		}
	}
	void borrow_fordri(string user, string id, Date today) {
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
		carid idopen(file);
		idopen.borrow(id, user);
		pricecal priopen(id);
		priopen.addborrow(today, user);
		cout << "Borrowed successfully. " << endl;
	}
	void borrow_fordri(string user, string user2, string id, Date today) {
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
		carid idopen(file);
		idopen.borrow(id, user, user2);
		pricecal priopen(id);
		priopen.addborrow(today, user, user2);
		cout << "Borrowed successfully. " << endl;
	}
	void returncar(string id, Date today) {
		int type = type_of_car(id);
		string file = "";
		double price = 0;
		switch (type)
		{
		case 1:
			file = smallcar;
			price = 150.0;
			break;
		case 2:
			file = middlecar;
			price = 200;
			break;
		case 3:
			file = bigcar;
			price = 250;
			break;
		default:
			break;
		}
		carid idopen(file);
		idopen.returncar(id);
		pricecal priopen(id);
		priopen.addreturn(today);
		double pay = priopen.pricecalculate(price, today);
		cout << "Successfuly return car " << id << " ,you should pay " << pay << endl;

	}
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
		carid idopen(file);
		return idopen.getoccupy(id);
	}
};

#endif // ! _STAFF