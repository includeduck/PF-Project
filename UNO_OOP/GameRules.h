#ifndef GAME_RULES_H
#define GAME_RULES_H

#include "Card.h"
#include "Player.h"
#include <string>

class GameRules {
public:
    // Validates whether a card can be played on top of the current top card
    static bool isValidPlay(Card playerCard, Card topCard);

    // Checks if the player must call UNO (2 cards left)
    // Returns true if no penalty, false if penalty should be applied
    static bool checkUnoCall(Player& player);
};

#endif


