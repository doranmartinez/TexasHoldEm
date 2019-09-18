#include <iostream>
#include "CircleList.h"
using namespace std;

template <class T>
CircleList<T>::CircleList() {
	end = nullptr;
	totNodes = 0;
	currPos = nullptr;
}

template <class T>
CircleList<T>::~CircleList() {
	while (totNodes) {
		Link<T> * trash = end;
		if (end) end = end->next;
		delete trash;
		trash = nullptr;
		totNodes--;
	}
}

template <class T>
Link<T> * CircleList<T>::getNextNode() {
	if (!currPos) currPos = end;
	else currPos = currPos->next;
	return currPos;
}

template <class T>
void CircleList<T>::putNode(T newData) {
	Link<T> * newNode = new Link<T>;
	if (!end) {
		end = newNode;
		end->next = newNode;
	}
	newNode->data = newData;
	newNode->next = end->next;
	end->next = newNode;
	end = newNode;
	totNodes++;
}

template <class T>
void CircleList<T>::printNodes() {
	Link<T> * j = end;
	do {
		cout << j->next->data << ' ';
		j = j->next;
	} while (j != end);
	cout << endl;
}

template<class T>
int CircleList<T>::getListSize()
{
	return totNodes;
}

template<class T>
Link<T> * CircleList<T>::getCurrPos()
{
	return currPos;
}

template<class T>
void CircleList<T>::resetList()
{
	currPos = NULL;
}

template<class T>
Link<T>* CircleList<T>::getEnd()
{
	return end;
}

template<class T>
bool CircleList<T>::findNode(T key) {
	if (currPos->next->data == key) return true;
	else if (currPos->next == end) {
		return false;
	}
	else {
		currPos = currPos->next;
		return this->findNode(key);
	}
}

template <class T>
void CircleList<T>::deleteNode(T trashData) {
	currPos = end;
	if (this->findNode(trashData)) {
		Link<T> * trash = currPos->next;
		currPos->next = currPos->next->next;
		if (currPos->next == end) end = currPos;
		delete trash;
		totNodes--;
	}
}