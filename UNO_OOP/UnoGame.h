#ifndef UNO_GAME_H
#define UNO_GAME_H

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "DiscardPile.h"
#include "ConsoleRenderer.h"
#include "GameRules.h"
#include "FileManager.h"

class UnoGame {
private:
    Deck deck;
    Player players[2];          // players[0] = Player One, players[1] = Player Two
    DiscardPile discardPile;
    ConsoleRenderer renderer;
    FileManager fileManager;

    int currentTurn;            // 1 or 2 (matches original turn variable)
    int moveCount;
    int discardPileIndex;

    // Core game operations
    void dealCards();
    void playTurn();
    void shiftTurn();

    // Card operations
    void drawCardForCurrentPlayer();
    void updateDiscardPile(int playerIndex, int cardIndex);
    void handleSpecialCard(int specialCardType);

    // Helper to get player reference by turn number
    Player& getCurrentPlayer();
    Player& getOpponentPlayer();

public:
    UnoGame();

    // Start and run the game
    void start();
};

#endif
