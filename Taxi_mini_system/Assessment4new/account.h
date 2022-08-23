#ifndef _ACCOUNT
#define _ACCOUNT
#include <string>
#include <iostream>
using namespace std;

class account {
	friend class FileOP;
private:
	string id;
	string password;
public:
	account() {
		id = "";
		password = "";
	};// default constructor
	account(string id, string password) {
		this->id = id;
		this->password = password;
	} // constructor
	string getid();// return the id of this account
	string getpassword();// return the password of this account
	void sets(string id, string password); // set the id and password of this account
	void print(); // print the account information on the screen
};

string account::getid() {
	return id;
}

string account::getpassword() {
	return password;
}
void account::sets(string id, string password) {
	this->id = id;
	this->password = password;
}
void account::print() {
	cout << "ID: " << id << "\t" << "Password: " << password << endl;
}
#endif 