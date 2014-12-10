#include <iostream>
#include "UserSensor.h"

using namespace std;
int UserSensor::getID(){
	return _id;
}

int UserSensor::getRefDeviceType(){
	return _refDeviceType;
}

string UserSensor::getName(){
	return _name;
}

int UserSensor::getRefDivision(){
	return _refDivision;
}

bool UserSensor::isActive() {
	return _active;
}

void UserSensor::setCounter(int c) {
	_counter = c;
}

void UserSensor::decCounter() {
	_counter--;
	if(_counter==0)
		_active=false;
}

void UserSensor::incCounter() {
	_counter++;
	_active=true;
}

void UserSensor::setActive(bool state) {
	_active = state;
}
