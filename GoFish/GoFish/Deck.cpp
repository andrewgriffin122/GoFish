#include "Deck.h"

//Sets currentSpot as 0, which would be the top of the deck
//Fills up the deck with cards
Deck::Deck()
{
    currentSpotInDeck = 0;
    fillDeck();
}

//Moves counter for top of deck and returns the top of deck
//Also checks if the end of the deck has been reached, and changes validCard as needed
Card Deck::getCardFromDeck(bool &validCard)
{
    if (currentSpotInDeck == FULL_DECK)
    {
        validCard = false;
        return Card(Suit::Clubs, Rank::Ace);
    }

    validCard = true;
    currentSpotInDeck++;
    return deck[currentSpotInDeck - 1];
}

//To know how far along the deck the counter is
int Deck::getCurrentSpotInDeck() const
{
    return currentSpotInDeck;
}

//fill taken from: https://www.geeksforgeeks.org/how-to-represent-the-deck-of-cards-using-array-in-cpp/
//Sets rank and suit so their is one of each
void Deck::fillDeck()
{
    for (int i = 0; i < NUM_SUITS; i++)
    {
        for (int j = 0; j < NUM_RANKS; j++)
        {
            deck[i * NUM_RANKS + j].rank = Rank(j + 1);
            deck[i * NUM_RANKS + j].suit = Suit(i);
        }
    }
}

//from: https://cplusplus.com/reference/algorithm/shuffle/
void Deck::shuffleDeck()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
}

//To make displaing hand easier
void Deck::printDeck() const
{
    for (int i = 0; i < NUM_SUITS; i++)
    {
        for (int j = 0; j < NUM_RANKS; j++)
        {
            deck[i * NUM_RANKS + j].printCard();
            std::cout << ", ";
        }
        std::cout << "\n";
    }
}
