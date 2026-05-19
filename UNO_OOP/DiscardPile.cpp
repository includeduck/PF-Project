using namespace std;
#include "DiscardPile.h"

DiscardPile::DiscardPile() : topIndex(0) {
    for (int i = 0; i < MAX_SIZE; i++) {
        cards[i] = Card();
    }
}

void DiscardPile::addCard(Card card) {
    if (topIndex < MAX_SIZE) {
        cards[topIndex] = card;
        topIndex++;
    }
}

Card DiscardPile::getCard(int index) const {
    if (index >= 0 && index < MAX_SIZE) {
        return cards[index];
    }
    return Card();
}

Card* DiscardPile::getCards() {
    return cards;
}

int DiscardPile::getTopIndex() const {
    return topIndex;
}

void DiscardPile::reset() {
    for (int i = 0; i < MAX_SIZE; i++) {
        cards[i] = Card();
    }
    topIndex = 0;
}

