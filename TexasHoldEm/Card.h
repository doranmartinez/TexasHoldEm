#pragma once
#include <string>
using namespace std;

	enum Suit
	{NONE, DIAMOND, CLUB, HEART, SPADE};
	enum Number
	{ZERO, TWO, THREE, FOUR, FIVE, SIX,
		SEVEN, EIGHT, NINE, TEN, JACK,
		QUEEN, KING, ACE};

struct Card {
	Suit thisSuit;
	Number thisNum;

	Card() {
		thisSuit = NONE;
		thisNum = ZERO;
	}

	Card(Suit s, Number n) {
		thisSuit = s;
		thisNum = n;
	}

	string showSuit() {
		switch (thisSuit) {
		case DIAMOND: return "Diamond";
			break;
		case CLUB: return "Club";
			break;
		case HEART: return "Heart";
			break;
		case SPADE: return "Spade";
			break;
		default: return "None";
		}
	}

	string showNum() {
		char num = '0';
		string strSuit = " ";
		if (thisNum && thisNum < TEN) {
			num += thisNum + 1;
			return strSuit + num;
		}
		switch (thisNum) {
		case TEN: return "10";
			break;
		case JACK: return " J";
			break;
		case QUEEN: return " Q";
			break;
		case KING: return " K";
			break;
		case ACE: return " A";
			break;
		default: return "00";
		}
	}
};
