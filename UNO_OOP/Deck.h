#ifndef DECK_H
#define DECK_H

#include "Card.h"

class Deck {
private:
    static const int DECK_SIZE = 108;
    static const int TEMPLATE_ROWS = 8;
    static const int TEMPLATE_COLS = 15;
    static const int TOP_CARD_INDEX = 14;

    Card cards[DECK_SIZE];
    int deckTemplate[TEMPLATE_ROWS][TEMPLATE_COLS];
    int nextCardIndex;

    void initializeTemplate();
    void populateFromTemplate();

public:
    Deck();

    // Core operations
    void shuffle();
    Card drawCard();
    bool canDraw() const;

    // Top card (index 14) management
    Card getTopCard() const;
    void setTopCard(Card card);
    void setTopCardColor(char color);

    // For initial deal
    Card getCardAt(int index) const;

    // Drawing index management
    int getNextCardIndex() const;
    void setNextCardIndex(int idx);

    // Repopulate from discard pile
    void repopulateFrom(Card* discardCards, int discardCount);

    // Debug
    void showDeck() const;

    static int getDeckSize() { return DECK_SIZE; }
};

#endif
