#ifndef DISCARD_PILE_H
#define DISCARD_PILE_H

#include "Card.h"

class DiscardPile {
private:
    static const int MAX_SIZE = 105;
    Card cards[MAX_SIZE];
    int topIndex;

public:
    DiscardPile();

    void addCard(Card card);
    Card getCard(int index) const;
    Card* getCards();  // For repopulating the deck
    int getTopIndex() const;
    void reset();
};

#endif


