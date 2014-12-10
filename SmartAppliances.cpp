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
string emptyID = "#";
string emptyStr = "";
xml_document doc;
xml_node domobus;

char* intToCharArray (int n) {
	stringstream strstream;
	strstream << (n);
	string str = strstream.str();
	char * cstr = new char[str.length()+1];
	strcpy(cstr, str.c_str());
	return cstr;
}

char* strToCharArray (string str) {
	char * cstr = new char [str.length()+1];
  strcpy (cstr, str.c_str());
  return cstr;
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
			cout << "\nERROR: Entered input is not an integer.\n\n";
			continue;
			}

		else
			cout << endl;
			return integer;
	}
}

bool displayChildNodesForSelection(xml_node parent, string options, int &lastID){
	// xml_node svtl = domobus.child("ScalarValueTypeList");
	bool hasChildren = false;
	if((emptyID.compare(parent.first_child().attribute("ID").value())) == 0) {
		// cout << "ERROR: No child elements defined.\n";
		// No child nodes defined
		return false;
	}
	for(xml_node child = parent.first_child(); child; child = child.next_sibling()) {
		hasChildren = true;
		if((emptyID.compare(child.attribute("ID").value())) != 0 && (emptyStr.compare(child.attribute("ID").value())) != 0) {
			
			lastID = charArrayToInteger(child.attribute("ID").value());
			cout << options << "[" << child.attribute("ID").value() << "] " << child.name() <<":";

			for(xml_attribute attr = child.first_attribute(); attr; attr = attr.next_attribute()){
				cout << " " << attr.name() << "=" << "\"" << attr.value() << "\"";
			}
			cout << "\n";
		}

	}
	return hasChildren;
}

bool chooseScalar(xml_node property){
	int lastID = -1;
	int optionSelected;
	while(true) {
		if(displayChildNodesForSelection(domobus.child("ScalarValueTypeList"), "1.1.1.1.", lastID)) {
			cout << "\n\n\n" << lastID << "\n\n\n";
			optionSelected = getIntegerFromInput("Select an option: ");
			xml_node chosenScalar = domobus.child("ScalarValueTypeList").find_child_by_attribute("ScalarValueType","ID",intToCharArray(optionSelected));
			return true;
		} 
		else {
			cout << "ERROR: No scalar types defined.";
			return false;
		}
	}

}

bool setValueType(xml_node property){
	// string valueType;
	int optionSelected;
	while(true) {
		optionSelected = getIntegerFromInput("\n1.1.1.[1] SCALAR\n1.1.1.[2] ENUM\n1.1.1.[3] ARRAY\n1.1.1.[4] USERID\n\n1.1.1.[0] Cancel and go back\n\nSelect an option: ");
		// cout << "Enter a value type [SCALAR, ENUM, ARRAY or USERID]: ";
		// cin >> valueType;
		if(optionSelected == 1){
			cout << "\n\nSCALAR\n\n";
			if(chooseScalar(property)){
				return true;
			}else
				break;
		}
		else if(optionSelected == 2){
			cout << "\n\nENUM\n\n";
			return true;
			// break;
		}
		else if(optionSelected == 3){
			cout << "\n\nARRAY\n\n";
			return true;
			// break;
		}
		else if(optionSelected == 4){
			cout << "\n\nUSERID\n\n";
			return true;
			// break;
		}
		else if(optionSelected == 0){
			cout << "\n\nEXIT\n\n";
			return false;
			// break;
		}
		else {
			cout << "\nERROR: Please select a valid option (one of the numbers between [] )\n\n";
			continue;
		}
	}
}

void addDeviceToDBS(xml_node domobus) {

	xml_node dtl = domobus.child("DeviceTypeList");
	xml_node device = dtl.append_child();
	device.set_name("DeviceType");
	device.append_attribute("ID") = ++deviceIDCounter;

	string deviceName;
	string description;
	string dummy;
	getline(cin, dummy);
	cout << "Please enter the device name: ";
	getline(cin, deviceName);
	device.append_attribute("Name") = strToCharArray(deviceName);
	
	cout << "Please enter a description for the device " + deviceName + ": ";
	getline(cin, description);
	device.append_attribute("Description") = strToCharArray(description);
	
	int propCounter = -1;
	int optionSelected = 0;

	xml_node ptl = device.append_child();
	ptl.set_name("PropertyTypeList");
	// Add one or more properties to device
	while(true) {
		optionSelected = getIntegerFromInput("\n1.1.[1] Add Property to Device\n1.1.[2] Finish\n\n1.1.[0] Cancel and go back\n\nSelect an option: ");
		if(optionSelected == 1) {
			xml_node property = ptl.append_child();
			property.set_name("PropertyType");
			property.append_attribute("ID") = ++propCounter;
			setValueType(property);
			continue;
		}
		else if(optionSelected == 2) {
			if(propCounter < 0) {
				cout << "ERROR: The device must have AT LEAST ONE property.\n";
				continue;
			}
			else
				break;
		}
		else if(optionSelected == 0) {
			dtl.remove_child(device);
			break;
		}
		else {
			cout << "ERROR: Please select a valid option (one of the numbers between [] ).\n";
		}
	}
	
	doc.save_file(strToCharArray(specFilename));
}



void addUserToDBS(xml_node domobus) {
	string username;
	string password;
	int accessLevel;
	cout << "Please enter the desired username: ";
	cin >> username;
	cout << "Please enter the desired password for user " + username + ": ";
	// SetStdinEcho(false);
	cin >> password;
	// SetStdinEcho(true);
	while(true) {
		accessLevel = getIntegerFromInput("Please enter the access level for user " + username + " [1-10]: ");
		if(accessLevel >= 1 && accessLevel <= 10)
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
	user.append_attribute("AccessLevel") = accessLevel;
	xml_node uidvtl = domobus.child("UserIDValueTypeList");
	user = uidvtl.append_child();
	user.set_name("UserIDValueType");
	user.append_attribute("ID") = userIDCounter;
	user.append_attribute("RefUser") = userIDCounter;
	user.append_attribute("UserName") = strToCharArray(username);
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
					addDeviceToDBS(domobus);
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
		docToLoad = strToCharArray(specFilename);

	xml_parse_result result = doc.load_file(docToLoad, pugi::parse_full);

	string nerr = "No error";
	if(nerr.compare(result.description())) 
	{
		cout << "ERROR: Error loading document " << docToLoad << ". Exiting." << endl;
		exit(1);
	}

	// xml_node 
	domobus = doc.child("DomoBusSystem");
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

