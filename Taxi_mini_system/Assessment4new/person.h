#ifndef _PERSON
#define _PERSON
#include "account.h"
class Person {
protected:
	account user;
public:
	Person(account user) {
		this->user = user;
	} // constructor
	Person() {
		user.sets("", "");
	}//default constructor
	void set(account user) {
		this->user = user;
	} // set the user
	virtual bool checkin() = 0; // for account check in 
};

#endif // !_PERSON
