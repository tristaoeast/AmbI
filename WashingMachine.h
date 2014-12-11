#ifndef _WASHINGMACHINE_H_
#define _WASHINGMACHINE_H_

#include <string>

using namespace std;
class WashingMachine {

private:
	int _id, _refDeviceType, _refDivision;
	string _name;
	bool _working, _loaded;

public:
	// Constructor
	WashingMachine(int id, int refDeviceType, string name, int refDivision)
		: _id(id), _name(name), _refDeviceType(refDeviceType), _refDivision(refDivision), _working(false), _loaded(false) {}

	// Destructor
	~WashingMachine();

	int getID();
	string getName();
	int getRefDeviceType();
	int getRefDivision();
	bool isWorking();
	bool isLoaded();

	void setLoaded(bool state);
	void setWorking(bool state);
	// void setName(string name);
	// void setPassword(string refDeviceType);
	// void setAccessLevel(int refDivision);

};


#endif