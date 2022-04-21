#include "LinkedList.h"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif

using namespace std;

string boolToString(bool input) {
	if (input) {
		return "true";
	}
	else {
		return "false";
	}
}

int main(int argc, char* argv[]) {
	VS_MEM_CHECK

	//open files
	if (argc < 3) {
		cerr << "Please provide name of input and output files";
		return 1;
	}
	ifstream in(argv[1]);
	if (!in.is_open()) {
		cout << "Uh oh there was an inputFile error..." << endl;
		return 2;
	}
	ofstream out(argv[2]);
	if (!out.is_open()) {
		cout << "Uh oh there was an outputFile error..." << endl;
		return 3;
	}
	//instantiate objects
	string command;
	string dataType;
	LinkedList<int> intList;
	LinkedList<string> stringList;

	//take in data type (always first)
	in >> dataType;
	out << dataType << " true" << endl;
	while (in >> command) {
		if (dataType == "INT") {
			//check if data type changes
			if (command == "STRING") {
				dataType = command;
				out << command << " true " << endl;
			}
			//lots of else if statements
			else if (command == "insertHead") {
				bool outputBool = false;
				int value = 0;
				in >> value;
				if (intList.checkDuplicate(value)) {
					outputBool = intList.insertHead(value);
				}
				out << command << " " << value << " " << boolToString(outputBool) << endl;
			}
			else if (command == "insertTail") {
				bool outputBool = false;
				int value = 0;
				in >> value;
				if (intList.checkDuplicate(value)) {
					outputBool = intList.insertTail(value);
				}
				out << command << " " << value <<  " " << boolToString(outputBool) << endl;
			}
			else if (command == "insertAfter") {
				bool outputBool = false;
				int matchNode = 0, node = 0;
				in >> matchNode;
				in >> node;
				if (intList.checkDuplicate(node)) {
					outputBool = intList.insertAfter(matchNode, node);
				}
				out << command << " " << matchNode << " " << node << " " << boolToString(outputBool) << endl;
			}
			else if (command == "printList") {
				/*string outputList = intList.toString();
				if (outputList == "") {
					outputList = "Empty \n";
				}*/
				out << command << " " << intList << endl;
			}
			//extra credit code
			else if (command == "iterateList") {
				LinkedList<int>::Iterator iter = intList.begin();
				string outputList;
				out << command << " ";
				for (; iter != intList.end(); ++iter) {
					out << *iter << " ";
				}
				out << endl;
			}
			else if (command == "at") {
				bool outputBool = false;
				int index = -1;
				string nodeValue;
				try {
					in >> index;
				}
				catch (...) {
					nodeValue = "Invalid Index";
				}
				if (index < 0) {
					outputBool = false;
				}
				else {
					size_t sendIndex = index;
					outputBool = intList.at(sendIndex, nodeValue);
				}
				if (outputBool) {
					out << command << " " << index << " " << nodeValue << boolToString(outputBool) << endl;
				}
				else {
					out << command << " " << index << " " << nodeValue << endl;
				}
			}
			else if (command == "size") {
				out << command << " " << intList.size() << endl;
			}
			else if (command == "remove") {
				int nodeValue = -1;
				in >> nodeValue;
				out << command << " " << nodeValue << " " << boolToString(intList.remove(nodeValue)) << endl;
			}
			else if (command == "clear") {
				out << command << " " << boolToString(intList.clear()) << endl;
			}
		}
		else {
			//repeat all functions but for a string linkedlist
			if (command == "insertHead") {
				bool outputBool = false;
				string value;
				in >> value; 
				if (stringList.checkDuplicate(value)) {
					outputBool = stringList.insertHead(value);
				}
				out << command << " " << value << " " << boolToString(outputBool) << endl; 
			}
			else if (command == "insertTail") {
				bool outputBool = false;
				string value;
				in >> value;
				if (stringList.checkDuplicate(value)) {
					outputBool = stringList.insertTail(value);
				}
				out << command << " " << value << " " << boolToString(outputBool) << endl;
			}
			else if (command == "insertAfter") {
				bool outputBool = false;
				string matchNode, node;
				in >> matchNode;
				in >> node;
				if (stringList.checkDuplicate(node)) {
					outputBool = stringList.insertAfter(matchNode, node);
				}
				out << command << " " << matchNode << " " << node << " " << boolToString(outputBool) << endl;
			}
			else if (command == "printList") {
				/*string outputList = stringList.toString();
				if (outputList == "") {
					outputList = "Empty \n";
				}*/
				out << command << " " << stringList << endl;
			}
			else if (command == "iterateList") {
				LinkedList<string>::Iterator iter = stringList.begin();
				string outputList;
				out << command << " ";
				for (; iter != stringList.end(); ++iter) {
					out << *iter << " ";
				}
				out << endl;
			}
			else if (command == "at") {
				bool outputBool = false;
				int index = -1;
				string nodeValue;
				try {
					in >> index;
				}
				catch (...) {
					nodeValue = "Invalid Index";
				}
				if (index < 0) {
					outputBool = false;
					nodeValue = "Invalid Index";
				}
				else {
					size_t sendIndex = index;
					outputBool = stringList.at(sendIndex, nodeValue);
				}
				if (outputBool) {
					out << command << " " << index << " " << nodeValue << boolToString(outputBool) << endl;
				}
				else {
					out << command << " " << index << " " << nodeValue << endl;
				}
			}
			else if (command == "size") {
				out << command << " " << stringList.size() << endl;
			}
			else if (command == "remove") {
				string nodeValue;
				in >> nodeValue;
				out << command << " " << nodeValue << " " << boolToString(stringList.remove(nodeValue)) << endl;
			}
			else if (command == "clear") {
				out << command << " " << boolToString(stringList.clear()) << endl;
			}
		}
	}
	//free memory
	intList.clear();
	stringList.clear();

	in.close();
	out.close();
	return 0;
}