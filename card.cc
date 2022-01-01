#include "card.h"

using namespace std;

Card::Card(Suit desiredSuit, Rank desiredRank): 
cardRank{desiredRank}, cardSuit{desiredSuit} {}

void Card::setRank(Rank desiredRank) {
   cardRank = desiredRank;
}

std::string rankToStr(Rank rank) {
   if (rank == Rank::Ace) {
      return "A";
   } else if (rank == Rank::Two) {
      return "2";
   } else if (rank == Rank::Three) {
      return "3";
   } else if (rank == Rank::Four) {
      return "4";
   } else if (rank == Rank::Five) {
      return "5";
   } else if (rank == Rank::Six) {
      return "6";
   } else if (rank == Rank::Seven) {
      return "7";
   } else if (rank == Rank::Eight) {
      return "8";
   } else if (rank == Rank::Nine) {
      return "9";
   } else if (rank == Rank::Ten) {
      return "10";
   } else if (rank == Rank::Jack) {
      return "J";
   } else if (rank == Rank::Queen) {
      return "Q";
   } else if (rank == Rank::King) {
      return "K";
   } else if (rank == Rank::unsetJoker) {
      return "UJ";
   } else {
      return "FAIL";
   }
}

std::string suitToStr(Suit suit) {
   if (suit == Suit::D) {
      return "D";
   } else if (suit == Suit::C) {
      return "C";
   } else if (suit == Suit::H) {
      return "H";
   } else if (suit == Suit::S) {
      return "S";
   } else if (suit == Suit::J) {
      return "J";
   } else {
      return "FAIL";
   }
}

std::string Card::getName() {
   bool joker = this->isJoker();
   if (!joker || cardRank != Rank::unsetJoker) {
      string rankString = rankToStr(cardRank);
      string suitString = suitToStr(cardSuit);
      string total = rankString + suitString;
      return total;
   } else { // if (joker && cardRank == Rank::unsetJoker) 
      return "Joker";
   }
}

Suit Card::getSuit() {
   return cardSuit;
}

Rank Card::getRank() {
   return cardRank;
}

bool Card::isJoker() {
   return 0;
}

bool Joker::isJoker() {
   return 1;
}

void Joker::setRank(Rank desiredRank) {
   Card::setRank(desiredRank);
}

void Joker::resetToJoker() {
   Card::setRank(Rank::unsetJoker);
}

Joker::Joker(): Card(Suit::J, Rank::unsetJoker) {}

