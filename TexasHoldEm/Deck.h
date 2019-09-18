#pragma once
#include "ArrStack.cpp"
#include "Card.h"

class Deck {
public:
	void getDeck();
	Card Deal();
	void Reset(Deck &);
	void take(Card);
	void ShuffleFrom(Deck &);
	bool cardsLeft();

	const int MAX = 52;
private:
	ArrStack<Card> Pile =
		ArrStack<Card>(MAX);
};