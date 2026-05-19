#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;

// Card value constants matching original encoding
const int CARD_SKIP = 10;
const int CARD_REVERSE = 11;
const int CARD_DRAW_TWO = 12;
const int CARD_WILD_DRAW_FOUR = 13;
const int CARD_WILD = 14;

class Card {
private:
    char color;   // 'R', 'G', 'B', 'Y', 'W', or '\0' for empty
    int value;    // 0-9 for numbers, 10-14 for special cards

public:
    Card();
    Card(char color, int value);

    // Getters
    char getColor() const;
    int getValue() const;

    // Setters
    void setColor(char c);
    void setValue(int v);

    // State queries
    bool isEmpty() const;
    bool isSpecial() const;
    bool isWild() const;
    void clear();

    // Display helpers
    string getColorInitial() const;
    string getValueDisplay() const;
};

#endif
