#pragma once

class Deck;
class Hand;
enum class Rank : char;

const int STARTING_CARD_NUM = 7;

class GoFish
{
private:
	bool playing;
	bool playerOneTurn;
	int playerOneScore, playerTwoScore;

	//Private functions as only the gameLoop needs to be visable to main
	int getUserChoice();

	//Shuffles deck, adds cards to each hand, sorts hand for displaying
	void initializeGame(Deck& deck, Hand& playerOne, Hand& playerTwo);

	void displayTurn(const Hand& turn) const;
	bool addToScore(Hand& turn, const Rank &choice);

	//Asks which card to ask for, if other hand has it, removes from other hand and adds to current hand
	//If other hand doesn't, draws a card from the deck
	//Checks if hand has all of a given rank
	void playTurn(Deck& deck, Hand& turn, Hand& others);

	//Check if the game is over by an empty deck and both hands are empty
	bool checkEndGame(const Deck& deck, const Hand& playerOne, const Hand& playerTwo) const;

public:
	GoFish();

	void gameLoop(Deck &deck, Hand &playerOne, Hand &playerTwo);
};