#include "Hand.h"
#include "Deck.h"
#include <algorithm>

//Initializing current spot of hand
Hand::Hand() : currentSpotInHand(STARTING_HAND_SPOT)
{ }

int Hand::getSpotInHand() const
{
    return currentSpotInHand;
}

//Takes first card from deck and adds to the hand, and moves max of hand
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

//Uses remove_if to find and remove the cardToRemove. 
// Decreases currentSpotInHand if the operation is successful
bool Hand::removeCardFromHand(const Card &cardToRemove)
{
    auto new_end = std::remove_if(hand.begin(), hand.begin() + currentSpotInHand, 
                    [&cardToRemove](const Card& handCard) {return handCard == cardToRemove; });

    //nothing changed
    if (new_end == hand.begin() + currentSpotInHand)
    {
        return false;
    }

    currentSpotInHand--;
    return true;
}

//Moves the spot variable so other functions can know how many have been removed
void Hand::removeAllOfRank(const Rank &rank, Card removedCard[], int &spot)
{
    spot = STARTING_SEARCH_SPOT;
    static Card temp;

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

//Check if the given hand has all of a certain rank using count_if
bool Hand::checkHasAllOfRank(const Rank& target)
{
    int count = std::count_if(hand.begin(), hand.begin() + currentSpotInHand,
        [&target](const Card& handCard) {return handCard.rank == target; });

    return count == NUM_SUITS;
}

//Sort using compareRanks, which only uses the card.rank and checks the enum values against each other
void Hand::sortByRank()
{
    std::sort(hand.begin(), hand.begin() + currentSpotInHand, compareRanks);
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