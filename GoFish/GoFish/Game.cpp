#include "Hand.h"
#include "GoFish.h"

int main()
{
    GoFish game; //Contains all the information to play the game Go Fish
    Deck deck;   //Creates a standard deck of cards and fills it up
    Hand h1, h2; //Go fish has been made as a two player game so two hands, or players, are made

    game.gameLoop(deck, h1, h2);
}
