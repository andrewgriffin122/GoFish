#include <iostream>
#pragma once

static const int FULL_DECK = 52;
static const int NUM_SUITS = 4;
static const int NUM_RANKS = 13;

static const int MIN_RANK_NUM = 1;
static const int MAX_RANK_NUM = 13;

//Rank and suit both use char as an underlying type since the maximum value for each is less than 1 byte
enum class Rank : char{
    Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, OVER_RANK
};
enum class Suit : char{
    Clubs, Diamonds, Hearts, Spades, OVER_SUIT
};

//Created as a struct and left everything public so rank and suit member variables can be freely used
struct Card {
    Suit suit = Suit::Clubs;
    Rank rank = Rank::Ace;

    Card();
    Card(Suit s, Rank r);

    void printCard() const;

    //Overloaded instead of a function to make the code easier to read
    bool operator==(const Card& other) const;
    Card& operator=(const Card& other);
};

//Functions to convert the enum class into characters to use to display what the card is
const char* displayRank(const Rank &rank);
const char* displaySuit(const Suit &suit);

//Used in sorting the hand
bool compareRanks(const Card &first, const Card &second);