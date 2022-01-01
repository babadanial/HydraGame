#include "deck.h"

using namespace std;

Deck::Deck(bool fullDeckWanted, int headNum): headNumber{headNum} {
   if (fullDeckWanted) {
      // iterates through types, creating the 52
      //    "main" cards of the deck and adding them
      for (int rank = 1; rank < 14; ++rank) {
         for (int suit = 0; suit < 4; ++suit) {
            auto c = make_shared<Card>(static_cast<Suit>(suit),static_cast<Rank>(rank));
            theDeck.push_back(c);
         }
      }

      // and we make & add the jokers as well
      auto j1 = make_shared<Joker>();
      auto j2 = make_shared<Joker>();
      theDeck.push_back(j1);
      theDeck.push_back(j2);
   }
}

void Deck::addCardToBottom(shared_ptr<Card> cardToAdd) {
   theDeck.push_back(cardToAdd);
}

void Deck::addCardToTop(shared_ptr<Card> cardToAdd) {
   theDeck.push_front(cardToAdd);
}

void Deck::shuffle() {
   // obtain time-based seed
   auto seed = std::chrono::system_clock::now().time_since_epoch().count();
   // and shuffle using that seed
   std::shuffle(theDeck.begin(), theDeck.end(), std::default_random_engine(seed));
}

void Deck::resetAllJokers() {
   for (auto cardIter = theDeck.begin(); cardIter != theDeck.end(); ++cardIter) {
      if ((*cardIter)->isJoker()) {
         (*cardIter)->setRank(Rank::unsetJoker);
      }
   }
}

shared_ptr<Card> Deck::findCard(Suit desiredSuit, Rank desiredRank) {
   shared_ptr<Card> target;
   for (auto aCard : theDeck) {
      shared_ptr<Card> toCheck = aCard;
      // remember range-based for loops do not use iterators
      //    you are DIRECTLY accessing elements
      if ((toCheck->getSuit() == desiredSuit) && (toCheck->getRank() == desiredRank)) {
         target = toCheck; 
         return target;        
      }
   }
   return target;
}

void Deck::deleteCard(Card * cardToDelete) {
   for (auto it = theDeck.begin(); it != theDeck.end(); ++it) {
      if ((*it).get() == cardToDelete) {
         it = theDeck.erase(it);
         return;
      }
   }
}

int Deck::getHeadNumber() {
   return headNumber;
}

bool Deck::isEmpty() {
   return theDeck.empty();
}

shared_ptr<Card> & Deck::seeTopCard() {
   return theDeck.front();
}

void Deck::removeTopCard() {
   theDeck.pop_front();
}

int Deck::getSize() {
   return theDeck.size();
}

shared_ptr<Card> Deck::drawCard() {
   shared_ptr<Card> theCard = seeTopCard();
   removeTopCard();
   return theCard;
}

void Deck::emptyDeck() {
   theDeck.clear();
}

void Deck::addDeck(Deck & toAdd) {
   deque<shared_ptr<Card>> newDeck;

   // add all cards from the deck toAdd
   for (auto it = toAdd.theDeck.begin(); it != toAdd.theDeck.end(); ++it) {
      newDeck.push_back(*it);
   }

   // add all cards from the original deck
   for (auto it = theDeck.begin(); it != theDeck.end(); ++it) {
      newDeck.push_back(*it);
   }

   // destroy the original deck
   emptyDeck();

   // and make the new aggregate deck the actual one for the instance
   theDeck = newDeck;
}

void Deck::printDeck() {
   for (auto it = theDeck.begin(); it != theDeck.end(); ++it) {
      cout << (*it)->getName() << endl;
      // note that we dereference it (*it) to get the 
      //    shared_ptr object from the iterator
      // and then we use -> to access Card object itself (i.e
      //    its fields and operations)
   }
}