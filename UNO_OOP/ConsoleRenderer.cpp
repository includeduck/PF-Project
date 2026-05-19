#include "ConsoleRenderer.h"
#include <iostream>
#include <iomanip>
using namespace std;

ConsoleRenderer::ConsoleRenderer() {}

void ConsoleRenderer::setColor(int textColor, int bgColor) {
    void* hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

void ConsoleRenderer::resetColor() {
    setColor(CLR_WHITE, CLR_BLACK);
}

void ConsoleRenderer::printColoredText(const string& text, Card card) {
    char c = card.getColor();
    if (c == 'R') setColor(CLR_BLACK, CLR_RED);
    else if (c == 'G') setColor(CLR_BLACK, CLR_GREEN);
    else if (c == 'B') setColor(CLR_WHITE, CLR_BLUE);
    else if (c == 'Y') setColor(CLR_BLACK, CLR_YELLOW);
    else if (c == 'W') setColor(CLR_BLACK, CLR_WHITE);
    cout << text;
    resetColor();
}

void ConsoleRenderer::printBlackText(const string& text, Card card) {
    if (card.isEmpty()) setColor(CLR_WHITE, CLR_BLACK);
    cout << text;
    resetColor();
}

void ConsoleRenderer::printCardRow(Card card, int row) {
    switch (row) {
        case 0:
            printColoredText("-------", card);
            break;
        case 1:
            printColoredText("---", card);
            printColoredText(card.getColorInitial(), card);
            printColoredText("---", card);
            break;
        case 2:
            printColoredText("-------", card);
            break;
        case 3:
            printColoredText("---", card);
            if (card.getValue() == CARD_SKIP) {
                printColoredText("S---", card);
            } else if (card.getValue() == CARD_REVERSE) {
                printColoredText("R---", card);
            } else if (card.getValue() == CARD_DRAW_TWO) {
                printColoredText("DT--", card);
            } else if (card.getValue() == CARD_WILD_DRAW_FOUR) {
                printColoredText("DF--", card);
            } else if (card.getValue() == CARD_WILD) {
                printColoredText("W---", card);
            } else {
                printColoredText(card.getValueDisplay(), card);
                printColoredText("---", card);
            }
            break;
        case 4:
            printColoredText("-------", card);
            break;
    }
}

void ConsoleRenderer::printBlackCardRow(Card card, int row) {
    switch (row) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            printBlackText("-------", card);
            break;
    }
}

void ConsoleRenderer::printPlayerHand(Player& player) {
    int maxHand = Player::getMaxHandSize();
    for (int i = 0; i < maxHand; i += 20) {
        for (int row = 0; row < 6; row++) {
            for (int j = i; j < i + 20 && j < maxHand; j++) {
                Card card = player.getCard(j);
                if (row == 5) {
                    // Print card label
                    if (j < 9) {
                        cout << " Card 0" << j + 1;
                    } else if (j > 99) {
                        cout << " Card" << j + 1;
                    } else {
                        cout << " Card " << j + 1;
                    }
                } else {
                    cout << " ";
                }

                if (!card.isEmpty()) {
                    printCardRow(card, row);
                } else {
                    printBlackCardRow(card, row);
                }
            }
            cout << endl;
        }
    }
}

void ConsoleRenderer::printBoard(Player& playerOne, Player& playerTwo, Card topCard) {
    cout << "Player One's Hand:" << endl;
    printPlayerHand(playerOne);

    cout << endl;
    cout << "Top Card: " << endl;
    for (int row = 0; row < 5; row++) {
        printCardRow(topCard, row);
        cout << endl;
    }
    cout << endl;

    cout << "Player Two's Hand:" << endl;
    printPlayerHand(playerTwo);
}

void ConsoleRenderer::printMenu() {
    cout << "<======================> " << endl;
    cout << "<----Two-Player-UNO----> " << endl;
    cout << "<======================> " << endl;
    cout << endl;
    cout << "1. Play" << endl;
    cout << "2. Exit UNO" << endl;
    cout << "Enter choice: ";
}

void ConsoleRenderer::printWinner(Player& winner, int moveCount) {
    cout << winner.getName() << " wins! The game had a total of "
         << moveCount << " moves!" << endl;
}

void ConsoleRenderer::clearScreen() {
    system("cls");
}
