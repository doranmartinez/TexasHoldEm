#include "Game.h"

void Game::setPot(int fundsIn)
{
	Pot += fundsIn;
}

void Game::setAnte()
{
	Ante = Ante + 5;
}

int Game::getPot()
{
	return Pot;
}

void Game::Play()
{
	// Initialize game, introduce settings
	cout << "===============================" << endl;
	cout << "|| Welcome to Texas Hold 'Em!||" << endl;
	cout << "===============================" << endl;
	cout << endl << "Game Length: 10 rounds" << endl;

	cout << "Enter number of players [1-6]: ";
	cin >> numPlayers;

	for (int i = 0; i < numPlayers; i++) {
		Add2Table(i+1); // adds a player to Table for each iteration
	}

	// Main Game Loop
	for (int currRound = 1; currRound < Rounds; currRound++) {

		phase = PRE_FLOP;

		switch (phase) {

		case PRE_FLOP:
			// collect ante
			for (int i = 0; i < Table->getListSize(); i++) {

				// Logic Error?
				// if player kicked, does it skip the next players opportunity to ante?
				try {
					setPot(PayIn(Table->getNextNode()->data, Ante));
				}
				catch (InsufficientFunds) {
					Kick(Table->getCurrPos()->data);
				}
			}
			Table->resetList();

			// deal hands - separate from collect ante loop b/c player may not be able to ante
			for (int i = 0; i < Table->getListSize(); i++) {
				Table->getNextNode()->data.setHand(PlayCards.Deal(), PlayCards.Deal());
			}
			Table->resetList();

			getBets();  // Players should have opportunity to check cards before bet	<---------------- DO THIS
			phase = FLOP;
			
		case FLOP:
			// play 3 card to table
			CommCards[0] = PlayCards.Deal();
			CommCards[1] = PlayCards.Deal();
			CommCards[2] = PlayCards.Deal();
			currCommCardLength = 3;

			// bet round
			getBets();

		case TURN:
			// play 1 card to table
			CommCards[3] = PlayCards.Deal();
			currCommCardLength++;

			// bet round
			getBets();

		case RIVER:
			// play 1 card to table
			CommCards[4] = PlayCards.Deal();
			currCommCardLength++;

			// bet round
			getBets();

		case SHOW:
			// reveal winner
			// distribute winnings
			
		default:
			break;
		} // switch

		setAnte(); // increases Ante by 5 credits

	} // for

} // Play()

int Game::PayIn(Player currPlayer, int betIn)
// PayIn takes player and amount the player must contribute to the pot
// returns amount to be placed into pot
{
	if (betIn > currPlayer.getWallet())
		throw InsufficientFunds();
	else {
		currPlayer.subWallet(betIn);
		return betIn;
	}
}

Game::Game()
{
	phase = PRE_FLOP;
	numPlayers = 0;
	Ante = 5;
	Pot = 0;
	totalBet = 0;
	currCommCardLength = 0;
}

Game::~Game()
{
	while (Table->getListSize() != 0) {
		Table->deleteNode(Table->getNextNode()->data);
		Table->setListSize(-1);
	}
}

void Game::displayCommCards()
{
	if (currCommCardLength == 3) {
		cout << "Community Cards" << endl;
		cout << CommCards[0].showNum << " " << CommCards[0].showSuit << endl;
		cout << CommCards[1].showNum << " " << CommCards[1].showSuit << endl;
		cout << CommCards[2].showNum << " " << CommCards[2].showSuit << endl;

		cout << "Your Cards" << endl;
		Table->getCurrPos()->data.displayHand();
	}
	else if (currCommCardLength == 4) {
		cout << "Community Cards" << endl;
		cout << CommCards[0].showNum << " " << CommCards[0].showSuit << endl;
		cout << CommCards[1].showNum << " " << CommCards[1].showSuit << endl;
		cout << CommCards[2].showNum << " " << CommCards[2].showSuit << endl;
		cout << CommCards[3].showNum << " " << CommCards[3].showSuit << endl;
		cout << "Your Cards" << endl;
		Table->getCurrPos()->data.displayHand();
	}
	else if (currCommCardLength = 5) {
		cout << "Community Cards" << endl;
		cout << CommCards[0].showNum << " " << CommCards[0].showSuit << endl;
		cout << CommCards[1].showNum << " " << CommCards[1].showSuit << endl;
		cout << CommCards[2].showNum << " " << CommCards[2].showSuit << endl;
		cout << CommCards[3].showNum << " " << CommCards[3].showSuit << endl;
		cout << CommCards[4].showNum << " " << CommCards[4].showSuit << endl;
		cout << "Your Cards" << endl;
		Table->getCurrPos()->data.displayHand();
	}
	else {
		cout << "Your Cards" << endl;
		Table->getCurrPos()->data.displayHand();
	}
}

void Game::Add2Table(int playerNum)
// Creates a player, and adds them to the Circular linked list Table
// Input: int to set player number
{
	Player * newPlayer = new Player();
	newPlayer->setPlayerNumber(playerNum);

	Table->putNode(*newPlayer);			// is *newPlayer a correct parameter logically for this function?
}

void Game::Kick(Player exitPlayer)
{
	Table->deleteNode(exitPlayer);
	Table->setListSize(-1);
}

void Game::getBets()
{
	Table->resetList();
	bool totalBetChange = false;

	// for loop of Table.length. Traverse table
	for (int i = 0; i < Table->getListSize(); i++) {
		
		// if next player elected to FOLD, skip
		if (Table->getCurrPos()->next->data.getPlayerChoice != FOLD) {

			// display cards
			displayCommCards();

			// get player choice
			Table->getNextNode()->data.setPlayerChoice();

			switch (Table->getCurrPos()->data.getPlayerChoice()) {
			case CHECK:

				// If no new bets have been made
				if (Table->getCurrPos()->data.getPlayerBet() == totalBet)
					break;
				else
					// ...Player must meet totalBet or fold
					do {
						cout << "Must meet current bet, or fold!" << endl;
						// display how much more must be bet		<--------------- DO THIS
						Table->getCurrPos()->data.setPlayerChoice();
					} while (Table->getCurrPos()->data.getPlayerChoice() == CHECK);

			case RAISE:

				totalBetChange = true;
				Table->getCurrPos()->data.setPlayerBet();
				setPot(PayIn(Table->getCurrPos()->data, Table->getCurrPos()->data.getPlayerBet()));
				totalBet += Table->getCurrPos()->data.getPlayerBet();
				break;

			case FOLD:

				Table->getCurrPos()->data.setFold(true);
				break;

			default:
				return;
			} // switch

		} // if Player.fold() == false
		else
			Table->getNextNode();

	} // for loop to traverse table

	if (totalBetChange) // all playerc met totalBet
		getBets();		// traverse list again, skip any players who have folded
}


