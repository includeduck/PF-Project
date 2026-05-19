#include "Card.h"

Card::Card() : color('\0'), value(0) {}

Card::Card(char color, int value) : color(color), value(value) {}

char Card::getColor() const { return color; }
int Card::getValue() const { return value; }

void Card::setColor(char c) { color = c; }
void Card::setValue(int v) { value = v; }

bool Card::isEmpty() const { return color == '\0'; }

bool Card::isSpecial() const { return value >= CARD_SKIP && value <= CARD_WILD; }

bool Card::isWild() const { return color == 'W'; }

void Card::clear() {
    color = '\0';
    value = 0;
}

string Card::getColorInitial() const {
    switch (color) {
        case 'R': return "R";
        case 'G': return "G";
        case 'B': return "B";
        case 'Y': return "Y";
        case 'W': return "W";
        default: return "";
    }
}

string Card::getValueDisplay() const {
    if (value >= 0 && value <= 9) return to_string(value);
    return "";
}
