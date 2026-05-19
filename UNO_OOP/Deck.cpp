#include "Deck.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Deck::Deck() : nextCardIndex(15) {
    initializeTemplate();
}

void Deck::initializeTemplate() {
    // Matches the original deck[8][15] layout exactly
    int templateData[8][15] = {
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
        {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
        {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
        {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1},
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},
        {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1}
    };
    for (int i = 0; i < TEMPLATE_ROWS; i++)
        for (int j = 0; j < TEMPLATE_COLS; j++)
            deckTemplate[i][j] = templateData[i][j];
}

void Deck::populateFromTemplate() {
    char colorChars[4] = {'R', 'G', 'Y', 'B'};
    int index = 0;

    for (int i = 0; i < TEMPLATE_ROWS; i++) {
        for (int j = 0; j < TEMPLATE_COLS; j++) {
            if (deckTemplate[i][j] != -1) {
                char c = (j == 13 || j == 14) ? 'W' : colorChars[i % 4];
                cards[index] = Card(c, deckTemplate[i][j]);
                index++;
            }
        }
    }
}

void Deck::shuffle() {
    srand(static_cast<unsigned>(time(0)));
    populateFromTemplate();

    do {
        for (int i = 0; i < 100; i++) {
            int j = rand() % DECK_SIZE;
            int k = rand() % DECK_SIZE;
            // Swap cards[j] and cards[k]
            Card temp = cards[j];
            cards[j] = cards[k];
            cards[k] = temp;
        }
    } while (cards[TOP_CARD_INDEX].getValue() >= CARD_SKIP);
    // Keep shuffling until the top card is a number card (not special)

    nextCardIndex = 15;
}

Card Deck::drawCard() {
    if (nextCardIndex >= DECK_SIZE) {
        return Card(); // Empty card signals deck exhausted
    }
    Card drawn = cards[nextCardIndex];
    nextCardIndex++;
    return drawn;
}

bool Deck::canDraw() const {
    return nextCardIndex < DECK_SIZE;
}

Card Deck::getTopCard() const {
    return cards[TOP_CARD_INDEX];
}

void Deck::setTopCard(Card card) {
    cards[TOP_CARD_INDEX] = card;
}

void Deck::setTopCardColor(char color) {
    cards[TOP_CARD_INDEX].setColor(color);
}

Card Deck::getCardAt(int index) const {
    if (index >= 0 && index < DECK_SIZE) {
        return cards[index];
    }
    return Card();
}

int Deck::getNextCardIndex() const {
    return nextCardIndex;
}

void Deck::setNextCardIndex(int idx) {
    nextCardIndex = idx;
}

void Deck::repopulateFrom(Card* discardCards, int discardCount) {
    // Shuffle the discard pile
    srand(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < 10000; i++) {
        int j = rand() % discardCount;
        int k = rand() % discardCount;
        Card temp = discardCards[j];
        discardCards[j] = discardCards[k];
        discardCards[k] = temp;
    }

    // Save current top card
    Card topCard = cards[TOP_CARD_INDEX];

    // Copy discard cards into deck
    int count = 0;
    for (int i = 0; i < discardCount; i++) {
        if (!discardCards[i].isEmpty()) {
            cards[count] = discardCards[i];
            count++;
        }
    }

    // Restore top card
    cards[TOP_CARD_INDEX] = topCard;
    nextCardIndex = count;

    cout << "Deck repopulated and shuffled!" << endl;
}

void Deck::showDeck() const {
    for (int i = 0; i < DECK_SIZE; i++) {
        cout << i << ": Color: " << cards[i].getColor()
             << " Number: " << cards[i].getValue() << endl;
    }
}
