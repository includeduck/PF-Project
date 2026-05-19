#include "GameRules.h"
#include <iostream>
using namespace std;

bool GameRules::isValidPlay(Card playerCard, Card topCard) {
    // Wild cards are always valid
    if (playerCard.isWild()) {
        return true;
    }

    // Check number/value match
    bool valid = (playerCard.getValue() == topCard.getValue());

    // If top card is wild (13 or 14), any card is valid
    if (topCard.getValue() == CARD_WILD_DRAW_FOUR || topCard.getValue() == CARD_WILD) {
        valid = true;
    }

    // Check color match
    if (playerCard.getColor() == topCard.getColor()) {
        valid = true;
    }

    return valid;
}

bool GameRules::checkUnoCall(Player& player) {
    if (player.getCardCount() == 2) {
        string calluno;
        cout << endl;
        cout << "Two cards left for " << player.getName() << ": ";
        cin >> calluno;

        // Case-insensitive check for "UNO" (matches all 8 combinations from original)
        if (calluno == "UNO" || calluno == "UNo" || calluno == "UnO" || calluno == "Uno" ||
            calluno == "uNO" || calluno == "uNo" || calluno == "unO" || calluno == "uno") {
            return true;
        }
        return false; // Penalty: didn't call UNO
    }
    return true; // No need to call UNO (not at 2 cards)
}
