#include <fstream>
#include <iostream>
#include <cstring>
#include "staff.h"
#include "Driver.h"
#include "staffmanager.h"
using namespace std;

void Clear_buffer()
{
	int count = 0;
	char c;
	while ((c = getchar()) != '\n');
	return;
}


void createfiles() {
	string driacc = "user_account_data.txt";
	string staffacc = "staff_accout_data.txt";
	string smallcar = "small_car.txt";
	string middlecar = "middle_car.txt";
	string bigcar = "big_car.txt";
	string manager_account = "manager_acc.txt";
	ofstream a(driacc);
	a.close();
	ofstream a1(staffacc);
	a1.close();
	ofstream a2(smallcar);
	a2.close();
	ofstream a3(middlecar);
	a3.close();
	ofstream a4(bigcar);
	a4.close();
	ofstream a5(manager_account);
	a5 << "123456" << "\t" << "123456" << endl;
	a5.close();
}

int gettype() {
	cout << "Please input the type of the car." << endl;
	cout << "1.Small car; 2.Middle car; 3. Big car" << endl;
	int choice = 0;
	cin >> choice;
	return choice;
}

bool catchtype(int type) {
	if (type == 1 || type == 2 || type == 3) {
		return true;
	}
	return false;
}

account getaccout() {
	system("cls");
	cout << "Please input the id number:";
	string id = "";
	cin >> id;
	cout << "Please input the password: ";
	string password = "";
	cin >> password;
	account user(id, password);
	return user;
}

Date gettoday() {
	int year = 0;
	int month = 0;
	int day = 0;
	cout << "Please enter the day informations (Format 'yaer month day') :";
	cin >> year >> month >> day;
	Date today(year, month, day);
	return today;
}

int cutbool(int a) {
	bool success = 0;
	while (success == 0) {
		if (a == 1 || a == 0) {
			return a;
		}
		else {
			cout << "Wrong command! Please try again." << endl;
			cin >> a;
		}
	}
}

int login(account& user) {
	bool success = 0;
	int choice1 = -1;
	int choice2 = -1;
	while (success == 0) {
		cout << "Please choose the mode: 1. Driver; 2. Staff; 3. Manager." << endl;
		cin >> choice1;
		Person* p1;
		switch (choice1)
		{
		case 1:
			system("cls");
			cout << "0. Log in; 1. Register. " << endl;
			cin >> choice2;
			choice2 = cutbool(choice2);
			if (choice2 == 0) {
				user = getaccout();
				p1 = new Driver(user);
				if (p1->checkin()) {
					success = 1;
					cout << "login successfully! " << endl;
					system("pause");
					delete p1;
					return choice1;
				}
				else {
					cout << "Woring accout or wrong password, please try again. " << endl;
				}
				break;
			}
			else if (choice2 == 1) {
				Driver a;
				a.addDriver();
				user = a.getuser();
				success = 1;
				cout << "Register successfully!" << endl;
				system("pause");
				return choice1;
			}
			break;
		case 2:
			user = getaccout();
			p1 = new staff(user);
			if (p1->checkin()) {
				success = 1;
				cout << "login successfully! " << endl;
				system("pause");
				delete p1;
				return choice1;
			}
			else {
				cout << "Woring accout or wrong password, please try again. " << endl;
			}
			break;
		case 3:
			user = getaccout();
			p1 = new staffmanager(user);
			if (p1->checkin()) {
				success = 1;
				cout << "login successfully! " << endl;
				system("pause");
				delete p1;
				return choice1;
			}
			else {
				cout << "Woring accout or wrong password, please try again. " << endl;
			}
			break;
		default:
			cout << "Wrong command." << endl;
			break;
		}
		Clear_buffer();
		cin.clear();
		system("pause");
		system("cls");
	}

}

void carinfomation() {
	cout << "Small  car has 2 seat, it cost 150 per day" << endl;
	cout << "Middle car has 4 seat, it cost 200 per day" << endl;
	cout << "Big    car has 6 seat, it cost 250 per day" << endl;
}

void carsys(account user) {
	system("cls");
	bool out = 0;
	Driver driver(user);
	Date today = gettoday();
	while (out == 0) {
		system("cls");
		int choice;
		cout << "1.borrow a car; 2. return a car; 3.find and borrow a car; 4. car information for each size; 5.out car system" << endl;
		cin >> choice;
		int type = 0;
		int adduser = 0;
		string user2 = "";
		string id = "";
		switch (choice)
		{
		case 1:
			type = gettype();
			if (catchtype(type)) {

				if (driver.numcars() <= 3) {
					cout << "If you want to add another user? 1. Yes 2.No" << endl;
					cin >> adduser;
					if (adduser == 1) {
						cout << "Input the other user id: ";
						cin >> user2;
						if (driver.checkid(user2)) {
							driver.borrow(today, type, user2);
							cout << "Borrowed successfully! " << endl;
						}
						else {
							cout << "Incorrect user number" << endl;
						}
					}
					else {
						driver.borrow(today, type);
						cout << "Borrowed successfully! " << endl;
					}
				}
				else {
					cout << "You can not borrow more than 3 cars.Please return first." << endl;
				}
			}
			else {
				cout << "Incorrect type number." << endl;
			}
			break;
		case 2:
			cout << "Please input the id of the car: ";
			cin >> id;
			if (driver.ifoccupy(id)) {
				driver.returncar(today, id);
			}
			else {
				cout << "Incorrect car id." << endl;
			}
			break;
		case 3:
			cout << "You have borrowed " << driver.numcars() << " cars." << endl;
			driver.borrowedcars();
			break;
		case 4:
			carinfomation();
		case 5:
			out = 1;
			cout << "System out..." << endl;
		default:
			break;
		}
		Clear_buffer();
		cin.clear();
		system("pause");
	}
}

void drivermode(account& user) {
	bool outsys = 0;
	Driver driver(user);
	while (outsys == 0) {
		system("cls");
		int choice1;
		cout << "1.change password.;" << endl;
		cout << "2.show the reputations and punishments.;" << endl;
		cout << "3.show the accout information.;" << endl;
		cout << "4,go to the car system;" << endl;
		cout << "5.log out ;" << endl; 
		cout << "6.out system." << endl;
		cin >> choice1;
		string password = "";
		int choice2;
		switch (choice1)
		{
		case 1:
			system("cls");
			cout << "Please input the new password: ";
			cin >> password;
			driver.changepassword(password);
			cout << "Changed successfully!" << endl;
			user = driver.getuser();
			system("pause");
			break;
		case 2:
			driver.showtheinfo();
			system("pause");
			break;
		case 3:
			user.print();
			system("pause");
			break;
		case 4:
			carsys(user);
			system("pause");
			break;
		case 5:
			system("cls");
			cout << "0. Log in; 1. Register. " << endl;
			cin >> choice2;
			choice2 = cutbool(choice2);
			if (choice2 == 0) {
				bool sublog = 0;
				while (sublog == 0) {
					user = getaccout();
					Driver derivernew(user);
					if (derivernew.checkin()) {
						cout << "login successfully! " << endl;
						sublog = 1;
					}
					else {
						cout << "Woring accout or wrong password, please try again. " << endl;
					}
					system("pause");
				}
				break;
			}
			else if (choice2 == 1) {
				Driver a;
				a.addDriver();
				user = a.getuser();
			}
			system("pause");
			break;
		case 6:
			cout << "System out..." << endl;
			outsys = 1;
			break;
		default:
			break;
		}
		Clear_buffer();
		cin.clear();
	}

}

void Driversmanage(account& user) {
	bool out = 0;
	while (out == 0) {
		system("cls");
		int choice1;
		cout << "1.register a deriver account;" << endl;
		cout << "2.delete a driver;" << endl;
		cout << "3.change password for driver;" << endl;
		cout << "4.find password back;" << endl;
		cout << "5.find driver's record (recent 10);" << endl;
		cout << "6.find driver's record(all); " << endl;
		cout << "7.add a record for driver; " << endl;
		cout << "8.search for record in one day; " << endl;
		cout << "9.find all drivers' accounts;" << endl;
		cout << "10.delte one day's record;" << endl;
		cout << "11.delete records during a period; " << endl;
		cout << "12.out of driver management  " << endl;
		cin >> choice1;
		staff thisfstaff(user);
		account accout1;
		string password = "";
		string id = "";
		switch (choice1)
		{
		case 1:
			accout1 = getaccout();
			if (!thisfstaff.checkacc_dri(accout1.getid())) {
				thisfstaff.addaccount(accout1);
				cout << "Accout: " << accout1.getid() << " has added successfully." << endl;
			}
			else {
				cout << "this account has already existed." << endl;
			}
			system("pause");
			break;
		case 2:
			cout << "Please input the id: ";
			cin >> id;
			if (thisfstaff.checkacc_dri(id)) {
				thisfstaff.deletedri(id);
				cout << "Accout: " << id << " has been deleted successfully." << endl;
			}
			else {
				cout << "this account doesn't  exist." << endl;
			}
			system("pause");
			break;
		case 3:
			accout1 = getaccout();
			if (thisfstaff.checkacc_dri(accout1.getid())) {
				thisfstaff.changepassword_dri(accout1);
				cout << "Changed successfully!" << endl;
				user = thisfstaff.geruser();
			}
			else {
				cout << "The account donesn't exist" << endl;
			}
			system("pause");
			break;
		case 4:
			cout << "Please input the id: ";
			cin >> id;
			password = thisfstaff.finfpassword(id);
			cout << "The password of " << id << " is " << password << endl;
			break;
		case 5:
			cout << "Please input the id: ";
			cin >> id;
			thisfstaff.drirecordshow10(id);
			system("pause");
			break;
		case 6:
			cout << "Please input the id: ";
			cin >> id;
			thisfstaff.drirecordsall(id);
			system("pause");
			break;
		case 7:
			cout << "Please the driver's id: " << endl;
			cin >> id;
			if (thisfstaff.checkacc_dri(id)) {
				cout << "Please input the date(year month day): ";
				int year = 0;
				int month = 0;
				int day = 0;
				cin >> year >> month >> day;
				Date thisday(year, month, day);
				cout << "Please input the money: ";
				double money = 0;
				cin >> money;
				Fixpoint fmoney(money);
				thisfstaff.addrecord(id, thisday, fmoney);
				cout << "Add successfully. " << endl;
			}
			else {
				cout << "This account doesn't exist." << endl;
			}
			system("pause");
			break;
		case 8:
			cout << "Please the driver's id: " << endl;
			cin >> id;
			if (thisfstaff.checkacc_dri(id)) {
				cout << "Please input the date(year month day): ";
				int year = 0;
				int month = 0;
				int day = 0;
				cin >> year >> month >> day;
				Date thisday(year, month, day);
				thisfstaff.search_day_rec(id, thisday);
				cout << "Add successfully! " << endl;
			}
			else {
				cout << "This account doesn't exist." << endl;
			}
			system("pause");
			break;
		case 9:
			thisfstaff.showalldriveracc();
			system("pause");
			break;
		case 10:
			cout << "Please the driver's id: " << endl;
			cin >> id;
			if (thisfstaff.checkacc_dri(id)) {
				cout << "Please input the date(year month day): ";
				int year = 0;
				int month = 0;
				int day = 0;
				cin >> year >> month >> day;
				Date thisday(year, month, day);
				thisfstaff.deleterecord(id, thisday);
				cout << "Delete successfully! " << endl;
			}
			else {
				cout << "This account doesn't exist." << endl;
			}
			system("pause");
			break;
		case 11:
			cout << "Please the driver's id: " << endl;
			cin >> id;
			if (thisfstaff.checkacc_dri(id)) {
				cout << "Please input the start date(year month day): ";
				int year = 0;
				int month = 0;
				int day = 0;
				cin >> year >> month >> day;
				Date sday(year, month, day);
				cout << "Please input the end date(year month day): ";
				cin >> year >> month >> day;
				Date eday(year, month, day);
				thisfstaff.deleterecord(id, sday, eday);
				cout << "Delete successfully! " << endl;
			}
			else {
				cout << "This account doesn't exist." << endl;
			}
			system("pause");
			break;
		case 12:
			out = 1;
			cout << "Out system. Go to the mode chosing. " << endl;
			system("pause");
			break;
		default:
			break;
		}
		Clear_buffer();
		cin.clear();
	}
}

void Carmanage(account& user) {
	bool out1 = 0;
	staff staffone(user);
	int choice;
	while (out1 == 0) {
		system("cls");
		cout << "1.Add a car; " << endl;
		cout << "2.delete a car; " << endl;
		cout << "3.All cars information; " << endl;
		cout << "4.Find all available car; " << endl;
		cout << "5.Borrow a car for users" << endl;
		cout << "6.Return a car; " << endl;
		cout << "7.Find the cars borrowed by user" << endl;
		cout << "8.Find the users of a car; " << endl;
		cout << "9.Price information of a car;" << endl;
		cout << "10.Out system." << endl;
		cin >> choice;
		Date today;
		int num = 0;
		string user1 = "";
		string user2 = "";
		string car_id = "";
		int type = 0;
		switch (choice)
		{
		case 1:
			cout << "Please input the car id: " << endl;
			cin >> car_id;
			if (staffone.type_of_car(car_id) == 0) {
				int type = gettype();
				staffone.addcar(car_id, type);
				cout << "Add successfully!" << endl;
			}
			else {
				cout << "The duplicated car id." << endl;
			}
			break;
		case 2:
			cout << "Please input the car id: " << endl;
			cin >> car_id;
			if (staffone.type_of_car(car_id) != 0) {
				staffone.deletecar(car_id);
				cout << "Delete successfully!" << endl;
			}
			else {
				cout << "The incorrect car id." << endl;
			}
			break;
		case 3:
			type = gettype();
			staffone.allcars(type);
			break;
		case 4:
			staffone.avaliablecars();
			break;
		case 5:
			cout << "The number of users (at least 1, max 2): " << endl;
			cin >> num;
			if (num == 1) {
				cout << "Please input the user's id: ";
				cin >> user1;
				if (staffone.checkacc_dri(user1)) {
					cout << "Please input the car id: ";
					cin >> car_id;
					if (staffone.type_of_car(car_id) != 0) {
						today = gettoday();
						staffone.borrow_fordri(user1, car_id, today);
					}
					else {
						cout << "Incorrect car id." << endl;
					}
				}
				else {
					cout << "Incorrect driver id." << endl;
				}
			}
			else if (num == 2) {
				cout << "Please input the user1's id: ";
				cin >> user1;
				cout << "Please input the user2's id: ";
				cin >> user2;
				if (staffone.checkacc_dri(user1) && staffone.checkacc_dri(user2)) {
					cout << "Please input the car id: ";
					cin >> car_id;
					if (staffone.type_of_car(car_id) != 0) {
						today = gettoday();
						staffone.borrow_fordri(user1, user2, car_id, today);
					}
					else {
						cout << "Incorrect car id." << endl;
					}
				}
				else {
					cout << "Incorrect driver id." << endl;
				}
			}
			else {
				cout << "Incorrect number of users" << endl;
			}
			break;
		case 6:
			cout << "Please input the car id: ";
			cin >> car_id;
			if (staffone.type_of_car(car_id) != 0) {
				if (staffone.ifoccupy(car_id)) {
					today = gettoday();
					staffone.returncar(car_id, today);
					cout << "Successfully return the car" << endl;
				}
				else {
					cout << "This car is available, not occupied." << endl;
				}
			}
			else {
				cout << "Incorrect car id" << endl;
			}
			break;
		case 7:
			cout << "The number of users (at least 1, max 2): " << endl;
			cin >> num;
			if (num == 1) {
				cout << "Please input the user's id: ";
				cin >> user1;
				if (staffone.checkacc_dri(user1)) {
					staffone.carsborrowed(user1);
				}
				else {
					cout << "Incorrect driver id." << endl;
				}
			}
			else if (num == 2) {
				cout << "Please input the user1's id: ";
				cin >> user1;
				cout << "Please input the user2's id: ";
				cin >> user2;
				if (staffone.checkacc_dri(user1) && staffone.checkacc_dri(user2)) {
					staffone.carsborrowed(user1, user2);
				}
				else {
					cout << "Incorrect driver id." << endl;
				}
			}
			else {
				cout << "Incorrect number of users" << endl;
			}
			break;
		case 8:
			cout << "Please input the car id: ";
			cin >> car_id;
			if (staffone.type_of_car(car_id) != 0) {
				if (staffone.ifoccupy(car_id)) {
					cout << "Car is occupied by: ";
					staffone.findusers(car_id);
				}
				else {
					cout << "This car is available, not occupied." << endl;
				}
			}
			else {
				cout << "Incorrect car id" << endl;
			}
			break;
		case 9:
			cout << "Please input the car id: ";
			cin >> car_id;
			if (staffone.type_of_car(car_id) != 0) {
				staffone.priceinfo(car_id);
			}
			else {
				cout << "Incorrect car id" << endl;
			}
			break;
		case 10:
			out1 = 1;
			cout << "System out..." << endl;
			break;
		default:
			break;
		}
		Clear_buffer();
		cin.clear();
		system("pause");
	}
}

void staffmode(account& user) {
	bool out1 = 0;
	staffmanager manager(user);
	bool ifmanager = manager.checkin();
	while (out1 == 0&& !ifmanager) {
		system("cls");
		int choice1;
		cout << "1.Drivers management; 2. Car management; 3. change password; 4.out system. " << endl;
		cin >> choice1;
		bool out2 = 0;
		string password = "";
		staff xiaoming(user);
		switch (choice1)
		{
		case 1:
			Driversmanage(user);
			break;
		case 2:
			Carmanage(user);
			break;
		case 3:
			system("cls");
			cout << "Please input the new password: ";
			cin >> password;
			xiaoming.changepassword_staff(password);
			cout << "Changed successfully!" << endl;
			user = xiaoming.geruser();
			break;
		case 4:
			out1 = 1;
			cout << "System out..." << endl;
			break;
		default:
			break;
		}
		Clear_buffer();
		cin.clear();
		system("pause");
	}
	while (out1 == 0 && ifmanager) {
		system("cls");
		int choice1;
		cout << "1.Drivers management; 2. Car management; 3.out system. " << endl;
		cin >> choice1;
		bool out2 = 0;
		switch (choice1)
		{
		case 1:
			Driversmanage(user);
			break;
		case 2:
			Carmanage(user);
			break;
		case 3:
			out1 = 1;
			cout << "System out..." << endl;
			break;
		default:
			cout << "Incorrect command!" << endl;
			break;
		}
		Clear_buffer();
		cin.clear();
		system("pause");
	}
}

void stafmanagermode(account& user) {
	bool outsys = 0;
	staffmanager manager(user);
	while (outsys == 0) {
		system("cls");
		int choice1;
		cout << "1. change password.; 2. add a staff; 3.delete a staff; 4,go to the staff system;5.show all staffs;6. outsystem; " << endl;
		cin >> choice1;
		string password = "";
		account staffacc;
		staff zhangsan;
		string id = "";
		switch (choice1) {
		case 1:
			system("cls");
			cout << "Please input the new password: ";
			cin >> password;
			manager.manager_passchange(password);
			cout << "Changed successfully!" << endl;
			user = manager.geruser();
			system("pause");
			break;
		case 2:
			staffacc = getaccout();
			if (manager.ifexist(staffacc.getid())) {
				cout << "The account already existed." << endl;
			}
			else {
				manager.staffadd(staffacc);
				cout << staffacc.getid() << " add successfully!" << endl;
			}
			system("pause");
			break;
		case 3:
			cout << "Please input the id: " << endl;
			cin >> id;
			if (!manager.ifexist(id)) {
				cout << "The account doesn't exist." << endl;
			}
			else {
				manager.deletestaff(id);
				cout << staffacc.getid() << " delete successfully!" << endl;
			}
			system("pause");
			break;
		case 4:
			system("cls");
			staffmode(user);
			system("pause");
			break;
		case 5:
			cout << "The account information of all staffs:" << endl;
			manager.allstaffshow();
			system("pause");
			break;
		case 6:
			cout << "System out..." << endl;
			system("pause");
			outsys = 1;
			break;
		default:
			break;
		}
		Clear_buffer();
		cin.clear();
	}

}

int main() {
	//createfiles();
	account user;
	int a = login(user);
	system("cls");
	if (a == 1) {
		drivermode(user);
	}
	else if (a == 3) {
		stafmanagermode(user);
	}
	else if (a == 2) {
		staffmode(user);
	}
}