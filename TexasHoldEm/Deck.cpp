#include "Deck.h"

void Deck::getDeck() {
	Suit s = DIAMOND;
	while (s <= SPADE) {
		Number n = TWO;
		while (n <= ACE) {
			Card newCard(s, n);
			Pile.add(newCard);
			n = static_cast<Number> (n + 1);
		}
		s = static_cast<Suit> (s + 1);
	}
}

Card Deck::Deal() {
	return Pile.pop();
}

void Deck::Reset(Deck & other) {
	while (!Pile.isEmpty())
		other.Pile.add(this->Deal());
}

void Deck::take(Card c) {
	Pile.add(c);
}

void Deck::ShuffleFrom(Deck & other) {
	Deck waiting;
	//take the top card of other deck
	Card check = other.Deal();
	//its number will be how many we skip
	int skip = check.thisNum + 1;
	//put that card in this deck
	this->take(check);
	while (!other.Pile.isEmpty()) {
		//move # of cards to waiting deck
		for (int i = 0; i < skip && !other.Pile.isEmpty(); i++) {
			waiting.take(other.Deal());
		}
		//put current top of other deck into this
		if (!other.Pile.isEmpty())
			this->take(other.Deal());
	}
	if (!this->Pile.isFull()) this->ShuffleFrom(waiting);
}

bool Deck::cardsLeft() {
	return !Pile.isEmpty();
}