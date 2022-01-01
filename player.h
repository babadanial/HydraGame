#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "deck.h"

class Player {
   Deck drawPile;
   Deck discardPile;
   std::shared_ptr<Card> reserve;
   std::shared_ptr<Card> cardInHand;

   public:
   // default constructor
   Player();

   // checks if the player's draw pile is empty
   bool drawPileEmpty();

   // returns the reserve card to top of draw pile
   void returnReserve();

   // checks if the player's discard pile is empty
   bool discardPileEmpty();

   // swaps the card in reserve with the cardInHand
   void swapReserveWithHand();

   // determines whether the player is in a condition to
   //    win the game (by all of their piles being empty)
   bool inWinningCondition();

   // adds the discard pile to the draw pile, then shuffles
   //    draw pile
   void addDiscardToDraw();

   // adds an individual card to top of the discard pile
   void addToTopOfDiscardPile(std::shared_ptr<Card> cardToAdd);

   // adds an individual card to bottom of the discard pile
   void addToBottomOfDiscardPile(std::shared_ptr<Card> cardToAdd);

   // adds a deck of cards to the discard pile, and shuffles it
   void addToDiscardPile(Deck deckToAdd);

   // adds an individual card to top of the draw pile
   void addToTopOfDrawPile(std::shared_ptr<Card> cardToAdd);

   // adds an individual card to bottom of the draw pile
   void addToBottomOfDrawPile(std::shared_ptr<Card> cardToAdd);

   // adds a deck of cards to the draw pile, and shuffles it
   void addToDrawPile(Deck deckToAdd); 

   // withdraws a card from the draw pile
   std::shared_ptr<Card> withdrawFromDrawPile();

   // withdraws a card from the discard pile
   std::shared_ptr<Card> withdrawFromDiscardPile();

   // gives a reference to the draw pile so it can be copied/removed
   Deck & getDrawPile();
   
   // gives a reference to the discard pile so it can be copied/removed
   Deck & getDiscardPile();

   // adds the card in hand to top of the discard pile
   void addHandToDiscard();

   // adds an entire Head to the discard pile
   void addHeadToDiscard(std::unique_ptr<Deck> & theHead);

   // adds the reserve, if it exists, to the top of the discard pile
   void addReserveToDiscard();

   // destroys the draw pile (presumably cards have already been removed from it as part of game and placed somewhere else)
   void clearDrawPile();

   // destroys the discard pile (presumably cards have already been removed from it as part of game and placed somewhere else)
   void clearDiscardPile();

   // draws into the Player's hand from draw pile
   void drawFromDrawPile();

   // draws into Player's hand from discard pile
   void drawFromDiscardPile();

   // returns size of discard pile
   int discardPileSize();

   // returns size of draw pile
   int drawPileSize();

   // determines whether a card is in reserve
   bool reservePresent();

   // determines the player has a card in hand
   bool hasCardInHand();

   // returns a reference to the card in hand
   std::shared_ptr<Card> & viewCardInHand();

   // forces the player into a winning condition
   void forceWin();

   // removes the card from the hand so that it may be placed into a head
   std::shared_ptr<Card> playHand();
};

#endif