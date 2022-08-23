#ifndef _FILEOP
#define _FILEOP


#include <fstream>
#include "account.h"
#include <cstring>
#include <iostream>


class FileOp {
private:
	string file;
	int totoaline;
public:
	FileOp(string file) {
		this->file = file;
		totoaline = countlines(file);
	};// constructor
	account* read();// read the account information 
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
	}// return the total lines of the account file
	void changepassword(account a); // update the password information for a account 
	void addaccount(account a); // add an account information in the account file
	void deleteaccount(string a); // delete an account information in the account file
	bool checkin(account a); // check the account  if correct in the account file
	bool checkacc(string a); //  check the account id  if existed in the account file
	void show(); // print all accounts information
};

account* FileOp::read() {
	account* a = new account[totoaline];
	ifstream fin(file);
	string id = "";
	string pass = "";
	for (int i = 0; i < totoaline; i++) {
		fin >> id >> pass;
		a[i].sets(id, pass);
	}
	fin.close();
	return a;
}

void FileOp::show() {
	ifstream readfile(file);
	string id = "";
	string pas = "";
	int i = 0;
	while (i < totoaline)
	{
		readfile >> id >> pas;
		cout << id << "\t" << pas << endl;
		i++;
	}
	readfile.close();
}

void FileOp::addaccount(account a) {
	ofstream fout(file, ios::app);
	fout << a.getid() << "\t" << a.getpassword() << endl;
	fout.close();
	this->totoaline++;
}

void FileOp::changepassword(account a) {
	account* b = new account[totoaline];
	b = read();
	ofstream fout(file);
	for (int i = 0; i < totoaline; i++) {
		if (a.getid() == b[i].getid()) {
			fout << a.getid() << "\t" << a.getpassword() << endl;
		}
		else {
			fout << b[i].getid() << "\t" << b[i].getpassword() << endl;
		}
	}
	fout.close();
}

void FileOp::deleteaccount(string a) {
	account* b = new account[totoaline];
	b = read();
	ofstream fout(file);
	int lines = totoaline;
	totoaline = 0;
	for (int i = 0; i < lines; i++) {
		if (a == b[i].getid()) {
			continue;
		}
		else {
			fout << b[i].getid() << "\t" << b[i].getpassword() << endl;
			totoaline++;
		}
	}
	fout.close();
	totoaline--;
}

bool FileOp::checkin(account a) {
	ifstream readfile(file);
	string id = "";
	string pas = "";
	int i = 0;
	bool find = false;
	while (i < totoaline)
	{
		readfile >> id >> pas;
		if (a.getid() == id) {
			if (a.getpassword() == pas) {
				return true;
			}
			else
			{
				cout << "Wrong password !" << endl;
			}
			find = true;
		}
		i++;
	}
	readfile.close();
	if (!find) {
		cout << "The account doesn't exist!" << endl;
	}
	return false;
}

bool FileOp::checkacc(string a) {
	ifstream readfile(file);
	string id = "";
	string pas = "";
	int i = 0;
	while (i < totoaline)
	{
		readfile >> id >> pas;
		if (a == id) {
			return true;
		}
		i++;
	}
	return false;
}// true for existed and false for available

#endif // !_FILEOP