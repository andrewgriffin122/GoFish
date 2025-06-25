#include "Card.h"
#include <array>
#pragma once

class Deck;

//Can have 3 of each card before you play it, 
// so 3x thumber of ranks + 1 so there is space to add the card before playing it
//constexpr as this value can be computed at compile time, and doesnt need to be computed at run time
static constexpr int MAX_HAND_SIZE = (NUM_SUITS * NUM_RANKS) - NUM_RANKS + 1;

//Values for searching
static const int INVALID_CARD = -1;
static const int STARTING_SEARCH_SPOT = 0;
static const int STARTING_HAND_SPOT = 0;

class Hand
{
private:
	//Hand is an array as the max number of cards you can get in go fish is three of each suit before the fourth causes you to score
	std::array<Card, MAX_HAND_SIZE> hand;
	int currentSpotInHand;

public:
	Hand();

	int getSpotInHand() const;

	//Adding to and removing from the Hand using the Deck class
	void addCardToHandFromDeck(Deck &deck);
	void addCardsToHand(Card cards[], const int &num);
	bool removeCardFromHand(const Card &cardToRemove);
	void removeAllOfRank(const Rank &rank, Card removedCard[], int &spot);

	//To see if theres a match for Go Fish
	bool checkHasAllOfRank(const Rank &target);

	void sortByRank();
	void printHand() const;
};