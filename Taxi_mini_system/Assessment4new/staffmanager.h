#include "staff.h"
class staffmanager :public staff {
private:
	string manager_account = "manager_acc.txt";
public:
	staffmanager(account user) {
		this->user = user;
	}
	staffmanager() {
		user.sets("", "");
	}
	bool checkin() {
		FileOp opfile(manager_account);
		return opfile.checkin(user);
	}
	void staffadd(account a) {
		FileOp opfile(staffacc);
		opfile.addaccount(a);
	}
	void deletestaff(string a) {
		FileOp opfile(staffacc);
		opfile.deleteaccount(a);
	}
	void manager_passchange(string pass) {
		string id = user.getid();
		this->user.sets(id, pass);
		FileOp opfile(manager_account);
		opfile.changepassword(user);
	}
	bool ifexist(string id) {
		FileOp opfile(staffacc);
		return opfile.checkacc(id);
	}
	void allstaffshow() {
		FileOp opfile(staffacc);
		opfile.show();
	}
};
