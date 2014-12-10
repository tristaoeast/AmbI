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

string charArrayToString(const char* cstr) {
	string str(cstr);
	return str;
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

			cout << "---------------------------\n\n" << options << "[" << (lastID + 1) << "] " << child.name() <<":";

			for(xml_attribute attr = child.first_attribute(); attr; attr = attr.next_attribute()){
				cout << " " << attr.name() << "=" << "\"" << attr.value() << "\"";
			}
			cout << "\n";
		}

	}
	return hasChildren;
}

void displayAllChildNodes(xml_node parent) {

	if((emptyID.compare(parent.first_child().attribute("ID").value())) == 0) {
		cout << "No " << parent.first_child().name() << "elements defined.\n";
	}
	for(xml_node child = parent.first_child(); child; child = child.next_sibling()) {
		if((emptyID.compare(child.attribute("ID").value())) != 0 && (emptyStr.compare(child.attribute("ID").value())) != 0) {

			cout << child.name() <<":";

			for(xml_attribute attr = child.first_attribute(); attr; attr = attr.next_attribute()){
				cout << " " << attr.name() << "=" << "\"" << attr.value() << "\"";
			}
			cout << "\n";
		}
	}
}

bool chooseScalar(xml_node property, string &name, int &ID){
	int lastID = -1;
	int optionSelected;
	while(true) {
		if(displayChildNodesForSelection(domobus.child("ScalarValueTypeList"), "1.1.1.1.", lastID)) {
			// cout << "\n\n\n" << lastID << "\n\n\n";
			cout << "\n1.1.1.1.[0] Cancel and go back\n\n";
			optionSelected = getIntegerFromInput("Select an option: ");
			if(optionSelected == 0) 
				return false;
			else if(optionSelected >= 1 && optionSelected <= (lastID +1)) {
				xml_node chosenScalar = domobus.child("ScalarValueTypeList").find_child_by_attribute("ScalarValueType","ID",intToCharArray(optionSelected-1));
				name = charArrayToString(chosenScalar.attribute("Name").value());
				ID = charArrayToInteger(chosenScalar.attribute("ID").value());
				return true;
			}
			else {
				cout << "ERROR: Please select a valid option (one of the numbers between [] )\n\n";
			}
		}
		else {
			cout << "ERROR: No SCALAR types defined.\n\n";
			return false;
		}
	}
}

bool chooseEnum(xml_node property, string &name, int &ID){
	int lastID = -1;
	int optionSelected;
	while(true) {
		if(displayChildNodesForSelection(domobus.child("EnumValueTypeList"), "1.1.1.2.", lastID)) {
			// cout << "\n\n\n" << lastID << "\n\n\n";
			cout << "\n1.1.1.2.[0] Cancel and go back\n\n";
			optionSelected = getIntegerFromInput("Select an option: ");
			if(optionSelected == 0) 
				return false;
			else if(optionSelected >= 1 && optionSelected <= (lastID +1)) {
				xml_node chosenEnum = domobus.child("EnumValueTypeList").find_child_by_attribute("EnumValueType","ID",intToCharArray(optionSelected-1));
				name = charArrayToString(chosenEnum.attribute("Name").value());
				ID = charArrayToInteger(chosenEnum.attribute("ID").value());
				return true;
			}
			else {
				cout << "ERROR: Please select a valid option (one of the numbers between [] )\n\n";
			}
		}
		else {
			cout << "ERROR: No ENUM types defined.\n\n";
			return false;
		}
	}
}

bool chooseArray(xml_node property, string &name, int &ID){
	int lastID = -1;
	int optionSelected;
	while(true) {
		if(displayChildNodesForSelection(domobus.child("ArrayValueTypeList"), "1.1.1.3.", lastID)) {
			// cout << "\n\n\n" << lastID << "\n\n\n";
			cout << "\n1.1.1.3.[0] Cancel and go back\n\n";
			optionSelected = getIntegerFromInput("Select an option: ");
			if(optionSelected == 0) 
				return false;
			else if(optionSelected >= 1 && optionSelected <= (lastID +1)) {
				xml_node chosenArray = domobus.child("ArrayValueTypeList").find_child_by_attribute("ArrayValueType","ID",intToCharArray(optionSelected-1));
				name = charArrayToString(chosenArray.attribute("Name").value());
				ID = charArrayToInteger(chosenArray.attribute("ID").value());
				return true;
			}
			else {
				cout << "ERROR: Please select a valid option (one of the numbers between [] )\n\n";
			}
		}
		else {
			cout << "ERROR: No ARRAY types defined.\n\n";
			return false;
		}
	}
}


bool chooseUserID(xml_node property, string &name, int &ID){
	int lastID = -1;
	int optionSelected;
	while(true) {
		if(displayChildNodesForSelection(domobus.child("UserIDValueTypeList"), "1.1.1.4.", lastID)) {
			// cout << "\n\n\n" << lastID << "\n\n\n";
			cout << "\n1.1.1.4.[0] Cancel and go back\n\n";
			optionSelected = getIntegerFromInput("Select an option: ");
			if(optionSelected == 0) 
				return false;
			else if(optionSelected >= 1 && optionSelected <= (lastID +1)) {
				xml_node chosenUserID = domobus.child("UserIDValueTypeList").find_child_by_attribute("UserIDValueType","ID",intToCharArray(optionSelected-1));
				name = charArrayToString(chosenUserID.attribute("UserName").value());
				ID = charArrayToInteger(chosenUserID.attribute("ID").value());
				return true;
			}
			else {
				cout << "ERROR: Please select a valid option (one of the numbers between [] )\n\n";
			}
		}
		else {
			cout << "ERROR: No USERID types defined.\n\n";
			return false;
		}
	}
}

bool selectValueType(xml_node property, string &propertyName, int &propertyID, string &propertyValueType) {
	// string valueType;
	int optionSelected;
	int typeID;
	string typeName, valueType;

	while(true) {
		optionSelected = getIntegerFromInput("---------------------------\n\n1.1.1.[1] SCALAR\n1.1.1.[2] ENUM\n1.1.1.[3] ARRAY\n1.1.1.[4] USERID\n\n1.1.1.[0] Cancel and go back\n\nSelect an option: ");
		// cout << "Enter a value type [SCALAR, ENUM, ARRAY or USERID]: ";
		// cin >> valueType;
		if(optionSelected == 1){
			if(chooseScalar(property, typeName, typeID)){
				propertyName = typeName;
				propertyID = typeID;
				propertyValueType="SCALAR";
				return true;
			}else
				continue;
		}
		else if(optionSelected == 2){
			if(chooseEnum(property, typeName, typeID)){
				propertyName = typeName;
				propertyID = typeID;
				propertyValueType="ENUM";
				return true;
			}else
				continue;
		}
		else if(optionSelected == 3){
			if(chooseArray(property, typeName, typeID)){
				propertyName = typeName;
				propertyID = typeID;
				propertyValueType="ARRAY";
				return true;
			}else
				continue;
		}
		else if(optionSelected == 4){
			cout << "\n\nUSERID\n\n";
			if(chooseUserID(property, typeName, typeID)){
				propertyName = typeName;
				propertyID = typeID;
				propertyValueType="SCALAR";
				return true;
			}else
				continue;
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
	// Cleaning cin;
	string dummy;
	getline(cin, dummy);

	cout << "Please enter the device name: ";
	getline(cin, deviceName);
	device.append_attribute("Name") = strToCharArray(deviceName);
	device.append_attribute("RefDeviceClass") = strToCharArray("#");
	
	cout << "Please enter a description for the device " + deviceName + ": ";
	getline(cin, description);
	device.append_attribute("Description") = strToCharArray(description);
	
	int propCounter = -1;
	int optionSelected = 0;

	xml_node ptl = device.append_child();
	ptl.set_name("PropertyTypeList");
	// Add one or more properties to device
	while(true) {
		optionSelected = getIntegerFromInput("---------------------------\n\n1.1.[1] Add Property to Device\n1.1.[2] Finish\n\n1.1.[0] Cancel and go back\n\nSelect an option: ");
		if(optionSelected == 1) {
			xml_node property = ptl.append_child();
			property.set_name("PropertyType");
			property.append_attribute("ID") = ++propCounter;
			string propertyName, propertyValueType;
			int propertyID;
			if(selectValueType(property, propertyName, propertyID, propertyValueType)) {
				property.append_attribute("Name") = strToCharArray(propertyName);
				string accesMode;
				cout << "Please enter desired property's access mode [RO, WO or RW]: ";
				cin >> accesMode;
				property.append_attribute("AccessMode") = strToCharArray(accesMode);
				property.append_attribute("ValueType") = strToCharArray(propertyValueType);
				property.append_attribute("RefValueType") = intToCharArray(propertyID);
			} else {
				ptl.remove_child(property);
				propCounter--;
				continue;
			}

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
	xml_node fl = domobus.child("House").child("FloorList");
	while(true) {
		string display1 =  "---------------------------\n\nDomoBusSystem Manager:\n\n1.[1] Add User\n1.[2] Add DeviceType\n1.[3] Add Floor\n1.[4] Add Division\n1.[5] List Users\n1.[6] List DeviceTypes\n1.[7] List Floors\n1.[8] List Divisions\n\n1.[0] Go back\n\nSelect an option: ";
		optionSelected = getIntegerFromInput(display1);
			switch(optionSelected) {
				case 1:
					addUserToDBS(domobus);
					break;
				case 2:
					addDeviceToDBS(domobus);
					break;
				case 5:
					displayAllChildNodes(domobus.child("UserList"));
					break;
				case 6:
					displayAllChildNodes(domobus.child("DeviceTypeList"));
					break;
				case 7:
					displayAllChildNodes(domobus.child("House").child("FloorList"));
					break;
				case 8:
					for(xml_node f = fl.first_child(); f; f = f.next_sibling())
						displayAllChildNodes(f.child("DivisionList"));
					break;
				case 0:
					return;
				default:
					cout << "Functionality under construction. Please choose another option.\n";
					continue;
			}
	}
}

int main(int argc, char* argv[])
{

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
	
	domobus = doc.child("DomoBusSystem");
	xml_node evtl = domobus.child("EnumValueTypeList");
	xml_node evt = domobus.child("EnumValueType");
	
	deviceIDCounter = charArrayToInteger(domobus.child("DeviceTypeList").last_child().attribute("ID").value());
	userIDCounter = charArrayToInteger(domobus.child("UserList").last_child().attribute("ID").value());

	// int id;
	// displayChildNodesForSelection(domobus.child("ScalarValueTypeList"), "0.", id);

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

