#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "LinkedListInterface.h"

#include <iostream>
#include <string>
#include <sstream>

#define MAX 10000

using namespace std;

template <typename Teml>
class LinkedList : public LinkedListInterface<Teml> {
private:
	//NODE nested struct ---------------------------------
	struct Node {
		Teml nodeValue;
		Node* ptrToNext;
		Node(const Teml& listNode) :
			nodeValue(listNode),
			ptrToNext(NULL) 
		{}
		Node(const Teml& listNode, Node* nodePointer) : 
			nodeValue(listNode), 
			ptrToNext(nodePointer) 
		{}
		virtual string toString() const {
			stringstream out;
			out << this->nodeValue << " ";
			return out.str();
		}
		friend ostream& operator<< (ostream& os, Node& parArray) {
			os << parArray.toString();
			return os;
		}
	};
	Node* headNode;
	//----------------------------------------------------

public:
	//ITERATOR nested class ========================================
	//very similar to last lab but using LinkedList and different operator* overload
	class Iterator {
	private:
		size_t index;
		LinkedList<Teml>* arrayPtr;
	public:
		Iterator(LinkedList<Teml>* alpha, size_t south) :
			arrayPtr(alpha), index(south) {
		}
		Teml operator[](size_t ind) const {
			arrayPtr->myArray[ind];
		}
		//finds the link corresponding to the index and returns its node value
		Teml operator*() const {
			Node* tempPtr = arrayPtr->headNode;
			unsigned int count = 0;
			while (tempPtr != NULL && count < index) {
				tempPtr = tempPtr->ptrToNext;
				count++;
			}
			return tempPtr->nodeValue;
		}
		Iterator& operator++() {
			++index;
			return *this;
		}
		bool operator!=(const Iterator& check) const {
			if (index == check.index) {
				return false;
			}
			return true;
		}
	};
	LinkedList::Iterator begin() {
		return LinkedList<Teml>::Iterator(this, 0);
	}
	LinkedList::Iterator end() {
		return LinkedList<Teml>::Iterator(this, this->size());
	}
	//==============================================================



	LinkedList() { 
		this->headNode = NULL; 
	}
	virtual ~LinkedList() { 
		clear(); 
	}
	//check for duplicate entries
	virtual bool checkDuplicate(Teml value);

	/** Insert value at beginning of list (no duplcates) */
	virtual bool insertHead(Teml value) {
		if (headNode == NULL) {
			headNode = new Node(value);
		}
		else {
			Node* tempPtr = headNode;
			headNode = new Node(value, tempPtr);
		}
		return true;
	}
	/** Insert value at end of list (no duplcates) */
	virtual bool insertTail(Teml value);

	//Insert sentValue after the matchThisValue parameter is found in the list
	virtual bool insertAfter(Teml matchThisValue, Teml sentValue);

	//Remove node with value of sentValue
	virtual bool remove(Teml sentValue);

	//move through the array deleting each node
	virtual bool clear() {
		Node* tempPtr = headNode;
		Node* prevTemp = tempPtr;
		while (tempPtr != NULL) {
			prevTemp = tempPtr;
			tempPtr = tempPtr->ptrToNext;
			delete prevTemp;
		}
		delete tempPtr;
		headNode = NULL;
		return true;
	}
	//Return node value of index searchIndex
	virtual bool at(size_t searchIndex, std::string &value);

	//Count the number of nodes
	virtual size_t size() const {
		Node* tempPtr = headNode;
		size_t count = 0;
		while (tempPtr != NULL) {
			tempPtr = tempPtr->ptrToNext;
			count++;
		}
		delete tempPtr;
		return count;
	}
	//Return parsed string of all node values
	virtual string toString() const {
		stringstream out;
		Node* tempPtr = headNode;
		while (tempPtr != NULL) {
			out << tempPtr->toString();
			tempPtr = tempPtr->ptrToNext;
		}
		if (out.str() == "") {
			return "Empty";
		}
		return out.str();
	}
	friend ostream& operator<< (ostream& os, LinkedList<Teml>& parArray) {
		os << parArray.toString();
		return os;
	}
};
#endif



template <typename Teml>
bool LinkedList<Teml>::checkDuplicate(Teml value) {
	Node* tempPtr = headNode;
	while (tempPtr != NULL) {
		if (tempPtr->nodeValue == value) {
			return false;
		}
		tempPtr = tempPtr->ptrToNext;
	}
	if (headNode == NULL) {
		return true;
	}
	return true;
}

template <typename Teml>
bool LinkedList<Teml>::insertTail(Teml value) {
	if (headNode == NULL) {
		insertHead(value);
		return true;
	}
	else {
		Node* newNode = new Node(value);
		Node* tempPtr = headNode;
		while (tempPtr->ptrToNext != NULL) {
			tempPtr = tempPtr->ptrToNext;
		}
		tempPtr->ptrToNext = newNode;
		newNode->ptrToNext = NULL;
		return true;
	}
	return false;
}

template <typename Teml>
bool LinkedList<Teml>::insertAfter(Teml matchThisValue, Teml sentValue) {
	if (headNode == NULL) {
		insertHead(sentValue);
		return true;
	}
	else {
		Node* newNode = new Node(sentValue);
		Node* tempPtr = headNode;
		bool isFound = false;
		if (headNode->nodeValue == sentValue) {
			isFound = true;
		}
		while (tempPtr != NULL && !isFound) {
			if (tempPtr->nodeValue == matchThisValue) {
				isFound = true;
				break;
			}
			tempPtr = tempPtr->ptrToNext;
		}
		if (isFound) {
			newNode->ptrToNext = tempPtr->ptrToNext;
			tempPtr->ptrToNext = newNode;
			return true;
		}
		delete newNode;
	}
	return false;
}

template <typename Teml>
bool LinkedList<Teml>::remove(Teml sentValue) {
	Node* tempPtr = headNode;
	Node* prevTemp = tempPtr;
	bool isFound = false;
	if (tempPtr == NULL) {
		return false;
	}
	else if (sentValue == headNode->nodeValue) {
		headNode = tempPtr->ptrToNext;
		isFound = true;
	}
	else {
		while (!isFound && tempPtr->ptrToNext != NULL) {
			prevTemp = tempPtr;
			tempPtr = tempPtr->ptrToNext;
			if (sentValue == (tempPtr->nodeValue)) {
				isFound = true;
			}
		}
	}
	if (isFound) {
		prevTemp->ptrToNext = tempPtr->ptrToNext;
		delete tempPtr;
		return true;
	}
	else {
		return false;
	}
}

template <typename Teml>
bool LinkedList<Teml>::at(size_t searchIndex, std::string &value) {
	Node* tempPtr = headNode;
	if (searchIndex > MAX) {
		tempPtr = NULL;
		searchIndex = 0;
	}
	if (searchIndex != 0) {
		for (size_t i = 0; i < searchIndex; i++) {
			if (tempPtr == NULL) {
				value = "Invalid Index";
				return false;
				break;
			}
			tempPtr = tempPtr->ptrToNext;
		}
	}
	if (tempPtr == NULL) {
		value = "Invalid Index";
		return false;
	}
	value = tempPtr->toString();
	return true;
}