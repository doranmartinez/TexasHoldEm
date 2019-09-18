#pragma once
#include <iostream>
#include <string>
using namespace std;
#include "Card.h"

enum PlayerChoice { CHECK, RAISE, FOLD };

class Player
{
private:
	int handRank; // value of hand
	Card hand[2]; // two cards in players hand
	bool winner; // true if winner of round, possible split winner
	int wallet; // total $ in wallet
	int bet; // amount player is betting in a given round, taken from wallet
	PlayerChoice decision;
	string playerID;

	void check();
	int bet(int);
	Card fold();

public:
	Player();
	void setHand(Card);
	PlayerChoice whatDo(); // returns enum check, raise, fold

	int setHandRank(Card *); // takes commCards[] from game.h, and player.hand[], and calculates player.handRank
};