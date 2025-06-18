#include "Hand.h"
#include "Deck.h"
#include <algorithm>

//Initializing current spot of hand
Hand::Hand()
{
    currentSpotInHand = STARTING_HAND_SPOT;
}

int Hand::getSpotInHand() const
{
    return currentSpotInHand;
}

//Pass deck in by refrence to change the current spot of the deck
//Takes first card from deck and adds to the hand, and moves max of hand
//Also checks if there is a valid card returned, cards will be invalid if the end of deck has been reached
void Hand::addCardToHandFromDeck(Deck &deck)
{
    if (auto temp = deck.getCardFromDeck())
    {
        hand[currentSpotInHand] = *temp;
        currentSpotInHand++;
    }
}

//Adds cards that have already been selected to the hand
//It is assumed that each of the cards is a valid card
void Hand::addCardsToHand(Card cards[], const int &num)
{
    for (int i = 0; i < num; i++)
    {
        hand[currentSpotInHand] = cards[i];
        currentSpotInHand++;
    }
}

//Goes through hand to find the passed in card 
// Removes the card by moving over all the cards after it in the hand
bool Hand::removeCardFromHand(const Card &cardToRemove)
{
    auto new_end = std::remove_if(hand.begin(), hand.begin() + currentSpotInHand, 
                    [cardToRemove](Card handCard) {return handCard == cardToRemove; });

    //nothing changed
    if (new_end == hand.begin() + currentSpotInHand)
    {
        return false;
    }

    currentSpotInHand--;
    return true;
}

//Simple function to remove all of a given rank
//Moves the spot variable so other functions can know how many have been removed
void Hand::removeAllOfRank(const Rank &rank, Card removedCard[], int &spot)
{
    spot = STARTING_SEARCH_SPOT;
    Card temp;

    //For each suit, create a card of that Rank, find it in the hand and remove it
    for (int i = 0; i < NUM_SUITS; i++)
    {
        temp = Card(static_cast<Suit>(i), rank);
        if (removeCardFromHand(temp))
        {
            removedCard[spot] = temp;
            spot++;
        }
    }
}

//Check if the given hand has all of a certain rank
bool Hand::checkHasAllOfRank(const Rank& target)
{
    int count = 0;

    for (int i = 0; i < currentSpotInHand; i++)
    {
        if (hand[i].rank == target)
        {
            count++;
            //Max number of cards for each rank is how many suits there are
            if (count == NUM_SUITS)
            {
                return true;
            }
        }
    }

    return false;
}

//Sort using compareRanks, which only uses the card.rank and checks the enum values against each other
void Hand::sortByRank()
{
    std::sort(hand.begin(), hand.end(), compareRanks);
}

//To make printing the hand easier
void Hand::printHand() const
{
    for (int i = 0; i < currentSpotInHand; i++)
    {
       hand[i].printCard();
       std::cout << ", ";
    }
    std::cout << "\n";
}