#ifndef _VACUUMCLEANER_H_
#define _VACUUMCLEANER_H_

#include <string>

using namespace std;
class VacuumCleaner {

private:
	int _id, _refDeviceType, _refDivision;
	string _name;
	bool _working;

public:
	// Constructor
	VacuumCleaner(int id, int refDeviceType, string name, int refDivision)
		: _id(id), _name(name), _refDeviceType(refDeviceType), _refDivision(refDivision), _working(false) {}

	// Destructor
	~VacuumCleaner();

	int getID();
	string getName();
	int getRefDeviceType();
	int getRefDivision();
	bool isWorking();


	void setWorking(bool state);
	// void setName(string name);
	// void setPassword(string refDeviceType);
	// void setAccessLevel(int refDivision);

};


#endif