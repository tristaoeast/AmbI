#include <iostream>
#include "VacuumCleaner.h"

using namespace std;
int VacuumCleaner::getID(){
	return _id;
}

int VacuumCleaner::getRefDeviceType(){
	return _refDeviceType;
}

string VacuumCleaner::getName(){
	return _name;
}

int VacuumCleaner::getRefDivision(){
	return _refDivision;
}

bool VacuumCleaner::isWorking() {
	return _working;
}

void VacuumCleaner::setWorking(bool state) {
	_working = state;
}
