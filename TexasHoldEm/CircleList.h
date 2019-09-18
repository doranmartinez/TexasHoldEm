#pragma once
#include "Node_1-link.h"

template <class T>
class CircleList {
private:
	Link<T> * end;
	int totNodes;
	Link<T> * currPos;
	bool findNode(T);
	
public:
	CircleList();
	~CircleList();
	void putNode(T);
	void deleteNode(T);
	int getListSize(); // returns totNodes
	void resetList();
	void printNodes();

	Link<T> * getCurrPos();
	Link<T> * getNextNode();
	Link<T> * getEnd();
};