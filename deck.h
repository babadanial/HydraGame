#ifndef _DECK_H_
#define _DECK_H_
#include <vector>
#include <deque>
#include <iostream>
#include "card.h"
#include <algorithm>
#include <memory>
#include <random>
#include <chrono>

class Deck {
   // the Deck container itself
   std::deque<std::shared_ptr<Card>> theDeck;
   int headNumber;

   // returns and removes the first Card from the Deck
   // return value may be ignored if seeTopCard is called
   //    beforehand
   void removeTopCard();

   public:
   // Constructor for full or empty deck for cards
   Deck(bool fullDeckWanted, int headNum = -1);

   // resets all jokers to the "unset joker" rank
   void resetAllJokers();

   // returns the top Card from the Deck
   std::shared_ptr<Card> & seeTopCard();

   // pseudo-randomly shuffles the deck 
   void shuffle();
   
   // adds a Card to bottom of the Deck
   void addCardToBottom(std::shared_ptr<Card> cardToAdd);

   // adds a Card to top of the Deck
   void addCardToTop(std::shared_ptr<Card> cardToAdd);

   // adds a Deck's cards to the current Deck
   void addDeck(Deck & toAdd);

   // empties and destroys the deck of Cards (but not the Deck object itself)
   void emptyDeck();

   // tells if the Deck is empty
   bool isEmpty();

   // returns the size of the Deck (number of cards contained)
   int getSize();

   // returns the head number
   int getHeadNumber();

   // returns the first Card with the desired suit and rank
   // FOR TESTING ONLY
   std::shared_ptr<Card> findCard(Suit desiredSuit, Rank desiredRank);

   // compares Card * against address stored in every shared_ptr and deletes the shared_ptr if it matches 
   // FOR TESTING ONLY
   void deleteCard(Card * cardToDelete);

   // prints the names of the Cards in the deck in order - for testing only
   void printDeck();

   // removes the first Card in the deck and returns it
   std::shared_ptr<Card> drawCard();
};

#endif