#include "player.h"

using namespace std;

Player::Player(): drawPile{Deck{false}}, discardPile{Deck{false}} {}

bool Player::drawPileEmpty() {
   return drawPile.isEmpty();
}

bool Player::discardPileEmpty() {
   return discardPile.isEmpty();
}

void Player::swapReserveWithHand() {
   if (reservePresent()) {
      swap(reserve,cardInHand);
   } else {
      reserve = cardInHand;
      cardInHand.reset();
   }
}

bool Player::inWinningCondition() {
   return (drawPile.isEmpty() && discardPile.isEmpty() && !reserve && !cardInHand);
}

bool Player::reservePresent() {
   if (reserve) {
      return 1;
   } else {
      return 0;
   }
}

void Player::forceWin() {
   drawPile.emptyDeck();
   discardPile.emptyDeck();
   cardInHand.reset();
   reserve.reset();
}

void Player::addHandToDiscard() {
   discardPile.addCardToTop(cardInHand);
   cardInHand.reset();
}

void Player::addReserveToDiscard() {
   if (reserve) {
      discardPile.addCardToTop(reserve);
      reserve.reset();
   }
}

void Player::addDiscardToDraw() {
   drawPile.addDeck(discardPile);
   discardPile.emptyDeck();
   drawPile.shuffle();
}

void Player::returnReserve() {
   if (reserve) {
      addToTopOfDrawPile(reserve);
      reserve.reset();
   }
}

bool Player::hasCardInHand() {
   if (cardInHand) {
      return 1;
   } else {
      return 0;
   }
}

int Player::discardPileSize() {
   return discardPile.getSize();
}

int Player::drawPileSize() {
   return drawPile.getSize();
}

Deck & Player::getDrawPile() {
   return drawPile;
}

Deck & Player::getDiscardPile() {
   return discardPile;
}

shared_ptr<Card> & Player::viewCardInHand() {
   return cardInHand;
}

shared_ptr<Card> Player::playHand() {
   shared_ptr<Card> temp = cardInHand;
   cardInHand.reset();
   return temp;
}

void Player::clearDiscardPile() {
   discardPile.emptyDeck();
}

void Player::clearDrawPile() {
   drawPile.emptyDeck();
}

shared_ptr<Card> Player::withdrawFromDrawPile() {
   return drawPile.drawCard();
}

shared_ptr<Card> Player::withdrawFromDiscardPile() {
   return discardPile.drawCard();
}

void Player::drawFromDrawPile() {
   if (cardInHand) {
      cout << "You already have a card in hand!" << endl;
   } else {
      cardInHand = drawPile.drawCard();
   }
}

void Player::drawFromDiscardPile() {
   if (cardInHand) {
      cout << "You already have a card in hand!" << endl;
   } else {
      cardInHand = discardPile.drawCard();
   }
}

void Player::addToTopOfDiscardPile(shared_ptr<Card> cardToAdd) {
   discardPile.addCardToTop(cardToAdd);
}

void Player::addToBottomOfDiscardPile(shared_ptr<Card> cardToAdd) {
   discardPile.addCardToBottom(cardToAdd);
}

void Player::addToDiscardPile(Deck deckToAdd) {
   discardPile.addDeck(deckToAdd);
   discardPile.shuffle();
}

void Player::addHeadToDiscard(std::unique_ptr<Deck> & theHead) {
   Deck * theDeck = theHead.get();
   int deckSize = theDeck->getSize();
   for (int i = 0; i < deckSize; ++i) {
      shared_ptr<Card> newCard = theDeck->drawCard();
      discardPile.addCardToBottom(newCard);
   }
}

void Player::addToTopOfDrawPile(shared_ptr<Card> cardToAdd) {
   drawPile.addCardToTop(cardToAdd);
}

void Player::addToBottomOfDrawPile(shared_ptr<Card> cardToAdd) {
   drawPile.addCardToBottom(cardToAdd);
}

void Player::addToDrawPile(Deck deckToAdd) {
   drawPile.addDeck(deckToAdd);
   drawPile.shuffle();
}