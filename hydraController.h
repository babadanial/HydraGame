#ifndef _HYDRACONTROLLER_H_
#define _HYDRACONTROLLER_H_

#include "player.h"
#include "hydraModel.h"

class HydraController {
   HydraModel * theModel;
   int numPlayers;
   bool testing;

   public:
   // Constructor
   // sets the pointer to the HydraModel we will be using
   // as well as sets testing mode if necessary
   HydraController(HydraModel * model, int howManyPlayers, bool testingMode);

   // main function inside of which we run the game
   void runGame();

   // prints out current information on the heads in the game
   void printHeads();

   // prints out current information on the players
   void printPlayers(int cardsToPlay, int whoseTurn);
};

#endif