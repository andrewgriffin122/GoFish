#include "Card.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <array>
#include <optional>
#pragma once


class Deck {
private:
    //Deck is an array as there is a fixed size of cards
    std::array<Card, FULL_DECK> deck;
    int currentSpotInDeck;

public:
    Deck();

    int getCurrentSpotInDeck() const;

    //Gets the current card and moves along the counter
    std::optional<Card> getCardFromDeck();
    
    //Functions to manipulate the deck initially 
    void fillDeck();
    void shuffleDeck();

    void printDeck() const;
};