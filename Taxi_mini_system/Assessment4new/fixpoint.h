#ifndef  _FIXPOINT
#define _FIXPOINT

#include <iostream>
using namespace std;

class Fixpoint {
public:
	long decimalnum;
	int index;
	Fixpoint(double a) {
		if (abs(a) < 0.0001) {
			decimalnum = 0;
			index = 0;
		}
		else {
			index = 0;
			while ((abs(a - (int)a) != 0) && index > -4) {
				a = a * 10;
				index--;
			}
			decimalnum = (int)a;
		}
	} // constructor with a double number
	Fixpoint(long decimalnum = 0, int index = 0) {
		this->decimalnum = decimalnum;
		if (index < -4) {
			this->index = index;
		}
		else {
			this->index = -4;
		}
	}// constructor with a deciaml number and the index number
	void set(long decimalnum, int index) {
		this->decimalnum = decimalnum;
		this->index = index;
	}// set with a deciaml number and the index number
	void set(double a) {
		if (abs(a) < 0.0001) {
			decimalnum = 0;
			index = 0;
		}
		else {
			index = 0;
			while ((abs(a - (int)a) != 0) && index > -4) {
				a = a * 10;
				index--;
			}
			decimalnum = (int)a;
		}
	}// set with a double number
	void print() {
		if (index < 0) {
			cout << decimalnum << "* 10^" << index << endl;
		}
		else {
			cout << decimalnum << endl;
		}
	} // print the fixed point on the screen
	double converFTD() {
		double out = decimalnum;
		for (int i = 0; i < -index; i++) {
			out /= 10;
		}
		return out;
	} // convert a fixed point into  a double number
	Fixpoint operator= (double a) {
		if (a < 0.0001) {
			decimalnum = 0;
			index = 0;
		}
		else {
			index = 0;
			while ((a - (int)a > 0) && index > -4) {
				a = a * 10;
				index--;
			}
			decimalnum = (int)a;
		}
	}// operation overloading =
	Fixpoint operator+ (Fixpoint a) {
		return Fixpoint(converFTD() + a.converFTD());
	}// operation overloading +
	Fixpoint operator- (Fixpoint a) {
		return Fixpoint(converFTD() - a.converFTD());
	}// operation overloading -
	Fixpoint operator* (Fixpoint a) {
		return Fixpoint(converFTD() * a.converFTD());
	}// operation overloading *
	Fixpoint operator/ (Fixpoint a) {
		return Fixpoint(converFTD() / a.converFTD());
	}// operation overloading /
};
#endif // ! _FIXPOINT