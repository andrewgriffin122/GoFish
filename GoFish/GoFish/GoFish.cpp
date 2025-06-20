#include "GoFish.h"
#include "Hand.h"
#include "Deck.h"
#include <algorithm>
#include <string>

GoFish::GoFish()
{
	playerOneScore = 0;
	playerTwoScore = 0;
	playing = true;
	playerOneTurn = true;
}

//Asks which card to search for. If card is outside of bounds, then asks again
int GoFish::getUserChoice()
{
	//Resetting values
	int static intChoice = 0;
	std::string static choice = "A";

	std::cout << "\n";
	std::cout << "Ask for an Ace(1), Two(2), Three(3), Four(4), Five(5), Six(6), Seven(7), \n Eight(8), Nine(9), Ten(10), Jack(11), Queen(12), or a King(13):";

	while (true)
	{
		std::cin >> choice;
		if (std::all_of(choice.begin(), choice.end(), std::isdigit))
		{
			intChoice = std::stoi(choice);

			//Bounds for the cards
			if (intChoice > MIN_RANK_NUM || intChoice < MAX_RANK_NUM)
			{
				break;
			}
		}

		std::cout << "Invalid selection. Please choose from the given options:";
	}

	std::cout << "\n";

	return intChoice;
}

//Shuffles deck, adds cards to each hand, sorts hand for displaying
void GoFish::initializeGame(Deck& deck, Hand& playerOne, Hand& playerTwo)
{
	deck.shuffleDeck();

	//Each player stars with the same number of cards
	//Cards are delt to back and forth between hands
	for (int i = 0; i < STARTING_CARD_NUM; i++)
	{
		playerOne.addCardToHandFromDeck(deck);
		playerTwo.addCardToHandFromDeck(deck);
	}

	playerOne.sortByRank();
	playerTwo.sortByRank();
}

//Asks which card to ask for, if other hand has it, removes from other hand and adds to current hand
// //If other hand doesn't, draws a card from the deck
//Checks if hand has all of a given rank
void GoFish::playTurn(Deck & deck, Hand & turn, Hand & other)
{
	//Static so they are only created once, and only in the scope of this function
	static Rank rankChoice = Rank::Ace;
	static Card removedCard[NUM_SUITS];
	static int spot = STARTING_SEARCH_SPOT;

	//Displays whose turn it is
	if (playerOneTurn)
	{
		std::cout << "Player One's hand:\n";
	}
	else
	{
		std::cout << "Player Two's hand:\n";
	}
	turn.printHand();

	//Gets the rank using the getUserChoice() function
	rankChoice = static_cast<Rank>(getUserChoice());

	//Removes all of the rank from the other players hand
	//Those cards go into the removedCard array and counts up spot as it goes
	other.removeAllOfRank(rankChoice, removedCard, spot);

	//If cards have been added to the array
	//then add the cards in the array to the current players hand
	if (spot != STARTING_SEARCH_SPOT)
	{
		turn.addCardsToHand(removedCard, spot);
		turn.sortByRank();
	}
	//If no cards have been removed, then its Go Fish
	else
	{
		std::cout << "Go Fish!\n\n";
		turn.addCardToHandFromDeck(deck);
		turn.sortByRank();
	}

	//If a player has all of a given rank they score a point in Go Fish
	if (turn.checkHasAllOfRank(rankChoice))
	{
		std::cout << "You got all four " << displayRank(rankChoice) << " cards!\n\n";

		//Remove cards from hand so the other player can't ask for them, or the cards get scored muultiple times
		turn.removeAllOfRank(rankChoice, removedCard, spot);

		if (playerOneTurn)
		{
			playerOneScore++;
		}
		else
		{
			playerTwoScore++;
		}
	}

	//Dividing line to make things slightly easier to read
	std::cout << "--------------------------------------------------------------------------------------------\n\n\n";
}

//Check if the game is over by an empty deck and both hands are empty
bool GoFish::checkEndGame(const Deck& deck, const Hand& playerOne, const Hand& playerTwo) const
{
	//repeat until no cards left in deck or either hand
	if (deck.getCurrentSpotInDeck() > MAX_HAND_SIZE && playerOne.getSpotInHand() == STARTING_HAND_SPOT && playerTwo.getSpotInHand() == STARTING_HAND_SPOT)
	{
		//Displays who wins
		if (playerOneScore > playerTwoScore)
		{
			std::cout << "Player one wins!\n";
		}
		else if (playerOneScore < playerTwoScore)
		{
			std::cout << "Player two wins!\n";
		}
		//Technically not possible with 13 ranks but good to have in case
		else
		{
			std::cout << "Tie game!\n";
		}

		return true;
	}

	return false;
}

//Entry point for Go Fish, handles running the entire game
void GoFish::gameLoop(Deck &deck, Hand &playerOne, Hand &playerTwo)
{
	//shuffles deck and fills hands
	initializeGame(deck, playerOne, playerTwo);
	
	while (playing)
	{
		//Display remaining cards so players know much is left
		std::cout << "Cards left in deck:" << (FULL_DECK - deck.getCurrentSpotInDeck()) << "\n\n";

		//Swaps back and forth between different hands 
		if (playerOneTurn)
		{
			playTurn(deck, playerOne, playerTwo);
		}
		else
		{
			playTurn(deck, playerTwo, playerOne);
		}

		playerOneTurn = !playerOneTurn;

		playing = !checkEndGame(deck, playerOne, playerTwo);
	}
}