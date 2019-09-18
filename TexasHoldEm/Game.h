#pragma once
#include "CircleList.h"	//can be ported to look like they are part
#include "Deck.h"
#include "Player.h"
#include <iostream>
using namespace std;

class Game {
public:

	// setters
	void setPot(int);
	void setAnte();

	// getters
	int getPot();

	// util
	void Play();
	int PayIn(Player, int);	// input circular list of players & payIn amount. return to Pot
	int PayOut(Player *);	// mutator for Pot
	int splitPot(Player *, Player *); // input two players who split the pot

	// constructor & destructor
	Game();
	~Game();

private:
	enum RoundPhase { PRE_FLOP, FLOP, TURN, RIVER, SHOW };	// Play() uses RoundPhase for readability 
	enum HandRank { HIGH_CARD, PAIR, TWO_PAIR, THREE_OF_KIND, STRAIGHT, FLUSH, FULL_HOUSE, FOUR_OF_KIND, STRAIGHT_FLUSH, ROYAL_FLUSH };
	int const Rounds = 10;

	Deck PlayCards;				// uses deck.h

	Card CommCards[5];			// Community Cards A.K.A. 3-5 cards on table
	int currCommCardLength;
	void displayCommCards();

	CircleList<Player> * Table;
	void Add2Table(int);		// adds Player to Table
	void  Kick(Player);
	void getBets();
	Player * DealerButton;		//Pointer type may have to be tweaked
	RoundPhase phase;
	int numPlayers;
	int Pot;
	int Ante;
	int totalBet; // Player.bet must equal totalBet, fold, or raise
		// if Player raises, totalBet = raise - Player.bet
};