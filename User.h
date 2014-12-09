#ifndef _USER_H_
#define _USER_H_

#include <string>

using namespace std;
class User {

private:
	int _id, _accessLevel;
	string _name, _password;

public:
	// Constructor
	User(int id, string name, string password, int accessLevel)
		: _id(id), _name(name), _password(password), _accessLevel(accessLevel) {}

	// Destructor
	~User();

	int getID();
	string getName();
	string getPassword();
	int getAccessLevel();

	// void setName(string name);
	// void setPassword(string password);
	// void setAccessLevel(int accessLevel);

};


#endif