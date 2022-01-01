#ifndef _HYDRAMODEL_H_
#define _HYDRAMODEL_H_
#include "player.h"

class HydraModel {
   bool testing;
   std::vector<std::unique_ptr<Player>> players;
   std::vector<std::unique_ptr<Deck>> heads;

   friend class HydraController;

   public:
   // constructs the model object, creating decks and players
   //    and dealing necessary number of cards to each player
   HydraModel(int numPlayers, bool testingMode);

   // function that assigns new values to
   //    the given card in testing mode
   void testingCardEntry(std::shared_ptr<Card> & theCard);
   // performs process of cuts a head off, creating two more
   void cutHead(int playerNumber);

   // returns the "ID" number of the first Head
   int startingHeadNum();

   // returns the number of heads currently present in the game
   int numHeads();

   // reads in a rank for the joker in hand and sets it accordingly
   void takeJokerValue(std::shared_ptr<Card> & cardInHand);

   // checks if the given player won
   bool didPlayerWin(int playerNum);

   // performs player 1's move for them and creates
   //    a head once the HydraModel object has been
   //    initialized
   void init();

   // determines whether the given move is valid
   //    returns 0 if invalid
   //    returns 1 if valid and decreases cards to play by 1
   //    returns 2 if valid but immediately ends turn
   //    returns 3 if we should cut off a head
   int isValidMove(int move, std::shared_ptr<Card> & cardInHand);

   // performs the desired move with the given move code and player
   void performMove(int move, int moveCode, int playerNumber);

   // finds the index of the head with the given number
   //    returns -1 if could not be found - but this outcome
   //    should not occur if fn. is used correctly
   int findHeadIndex(int headID);

   // checks if a valid move of type 1, 2, or 3 exists
   //    given a card's rank (i.e. checks all heads in the game)
   bool validMoveExists(Rank cardRank);

   // checks if a number is a valid head number
   bool isValidHeadNumber(int num);

   // returns the "ID" number of the first head in heads
   int firstHeadNumber();

   /*
   // resets all jokers in the given head to the "unset joker" rank
   void resetAllJokers(int headIndex = 0);
   */
};

#endif