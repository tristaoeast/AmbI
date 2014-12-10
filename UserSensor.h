#ifndef _USERSENSOR_H_
#define _USERSENSOR_H_

#include <string>

using namespace std;
class UserSensor {

protected:
	int _id, _refDeviceType, _refDivision, _counter;
	string _name;
	string _chandler, _monica;
	bool _active;

public:
	// Constructor
	UserSensor(int id, int refDeviceType, string name, int refDivision, string chandler, string monica)
		: _id(id), _name(name), _refDeviceType(refDeviceType), _refDivision(refDivision), _chandler(chandler), _monica(monica), _active(false), _counter(0) {}

	// Destructor
	~UserSensor();

	int getID();
	string getName();
	int getRefDeviceType();
	int getRefDivision();
	bool isActive();
	int getCounter();

	void setCounter(int c);
	void incCounter();
	void decCounter();
	void setActive(bool state);
	// void setName(string name);
	// void setPassword(string refDeviceType);
	// void setAccessLevel(int refDivision);

};


#endif