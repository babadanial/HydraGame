#include "hydraController.h"

using namespace std;

HydraController::HydraController(HydraModel * model, int howManyPlayers, bool testingMode): theModel{model}, numPlayers{howManyPlayers}, testing{testingMode} {}

void HydraController::printHeads() {
   cout << "Heads:" << endl;
   for (auto headIter = theModel->heads.begin(); headIter != theModel->heads.end(); ++headIter) {
      cout << (*headIter)->getHeadNumber() << ": ";
      cout << (*headIter)->seeTopCard()->getName() << " ";
      cout << "(" << (*headIter)->getSize() << ")" << endl;
   }
}

// whoseTurn is -1 if it's nobody's turn
void HydraController::printPlayers(int cardsToPlay , int whoseTurn = -1) {
   cout << "Players:" << endl;
   int numPlayers = theModel->players.size();
   for (int i = 0; i < numPlayers; ++i) {
      cout << "Player " << (i + 1) << ": ";
      int drawPileSize = theModel->players.at(i)->drawPileSize();
      int discardPileSize = theModel->players.at(i)->discardPileSize();
      int totalCards = drawPileSize + discardPileSize;


      cout << totalCards << " (" << drawPileSize << " draw, ";
      cout << discardPileSize << " discard)";


      if (i == whoseTurn) {
         cout << " + 1 in hand, ";
         cout << (cardsToPlay - 1) << " remaining, ";
         if (theModel->players.at(i)->reservePresent()) {
            cout << "1 ";
         } else {
            cout << "0 ";
         }
         cout << "in reserve" << endl;
      } else {
         cout << endl;
      }

   }
}

void HydraController::runGame() {
   cin.exceptions(ios::eofbit|ios::failbit);
   int whoseTurn = 1; // not 0 - we start at player 2's turn
   int cardsToPlay = 1;
   bool gameWon = 0;
   int moveSatisfied;
   int move;

   while (1) {
      // reset the number of cards to play
      cardsToPlay = theModel->numHeads();

      // print out the Heads necessary to show the player
      //    before each move
      printHeads();

      // print out the necessary information on the players
      //    that they must see before each move
      cout << endl;
      printPlayers(cardsToPlay); 
      // -1 because we do not want to print turn information for a player yet

      // print out beginning-of-turn interactive prompt
      cout << endl;
      cout << "Player " << (whoseTurn + 1) << ", it is your turn." << endl;
      cout << endl;

      // now the following while loop takes care of all the 
      //    "rounds" of a player's turn
      try {
         while (cardsToPlay > 0) {
            // reset the flag variable as to whether the move was valid
            moveSatisfied = 0;


            // let's set up a pointer to the player whose turn
            //    it is for easy access.
            Player * thePlayer = theModel->players.at(whoseTurn).get();
            // and see if they already have a card in hand
            bool hasCardAlready = thePlayer->hasCardInHand();


            // draw a card for the player whose turn it is,
            //    if they do not already have a card in hand
            if (!hasCardAlready && !thePlayer->drawPileEmpty()) {
               thePlayer->drawFromDrawPile();
            // add discard to draw pile and then draw if draw pile is empty
            } else if (!hasCardAlready && !thePlayer->discardPileEmpty()) {
               thePlayer->addDiscardToDraw();
               thePlayer->drawFromDrawPile();
            // put reserve back on top of draw pile if both draw & discard piles
            //    are empty
            } else if (!hasCardAlready && thePlayer->reservePresent()) {
               thePlayer->returnReserve();
               cardsToPlay = 0;
            // check if they've won
            } else if (!hasCardAlready && thePlayer->inWinningCondition()) {
               cout << "Player " << (whoseTurn + 1) << " wins!" << endl;
               gameWon = 1;
               break;
            }


            // we show the player the number of heads, and player information
            //    including special information on their current state
            printHeads();
            cout << endl;
            printPlayers(cardsToPlay, whoseTurn);
            cout << endl;


            // now, we take care of displaying the interactive prompt
            if (cardsToPlay != 0) {
               string cardname = thePlayer->viewCardInHand()->getName();
               cout << "Player " << (whoseTurn + 1) << ", ";
               if (!testing) {
                  cout << "you are holding a " << cardname << ". ";
               } else {
                  // and entering card value & suit if we are in testing mode
                  cout << "you are holding a..." << endl;
                  theModel->testingCardEntry(thePlayer->viewCardInHand());
               }
            }


            // and now we receive the player's choice of move 
            //    and determine whether it's valid 
            while (moveSatisfied == 0) {
               cout << "Your move?" << endl;
               cin >> move;
               cout << endl;
               if (move == 1000000 && testing) {
                  moveSatisfied = 4;
                  --cardsToPlay;
               } else {
                  moveSatisfied = theModel->isValidMove(move, thePlayer->viewCardInHand());
               }
            }

            
            // first we check if we are swapping a card into a previously-empty
            //    reserve spot
            bool reserveEmpty = 0;
            if (!thePlayer->reservePresent() && move == 0) {
               reserveEmpty = 1;
            }


            // and now we perform the move
            theModel->performMove(move, moveSatisfied, whoseTurn);


            // and decrement the number of cards as necessary...
            if (move == 0 && moveSatisfied == 1 && reserveEmpty) {
               --cardsToPlay;
            } else if (move > 0 && moveSatisfied == 1) {
               --cardsToPlay;
            } else if (move > 0 && (moveSatisfied == 2 || moveSatisfied == 3)) {
               cardsToPlay = 0;
            }


            // if the player's turn is over...
            if (cardsToPlay == 0) {
               // check if the player has won (at the end of their turn)
               if (thePlayer->inWinningCondition()) {
                  cout << "Player " << (whoseTurn + 1) << " wins!" << endl;
                  gameWon = 1;
                  break;
               }

               // otherwise, move on to the next player's turn after putting
               //    their reserve card back on top of their draw pile
               thePlayer->returnReserve();

               if (whoseTurn == (numPlayers - 1)) {
                  whoseTurn = 0;
               } else {
                  ++whoseTurn;
               }
            }
         }
      }  
      // handle exceptions from reading input below
      catch (ios::failure &) {
         if (cin.eof()) {
            break;
         }
   
         cin.clear();
         cin.ignore();
      }

      if (gameWon) {
         break;
      }
   }
}