#ifndef _CARD_H_
#define _CARD_H_

#include "suits.h"
#include "ranks.h"
#include <string>

class Card {
   Rank cardRank;
   Suit cardSuit;
   
   public:
   // Constructor
   Card(Suit desiredSuit, Rank desiredRank);

   // determines card's suit
   Suit getSuit();

   // determines card's rank
   Rank getRank();

   // sets card's suit
   void setSuit(Suit desiredSuit);

   // sets card's rank
   void setRank(Rank desiredRank);

   // gets card's name
   std::string getName();

   // determines whether card is a joker
   virtual bool isJoker(); // returns 0
};

class Joker : public Card {
   public:
   // Constructor
   Joker();

   // determines whether card is a joker
   bool isJoker() override; // returns 1

   // restricts Joker card to a specific rank 
   //    in course of Hydra game
   void setRank(Rank desiredRank);

   // gets rid of rank that the Joker card was previously restricted to
   void resetToJoker();
};

#endif