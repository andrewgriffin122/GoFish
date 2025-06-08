#include "Card.h"
#include <algorithm>
#include <random>
#include <chrono>
#pragma once


class Deck {
private:
    //Deck is an array as there is a fixed size of cards
    Card deck[FULL_DECK];
    int currentSpotInDeck;

public:
    Deck();

    int getCurrentSpotInDeck() const;

    //Gets the current card and moves along the counter
    Card getCardFromDeck(bool &validCard);

    //Functions to manipulate the deck initially 
    void fillDeck();
    void shuffleDeck();

    void printDeck() const;
};