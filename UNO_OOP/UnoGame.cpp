#include "UnoGame.h"
#include <iostream>
#include <string>
using namespace std;

UnoGame::UnoGame()
    : currentTurn(1), moveCount(0), discardPileIndex(0) {
    players[0] = Player("Player One", 1);
    players[1] = Player("Player Two", 2);
}

Player& UnoGame::getCurrentPlayer() {
    return players[currentTurn - 1];
}

Player& UnoGame::getOpponentPlayer() {
    return players[(currentTurn == 1) ? 1 : 0];
}

void UnoGame::shiftTurn() {
    if (currentTurn == 1)
        currentTurn = 2;
    else
        currentTurn = 1;
}

void UnoGame::dealCards() {
    // Deal 7 cards to each player (indices 0-6 for P1, 7-13 for P2)
    for (int i = 0; i < 7; i++) {
        players[0].addCard(deck.getCardAt(i));
    }
    for (int i = 0; i < 7; i++) {
        players[1].addCard(deck.getCardAt(7 + i));
    }
    // Index 14 is the initial face-up top card (handled by Deck)
}

void UnoGame::drawCardForCurrentPlayer() {
    // Count total cards in play to prevent exceeding 108
    int totalCards = players[0].getCardCount() + players[1].getCardCount() + 1;
    if (totalCards >= 108) {
        cout << "Cannot Draw more Cards as the card count is 108 Currently. " << endl;
        return;
    }

    if (!deck.canDraw()) {
        cout << "The deck is out of cards!" << endl;
        deck.repopulateFrom(discardPile.getCards(), discardPileIndex);
        return;
    }

    Player& current = getCurrentPlayer();
    if (current.isHandFull()) {
        cout << current.getName() << "'s hand is full." << endl;
        shiftTurn();
    } else {
        Card drawn = deck.drawCard();
        current.addCard(drawn);
        cout << current.getName() << " drew a card." << endl;
    }
}

void UnoGame::updateDiscardPile(int playerIndex, int cardIndex) {
    Card played = players[playerIndex].getCard(cardIndex);
    discardPile.addCard(played);
    deck.setTopCard(played);
}

void UnoGame::handleSpecialCard(int specialCardType) {
    if (specialCardType == CARD_SKIP) {
        // Skip
        cout << "Special card: Skip! The opponent loses their turn!" << endl;
        shiftTurn();
    }
    else if (specialCardType == CARD_REVERSE) {
        // Reverse (same as skip in 2-player)
        cout << "Special card: Reverse! The opponent loses their turn!" << endl;
        shiftTurn();
    }
    else if (specialCardType == CARD_DRAW_TWO) {
        // Draw Two
        cout << "Special card: Draw Two! The opponent draws two cards!" << endl;
        shiftTurn();
        drawCardForCurrentPlayer();
        drawCardForCurrentPlayer();
    }
    else if (specialCardType == CARD_WILD) {
        // Wild
        char chosenColor;
        do {
            cout << "Special card: Wild! Choose a new color (R, G, B, Y): ";
            cin >> chosenColor;
            if (chosenColor != 'R' && chosenColor != 'G' && chosenColor != 'B' && chosenColor != 'Y') {
                cout << "Invalid. Chosen Color can only be either Red, Green, Blue, or Yellow!" << endl;
            }
        } while (chosenColor != 'R' && chosenColor != 'G' && chosenColor != 'B' && chosenColor != 'Y');
        deck.setTopCardColor(chosenColor);
        cout << "The new color is: " << deck.getTopCard().getColor() << endl;
    }
    else if (specialCardType == CARD_WILD_DRAW_FOUR) {
        // Wild Draw Four
        char chosenColor;
        do {
            cout << "Special card: Wild Draw Four! Choose a new color (R, G, B, Y): ";
            cin >> chosenColor;
            if (chosenColor != 'R' && chosenColor != 'G' && chosenColor != 'B' && chosenColor != 'Y') {
                cout << "Invalid. Chosen Color can only be either Red, Green, Blue, or Yellow!" << endl;
            }
        } while (chosenColor != 'R' && chosenColor != 'G' && chosenColor != 'B' && chosenColor != 'Y');
        deck.setTopCardColor(chosenColor);
        cout << "The new color is: " << deck.getTopCard().getColor() << endl;
        cout << "The opponent draws four cards." << endl;
        shiftTurn();
        for (int i = 0; i < 4; i++) {
            drawCardForCurrentPlayer();
        }
    }
}

void UnoGame::playTurn() {
    int playerCard;
    bool turnShifted = false;
    bool drawed = false;
    string exitchar;

    Card topCard = deck.getTopCard();
    int topCardNumber = topCard.getValue();
    char topCardColor = topCard.getColor();

    Player& current = getCurrentPlayer();
    int playerIndex = currentTurn - 1;

    // Ask to exit
    do {
        cout << "Enter E to exit or any other key to continue: ";
        cin >> exitchar;
        if (exitchar == "E" || exitchar == "e") {
            cout << "Exiting...";
            exit(0);
        }

        cout << current.getName() << ", enter your move or enter 0 to draw a card: ";

        // Check UNO call
        bool unocall = GameRules::checkUnoCall(current);
        if (!unocall) {
            cout << "\nUno penalty invoked!" << endl;
            drawCardForCurrentPlayer();
            drawCardForCurrentPlayer();
            shiftTurn();
        }

        cin >> playerCard;
        if (playerCard < 0 || playerCard > 108) {
            cout << "Invalid input. Enter a number or 0 to draw a card." << endl;
        }
    } while (playerCard < 0 || playerCard > 106);

    // Process the move
    while (true) {
        if (playerCard == 0) {
            // Player chooses to draw a card
            drawCardForCurrentPlayer();

            // Check if player can now play (prevents special card side effects)
            bool canPlay = false;
            for (int i = 0; i < Player::getMaxHandSize(); i++) {
                Card c = current.getCard(i);
                if (!c.isEmpty()) {
                    bool numberMatch = (c.getValue() == topCardNumber);
                    if (topCardNumber == CARD_WILD_DRAW_FOUR || topCardNumber == CARD_WILD) {
                        numberMatch = true;
                    }
                    if (numberMatch || c.getColor() == topCardColor) {
                        canPlay = true;
                        break;
                    }
                }
            }

            if (!canPlay) {
                shiftTurn();
                turnShifted = true;
            }
            drawed = true;
            break;
        }

        // Validate card selection
        if (playerCard < 1 || playerCard > 106 || current.getCard(playerCard - 1).isEmpty()) {
            cout << "Invalid card selection! Try again or enter 0 to draw a card: ";
            cin >> playerCard;
            continue;
        }

        // Check if play is valid
        Card selectedCard = current.getCard(playerCard - 1);
        bool valid = GameRules::isValidPlay(selectedCard, topCard);

        if (valid) {
            int specialCardType = selectedCard.getValue();

            // Update discard pile with the played card
            updateDiscardPile(playerIndex, playerCard - 1);

            // Remove card from hand
            current.removeCard(playerCard - 1);

            // Handle special cards
            if (specialCardType >= CARD_SKIP && specialCardType <= CARD_WILD) {
                handleSpecialCard(specialCardType);
            }
            break;
        } else {
            cout << "Invalid card! Try again or enter 0 to draw a card: ";
            cin >> playerCard;
        }
    }

    if (!turnShifted) { shiftTurn(); }
    if (!drawed) { discardPileIndex++; }
    moveCount++;
}

void UnoGame::start() {
    // Load and display previous game results
    fileManager.loadAndDisplayResult();
    cout << endl;

    // Initialize and shuffle deck, deal cards
    deck.shuffle();
    dealCards();

    // Main game loop — runs while both players have cards
    while (players[0].hasCards() && players[1].hasCards()) {
        renderer.printBoard(players[0], players[1], deck.getTopCard());
        cout << endl;
        playTurn();
        system("pause");
        renderer.clearScreen();
    }

    // Determine and announce winner
    if (!players[0].hasCards()) {
        renderer.printWinner(players[0], moveCount);
        string result = "Player One Wins! The game had a total of " + to_string(moveCount) + " moves!";
        fileManager.saveResult(result);
    } else if (!players[1].hasCards()) {
        renderer.printWinner(players[1], moveCount);
        string result = "Player Two Wins! The game had a total of " + to_string(moveCount) + " moves!";
        fileManager.saveResult(result);
    }
}
