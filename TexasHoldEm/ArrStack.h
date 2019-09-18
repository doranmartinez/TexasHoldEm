#pragma once

template <class T>
class ArrStack {
private:
	T * items;
	int capacity;
	int top;
public:
	ArrStack(int);
	~ArrStack();
	bool isEmpty();
	bool isFull();
	T pop();
	void add(T);
};