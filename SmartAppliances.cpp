#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include "User.h"

using namespace std;
using namespace pugi;

int userIDCounter = 0, deviceIDCounter = 0;
string specFilename = "dbspec.xml";
xml_document doc;

char* strToCharArray (string str) {
	char * cstr = new char [str.length()+1];
  strcpy (cstr, str.c_str());
  return cstr;
}

string getInput() {

}

int charArrayToInteger(const char* value) {
	stringstream strValue;
	strValue << value;

	int intValue;
	strValue >> intValue;
	return intValue;
}

int getIntegerFromInput(string display) {
	int integer;
	while(true){
		cout << display;
		cin >> integer;

		// CHECKS IF THERE'S SOMETHING WRONG WITH THE INPUT (NOT AN INTEGER FOR EXAMPLE)
		if(cin.fail()) {
			cin.clear();
			string dummy;
	  	cin >> dummy; // throw away garbage.
			cout << "\nInvalid input type. Please insert a valid number.\n\n";
			continue;
			}

		else
			cout << endl;
			return integer;
	}
}

// void SetStdinEcho(bool enable)
// {
// #ifdef WIN32
//     HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE); 
//     DWORD mode;
//     GetConsoleMode(hStdin, &mode);

//     if( !enable )
//         mode &= ~ENABLE_ECHO_INPUT;
//     else
//         mode |= ENABLE_ECHO_INPUT;

//     SetConsoleMode(hStdin, mode );

// #else
//     struct termios tty;
//     tcgetattr(STDIN_FILENO, &tty);
//     if( !enable )
//         tty.c_lflag &= ~ECHO;
//     else
//         tty.c_lflag |= ECHO;

//     (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
// #endif
// }

void addDeviceToDBS(xml_node domobus) {
	string deviceName;
	string password;
	int accesLevel;
	cout << "Please enter the device name: ";
	cin >> deviceName;
	cout << "Please enter the dsired password for user " + username + ": ";
	// SetStdinEcho(false);
	cin >> password;
	// SetStdinEcho(true);
	while(true) {
		accesLevel = getIntegerFromInput("Please enter the access level for user " + username + ": ");
		if(accesLevel >= 1 && accesLevel <= 10)
			break;
		else {
			cout << "Invalid access level. Please input a value between 1 and 10, inclusive.\n\n";
			continue;
		}
	}
	// add node with name User
	xml_node ul = domobus.child("UserList");
	xml_node user = ul.append_child();
	user.set_name("User");
	user.append_attribute("ID") = ++userIDCounter;
	user.append_attribute("Name") = strToCharArray(username);
	user.append_attribute("Password") = strToCharArray(password);
	user.append_attribute("AccessLevel") = accesLevel;
	doc.save_file(strToCharArray(specFilename));
}



void addUserToDBS(xml_node domobus) {
	string username;
	string password;
	int accesLevel;
	cout << "Please enter the desired username: ";
	cin >> username;
	cout << "Please enter the dwsired password for user " + username + ": ";
	// SetStdinEcho(false);
	cin >> password;
	// SetStdinEcho(true);
	while(true) {
		accesLevel = getIntegerFromInput("Please enter the access level for user " + username + ": ");
		if(accesLevel >= 1 && accesLevel <= 10)
			break;
		else {
			cout << "Invalid access level. Please input a value between 1 and 10, inclusive.\n\n";
			continue;
		}
	}
	// add node with name User
	xml_node ul = domobus.child("UserList");
	xml_node user = ul.append_child();
	user.set_name("User");
	user.append_attribute("ID") = ++userIDCounter;
	user.append_attribute("Name") = strToCharArray(username);
	user.append_attribute("Password") = strToCharArray(password);
	user.append_attribute("AccessLevel") = accesLevel;
	doc.save_file(strToCharArray(specFilename));
}

void manageDomoBusSystem(xml_node domobus) {
	int optionSelected;
	while(true) {
		string display1 =  "---------------------------\n\nDomoBusSystem Manager:\n\n1.[1] Add User\n1.[2] Add Device\n1.[3] Add Activity Scenario\n1.[4] Remove User\n1.[5] Remove Device\n1.[6] Remove Activity Scenario\n\n1.[0] Go back\n\nSelect an option: ";
		optionSelected = getIntegerFromInput(display1);
			switch(optionSelected) {
				case 1:
					addUserToDBS(domobus);
					break;
				case 2:
					cout << "ADDING DEVICE..............";
					break;
				case 0:
					return;
			}
	}
}

int main(int argc, char* argv[])
{

	// xml_document doc;
	char* docToLoad;

	if(argc > 1)
		docToLoad = strToCharArray(argv[1]);
	else
		docToLoad = strToCharArray("dbspec.xml");

	xml_parse_result result = doc.load_file(docToLoad);

	string nerr = "No error";
	if(nerr.compare(result.description())) 
	{
		cout << "ERROR: Error loading document " << docToLoad << ". Exiting." << endl;
		exit(1);
	}

	xml_node domobus = doc.child("DomoBusSystem");
	xml_node evtl = domobus.child("EnumValueTypeList");
	xml_node evt = domobus.child("EnumValueType");
	
	deviceIDCounter = charArrayToInteger(domobus.child("DeviceTypeList").last_child().attribute("ID").value());
	userIDCounter = charArrayToInteger(domobus.child("UserList").last_child().attribute("ID").value());

	cout << endl << "Welcome to DomoBusSystem " << "Project : " << domobus.attribute("Name").value() << " - " << domobus.attribute("Type").value() << " Simulator - Version: " << domobus.attribute("Version").value() << endl << endl;

	int optionSelected; 
	while(true) {
		string display = "---------------------------\n\nMain Menu:\n\n[1] DomoBusSystem Manager.\n[2] DomoBusSystem Simulator\n\n[0] Exit\n\nSelect an option: ";
		optionSelected = getIntegerFromInput(display);


		// ENTERED DOMOBUSSYSTEM MANAGER
		if(optionSelected == 1) {
			manageDomoBusSystem(domobus);
		}


		// ENTERED DOMOBUSSYTEM SIMULATOR
		else if(optionSelected == 2) {
			
		} 


		// EXIT APPLICATION
		else if(optionSelected == 0) {
			exit(0);
		}


		// INVALID OPTION SELECTED
		else {
			cout << "Invalid option selected. Please select an option using one of the numbers betwen []." << endl;
		}
	}
}






//[code_load_file
//     xml_document doc;

//     xml_parse_result result = doc.load_file("tree.xml");

//     cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << endl;
// //]
