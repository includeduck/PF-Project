#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include <string>

class Player {
private:
    static const int MAX_HAND_SIZE = 106;
    Card hand[MAX_HAND_SIZE];
    std::string name;
    int playerNumber; // 1 or 2

public:
    Player();
    Player(const std::string& name, int number);

    // Hand management
    void addCard(Card card);
    Card getCard(int index) const;
    void removeCard(int index);
    int getCardCount() const;
    bool hasCards() const;         // first card is not empty
    bool isHandFull() const;

    // Getters
    std::string getName() const;
    int getPlayerNumber() const;

    // Game logic helper
    bool hasPlayableCard(int topValue, char topColor) const;

    static int getMaxHandSize() { return MAX_HAND_SIZE; }
};

#endif


