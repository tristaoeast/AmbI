#include <iostream>
#include "WashingMachine.h"

using namespace std;
int WashingMachine::getID() {
	return _id;
}

int WashingMachine::getRefDeviceType() {
	return _refDeviceType;
}

string WashingMachine::getName() {
	return _name;
}

int WashingMachine::getRefDivision() {
	return _refDivision;
}

bool WashingMachine::isLoaded() {
	return _loaded;
}

bool WashingMachine::isWorking() {
	return _working;
}

void WashingMachine::setLoaded(bool state) {
	_loaded = state;
}

void WashingMachine::setWorking(bool state) {
	_working = state;
}
