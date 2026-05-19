#include "Player.h"
#include <iostream>
using namespace std;

Player::Player() : name(""), playerNumber(0) {
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        hand[i] = Card();
    }
}

Player::Player(const string& name, int number) : name(name), playerNumber(number) {
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        hand[i] = Card();
    }
}

void Player::addCard(Card card) {
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (hand[i].isEmpty()) {
            hand[i] = card;
            return;
        }
    }
    cout << getName() << "'s hand is full." << endl;
}

Card Player::getCard(int index) const {
    if (index >= 0 && index < MAX_HAND_SIZE) {
        return hand[index];
    }
    return Card();
}

void Player::removeCard(int index) {
    // Shift all cards after the removed one to fill the gap (matches original behavior)
    for (int i = index; i < MAX_HAND_SIZE - 1; i++) {
        hand[i] = hand[i + 1];
    }
    hand[MAX_HAND_SIZE - 1].clear();
}

int Player::getCardCount() const {
    int count = 0;
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (!hand[i].isEmpty()) {
            count++;
        }
    }
    return count;
}

bool Player::hasCards() const {
    return !hand[0].isEmpty();
}

bool Player::isHandFull() const {
    return getCardCount() >= MAX_HAND_SIZE;
}

string Player::getName() const { return name; }
int Player::getPlayerNumber() const { return playerNumber; }

bool Player::hasPlayableCard(int topValue, char topColor) const {
    for (int i = 0; i < MAX_HAND_SIZE; i++) {
        if (!hand[i].isEmpty()) {
            bool numberMatch = (hand[i].getValue() == topValue);
            // Also match if top card is wild (13 or 14)
            if (topValue == CARD_WILD_DRAW_FOUR || topValue == CARD_WILD) {
                numberMatch = true;
            }
            bool colorMatch = (hand[i].getColor() == topColor);
            if (numberMatch || colorMatch) {
                return true;
            }
        }
    }
    return false;
}
