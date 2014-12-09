#include "pugixml.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
using namespace pugi;


char* strToCharArray (string str) {
	char * cstr = new char [str.length()+1];
  strcpy (cstr, str.c_str());
  return cstr;
}

string getInput() {

}

int getIntegerFromInput(string display) {
	int integer;
	while(true){
		cout << display;
		cin >> integer;
		if(cin.fail()) {
			cin.clear();
			string dummy;
	  	cin >> dummy; // throw away garbage.
			cout << "Invalid input type. Please select an option using one of the numbers betwen []." << endl;
			continue;
			}
		else
			return integer;
	}
}

int main(int argc, char* argv[])
{

	xml_document doc;
	char* docToLoad;

	// cout << "argc: " << argc << endl;

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



	cout << endl << "Welcome to DomoBusSystem " << "Project : " << domobus.attribute("Name").value() << " - " << domobus.attribute("Type").value() << " Simulator - Version: " << domobus.attribute("Version").value() << endl;

	int optionSelected; 
	while(true) {
		string display = "\n[1] DomoBusSystem Manager\n[2] DomoBusSystem Simulator\n\n[0] Exit\nSelect an option: ";
		optionSelected = getIntegerFromInput(display);

		if(optionSelected == 1) {
			// cout << "ENTREI !!!!\n";
			string display1 ;
		} 

		else if(optionSelected == 2) {
			
		} 

		else if(optionSelected == 0) {
			exit(0);
		}

		else {
			cout << "Wrong option selected. Please select an option using one of the numbers betwen []." << endl;
		}

	}


}






//[code_load_file
//     xml_document doc;

//     xml_parse_result result = doc.load_file("tree.xml");

//     cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << endl;
// //]
