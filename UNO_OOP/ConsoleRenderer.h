#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

#include "Card.h"
#include "Player.h"
#include <string>
#include <Windows.h>
using namespace std;

class ConsoleRenderer {
private:
    // Console color constants
    static const int CLR_BLACK = 0;
    static const int CLR_BLUE = 1;
    static const int CLR_GREEN = 2;
    static const int CLR_CYAN = 3;
    static const int CLR_RED = 4;
    static const int CLR_MAGENTA = 5;
    static const int CLR_YELLOW = 6;
    static const int CLR_WHITE = 7;

    void setColor(int textColor, int bgColor);
    void resetColor();
    void printColoredText(const string& text, Card card);
    void printBlackText(const string& text, Card card);
    void printCardRow(Card card, int row);
    void printBlackCardRow(Card card, int row);

public:
    ConsoleRenderer();

    // Board rendering
    void printBoard(Player& playerOne, Player& playerTwo, Card topCard);
    void printPlayerHand(Player& player);

    // UI elements
    void printMenu();
    void printWinner(Player& winner, int moveCount);
    void clearScreen();
};

#endif
