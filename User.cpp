#include <iostream>
#include "User.h"

using namespace std;
int User::getID(){
	return _id;
}

string User::getName(){
	return _name;
}

string User::getPassword(){
	return _password;
}

int User::getAccessLevel(){
	return _accessLevel;
}

string User::getCurrentDivision(){
	return _currentDivision;
}

void User::setCurrentDivision(string division){
	_currentDivision = division;
}

