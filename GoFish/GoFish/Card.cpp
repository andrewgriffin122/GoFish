#include "Card.h"

Card::Card()
{
    suit = Suit::OVER_SUIT;
    rank = Rank::OVER_RANK;
}

//Parameterized Constructor
Card::Card(Suit s, Rank r)
{
    suit = s;
    rank = r;
}

//To make printing each card easier
void Card::printCard() const
{
    std::cout << displayRank(rank) << " " << displaySuit(suit);
}

//Overloading operators so I can compare card ranks
//Overloaded the operater instead of making a member function because it is easier to read with the ==
bool Card::operator==(const Card& other) const
{
    return suit == other.suit && rank == other.rank;
}

//Same as the previous operator
Card& Card::operator=(const Card& other)
{
    suit = other.suit;
    rank = other.rank;
    return *this;
}

//For printing
const char* displayRank(const Rank &rank) 
{
    switch (rank) 
    {
    case Rank::Ace:   return "Ace";
    case Rank::Two:   return "2";
    case Rank::Three: return "3";
    case Rank::Four:  return "4";
    case Rank::Five:  return "5";
    case Rank::Six:   return "6";
    case Rank::Seven: return "7";
    case Rank::Eight: return "8";
    case Rank::Nine:  return "9";
    case Rank::Ten:   return "10";
    case Rank::Jack:  return "Jack";
    case Rank::Queen: return "Queen";
    case Rank::King:  return "King";
    default:          return "Unknown";
    }
}

//For printing
const char* displaySuit(const Suit &suit) 
{
    switch (suit) 
    {
    case Suit::Clubs:    return "Clubs";
    case Suit::Diamonds: return "Diamonds";
    case Suit::Hearts:   return "Hearts";
    case Suit::Spades:   return "Spades";
    default:             return "Unknown";
    }
}

//Used to sort a hand, taken from:https://www.geeksforgeeks.org/sort-c-stl/
bool compareRanks(const Card &first, const Card &second)
{
    return static_cast<int>(first.rank) < static_cast<int>(second.rank);
}