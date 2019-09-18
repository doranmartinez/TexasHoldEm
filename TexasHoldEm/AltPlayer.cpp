#include "Player.h"

Player::Player () {
	cout << "Enter Player ID: ";
	cin >> playerID;
}

void Player::setHand(Card c) {
	if (!hand[0].thisNum) hand[0] = c;
	else if (!hand[1].thisNum) hand[1] = c;
}

void Player::check() {
	decision = CHECK;
}



PlayerChoice Player::whatDo() {
	return decision;
}