#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <string>

using namespace std;
class Sensor {

protected:
	int _id, _refDeviceType, _refDivision;
	string _name;

	bool _active;

public:
	// Constructor
	Sensor(int id, int refDeviceType, string name, int refDivision)
		: _id(id), _name(name), _refDeviceType(refDeviceType), _refDivision(refDivision), _active(false) {}

	// Destructor
	~Sensor();

	int getID();
	string getName();
	int getRefDeviceType();
	int getRefDivision();
	bool isActive();

	void setActive(bool state);
	// void setName(string name);
	// void setPassword(string refDeviceType);
	// void setAccessLevel(int refDivision);

};


#endif