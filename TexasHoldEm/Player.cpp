#include "Player.h"



Player::Player()
{
	int handRank = 0; // value of hand
	Card hand[2] = { {hand[0].thisSuit = NONE, hand[0].thisNum = ZERO }, {hand[1].thisSuit = NONE, hand[1].thisNum = ZERO } }; // two cards in players hand
	bool winner = false; // true if winner of round, possible split winner
	int wallet = 1000; // total $ in wallet
	int bet = 0; // amount player is betting in a given round, taken from wallet
	int playerNumber = 0;
	bool fold = false;
}


Player::~Player()
{
}

void Player::setPlayerNumber(int playerNum)
{
	playerNumber = playerNum;
}

void Player::setFold(bool fold)
{
	this->fold = fold;
}

void Player::addWallet(int funds)
{
	wallet += funds;
}

void Player::subWallet(int withdraw)
{
	wallet -= withdraw;
}

void Player::setHand(Card card1, Card card2)
{
	if (!hand[0].thisNum) hand[0] = card1;
	else if (!hand[1].thisNum) hand[1] = card2;
}

bool Player::getFold()
{
	return fold;
}

int Player::getWallet()
{
	return wallet;
}
