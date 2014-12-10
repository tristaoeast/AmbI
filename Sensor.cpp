#include <iostream>
#include "Sensor.h"

using namespace std;
int Sensor::getID(){
	return _id;
}

int Sensor::getRefDeviceType(){
	return _refDeviceType;
}

string Sensor::getName(){
	return _name;
}

int Sensor::getRefDivision(){
	return _refDivision;
}

bool Sensor::isActive() {
	return _active;
}

void Sensor::setActive(bool state) {
	_active = state;
}

