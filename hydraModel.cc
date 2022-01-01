#include "hydraModel.h"

using namespace std;

void HydraModel::testingCardEntry(shared_ptr<Card> & theCard) {
   string rank, suit;
   Rank cardNewRank;
   Suit cardNewSuit;
   bool rankSatisfied = 0;
   bool suitSatisfied = 0;
   bool wasJoker = 0;

   while (!rankSatisfied) {
      cout << "Card value?" << endl;
      cin >> rank;
      if (rank == "A") {
         cardNewRank = Rank::Ace;
         rankSatisfied = 1;
      } else if (rank == "J") {
         cardNewRank = Rank::Jack;
         rankSatisfied = 1;
      } else if (rank == "Q") {
         cardNewRank = Rank::Queen;
         rankSatisfied = 1;
      } else if (rank == "K") {
         cardNewRank = Rank::King;
         rankSatisfied = 1;
      } else if (rank == "2") {
         cardNewRank = Rank::Two;
         rankSatisfied = 1;
      } else if (rank == "3") {
         cardNewRank = Rank::Three;
         rankSatisfied = 1;
      } else if (rank == "4") {
         cardNewRank = Rank::Four;
         rankSatisfied = 1;
      } else if (rank == "5") {
         cardNewRank = Rank::Five;
         rankSatisfied = 1;
      } else if (rank == "6") {
         cardNewRank = Rank::Six;
         rankSatisfied = 1;
      } else if (rank == "7") {
         cardNewRank = Rank::Seven;
         rankSatisfied = 1;
      } else if (rank == "8") {
         cardNewRank = Rank::Eight;
         rankSatisfied = 1;
      } else if (rank == "9") {
         cardNewRank = Rank::Nine;
         rankSatisfied = 1;
      } else if (rank == "10") {
         cardNewRank = Rank::Ten;
         rankSatisfied = 1;
      } else if (rank == "Joker") {
         wasJoker = 1;
         rankSatisfied = 1;
      } else {
         rankSatisfied = 0;
      }
      cout << endl; // so that new input is entered on a fresh line
   }

   while (!suitSatisfied && !wasJoker) {
      cout << "Suit?" << endl;
      cin >> suit;
      if (suit == "S") {
         cardNewSuit = Suit::S;
         suitSatisfied = 1;
      } else if (suit == "D") {
         cardNewSuit = Suit::D;
         suitSatisfied = 1;
      } else if (suit == "C") {
         cardNewSuit = Suit::C;
         suitSatisfied = 1;
      } else if (suit == "H") {
         cardNewSuit = Suit::H;
         suitSatisfied = 1;
      } else {
         suitSatisfied = 0;
      }
      cout << endl; // so that new input/output is on a fresh line
   }

   if (wasJoker) {
      theCard = make_shared<Joker>();
   } else {
      theCard = make_shared<Card>(cardNewSuit, cardNewRank);
   }
}

HydraModel::HydraModel(int numPlayers, bool testingMode): testing{testingMode} {
   Deck chief = Deck{false};

   // add as many decks as the number of players to the
   //    chief deck we will be distributing from
   for (int i = 0; i < numPlayers; ++i) {
      Deck toAdd = Deck{true};
      chief.addDeck(toAdd);
      chief.shuffle();
   }

   // allocate the player objects and add them to the players vector
   for (int i = 0; i < numPlayers; ++i) {
      players.emplace_back(make_unique<Player>());
   }

   // now we deal 54 cards to each player
   // for each player...
   for (int i = 0; i < numPlayers; ++i) {
      // 54 times...
      for (int j = 0; j < 54; ++j) {
         // draw a card
         auto thisCard = chief.drawCard();
         // and deal it to them
         players.at(i)->addToBottomOfDrawPile(thisCard);
      }
   }
}

void HydraModel::init() {
   // we draw a card from player 1's draw pile into player
   //    1's hand
   players.at(0)->drawFromDrawPile();

   // and play that card...
   auto firstCard = players.at(0)->playHand();

   // and we give the user the option to customize it if in testing mode
   if (testing) {
      cout << "For the first card in the first head..." << endl;
      cout << endl;
      testingCardEntry(firstCard);
   }

   // we check if the firstCard is a Joker, in which case
   //    we assign it value 2
   if (firstCard->isJoker()) {
      firstCard->setRank(Rank::Two);
   }
   
   // and before we play the card into the first head, we
   //    need to create it and add it to the heads vector
   heads.emplace_back(make_unique<Deck>(false, 1));

   // and now we add the card to the first head
   heads.at(0)->addCardToTop(firstCard);
}

int HydraModel::firstHeadNumber() {
   return heads.at(0)->getHeadNumber();
}

int HydraModel::numHeads() {
   return heads.size();
}

bool HydraModel::validMoveExists(Rank cardRank) {
   int rankInt = static_cast<int>(cardRank);

   for (auto head = heads.begin(); head != heads.end(); ++head) {
      shared_ptr<Card> & topCard = (*head)->seeTopCard();
      Rank topCardRank = topCard->getRank();
      if (topCardRank == Rank::Ace) {
         return 1;
      }
      int topCardRankInt = static_cast<int>(topCardRank);
      if (topCardRankInt >= rankInt) {
         return 1;
      }
   }
   return 0;
}

bool HydraModel::isValidHeadNumber(int num) {
   for (auto head = heads.begin(); head != heads.end(); ++head) {
      int thisHeadNum = (*head)->getHeadNumber();
      if (thisHeadNum == num) {
         return 1;
      }
   }
   return 0;
}

int HydraModel::findHeadIndex(int headID) {
   int numHeads = heads.size();
   for (int i = 0; i < numHeads; ++i) {
      if (heads.at(i)->getHeadNumber() == headID) {
         return i;
      }
   }
   return -1;
}

void HydraModel::takeJokerValue(shared_ptr<Card> & cardInHand) {
   bool rankSatisfied = 0;
   string rank;
   Rank cardNewRank;

   while (!rankSatisfied) {
      cout << "Joker value?" << endl;
      cin >> rank;
      if (rank == "A") {
         cardNewRank = Rank::Ace;
         rankSatisfied = 1;
      } else if (rank == "J") {
         cardNewRank = Rank::Jack;
         rankSatisfied = 1;
      } else if (rank == "Q") {
         cardNewRank = Rank::Queen;
         rankSatisfied = 1;
      } else if (rank == "K") {
         cardNewRank = Rank::King;
         rankSatisfied = 1;
      } else if (rank == "2") {
         cardNewRank = Rank::Two;
         rankSatisfied = 1;
      } else if (rank == "3") {
         cardNewRank = Rank::Three;
         rankSatisfied = 1;
      } else if (rank == "4") {
         cardNewRank = Rank::Four;
         rankSatisfied = 1;
      } else if (rank == "5") {
         cardNewRank = Rank::Five;
         rankSatisfied = 1;
      } else if (rank == "6") {
         cardNewRank = Rank::Six;
         rankSatisfied = 1;
      } else if (rank == "7") {
         cardNewRank = Rank::Seven;
         rankSatisfied = 1;
      } else if (rank == "8") {
         cardNewRank = Rank::Eight;
         rankSatisfied = 1;
      } else if (rank == "9") {
         cardNewRank = Rank::Nine;
         rankSatisfied = 1;
      } else if (rank == "10") {
         cardNewRank = Rank::Ten;
         rankSatisfied = 1;
      } else {
         rankSatisfied = 0;
      }
      cout << endl;
   }

   cardInHand->setRank(cardNewRank); 
}

int HydraModel::isValidMove(int move, shared_ptr<Card> & cardInHand) {
   bool joker = 0;

   
   // first, we check if the move is simply a reserve swap and act accordingly
   if (move == 0 && numHeads() > 1) {
      return 1;
   } else if (move == 0) {
      return 0;
   }


   // if not a swap, then check if the desired head number is even valid
   if (!isValidHeadNumber(move)) {
      return 0;
   }


   // then, we need to get the index of head with the desired head number
   int index = findHeadIndex(move);
   unique_ptr<Deck> & theHead = heads.at(index);
   // and check if this move could trigger cutting off a head
   bool couldCut = 0;
   if (index == 0) {
      couldCut = 1;
   }


   // and we record the ranks of the card in hand and the head's top card
   Rank handRank = cardInHand->getRank();
   Rank topRank = theHead->seeTopCard()->getRank();


   // we check if the card is a joker in which case we take a value for it
   if (cardInHand->isJoker()) {
      joker = 1;
      takeJokerValue(cardInHand);
      handRank = cardInHand->getRank();
   }


   // then, we check if the head's top card or the card in hand
   //    is an Ace and decide accordingly
   // if they're both aces, the player's turn ends
   if (handRank == Rank::Ace && topRank == Rank::Ace) {
      return 2;
   // if one of them is an ace, then the move is simply valid
   } else if (handRank == Rank::Ace || topRank == Rank::Ace) {
      return 1;
   }


   // then, we compare the card rank to the top card's rank
   if (handRank < topRank) {
      return 1;
   } else if (handRank == topRank) {
      return 2;
   } else if (joker) { 
      // handSuit > topSuit and hand has a joker 
      //    so we can fix it by giving the joker another value !
      //    (Ace if all else fails)
      return 0;
   } else if (validMoveExists(handRank) || !couldCut) {
      return 0;
   } else { 
      // no other valid move exists and we entered the first head
      // and the current card is not a joker
      // so we need to cut head
      return 3; 
   }
}

void HydraModel::cutHead(int playerNumber) {
   // first, we set up a pointer to the player performing the head-cutting
   Player * thePlayer = players.at(playerNumber).get();

   // then, we go through the oldest head and reset all of its jokers
   heads.at(0)->resetAllJokers();

   // then, we add the card currently in hand to the top of the discard pile,
   //    as well as the reserve (if it exists)
   thePlayer->addHandToDiscard();
   thePlayer->addReserveToDiscard();

   // now, we get the ID number of the newest head and calculate ID numbers for
   //    the new heads
   int baseID = heads.at(heads.size() - 1)->getHeadNumber();
   int newID1 = baseID + 1;
   int newID2 = baseID + 2;

   // then, we add the oldest head to the player's discard pile and 
   //    destroy that head
   thePlayer->addHeadToDiscard(heads.at(0));
   heads.erase(heads.begin());

   // add the discard pile to the draw pile if draw pile has <2 cards
   if (thePlayer->drawPileSize() < 2) {
      thePlayer->addDiscardToDraw();
   }

   // and now we create the two new heads
   heads.emplace_back(make_unique<Deck>(false, newID1));
   heads.emplace_back(make_unique<Deck>(false, newID2));

   // and now we draw two cards to anchor these heads with
   shared_ptr<Card> anchor1 = thePlayer->withdrawFromDrawPile();
   shared_ptr<Card> anchor2 = thePlayer->withdrawFromDrawPile();

   // take new values for the two anchor cards if we're in testing mode
   if (testing) {
      cout << "For the first card in the first new head:" << endl;
      cout << endl;
      testingCardEntry(anchor1);
      cout << "For the first card in the second new head:" << endl;
      cout << endl;
      testingCardEntry(anchor2);
   }

   // and if any of the anchor cards are jokers, we set them to be 2
   if (anchor1->getRank() == Rank::unsetJoker) {
      anchor1->setRank(Rank::Two);
   }
   if (anchor2->getRank() == Rank::unsetJoker) {
      anchor2->setRank(Rank::Two);
   }

   // and now we add the cards to their respective heads
   heads.at(heads.size() - 2)->addCardToTop(anchor1);
   heads.at(heads.size() - 1)->addCardToTop(anchor2);
}

void HydraModel::performMove(int move, int moveCode, int playerNumber) {
   // obtain a reference to the player making the move
   unique_ptr<Player> & thePlayer = players.at(playerNumber);

   // check if the move was 1000000 (cheat code)
   if (move == 1000000 && moveCode == 4) {
      thePlayer->forceWin();
      return;
   }

   // swap with reserve if that was the move
   if (move == 0 && moveCode == 1) {
      bool reserveAlready = thePlayer->reservePresent();
      thePlayer->swapReserveWithHand(); 
      if (testing && reserveAlready) {
         cout << "For card from reserve coming into your hand..." << endl;
         testingCardEntry(thePlayer->viewCardInHand());
         cout << endl;
      }
      return;
   } 
   
   // if not a swap get a reference to the actual head referenced by the 
   //    inputted head number
   unique_ptr<Deck> & theHead = heads.at(findHeadIndex(move));

   // and then perform the move or cut head, as necessary
   if (move > 0 && (moveCode == 1 || moveCode == 2)) {
      shared_ptr<Card> theCard = thePlayer->playHand();
      theHead->addCardToTop(theCard);
      return;
   } else if (moveCode == 3) {
      cutHead(playerNumber);
      return;
   }
   cout << "MADE IT HERE? UH OH!" << endl;
}