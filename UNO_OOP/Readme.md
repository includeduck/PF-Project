# UNO Game (OOP + SDA Refactored)

This project is a two-player console-based implementation of the classic UNO card game in C++. It has been fully refactored from a procedural approach into a robust Object-Oriented architecture using Software Design Architecture (SDA) principles.

## Architecture & Principles
The codebase adheres to solid OOP principles, ensuring high cohesion, low coupling, and clear separation of concerns:
- **Single Responsibility Principle (SRP):** Game components are divided into distinct classes (`Deck`, `Player`, `DiscardPile`, `ConsoleRenderer`, `GameRules`, `FileManager`).
- **Encapsulation:** Class internals are hidden with public interfaces to manipulate game state safely.
- **Modularity:** Core game logic is decoupled from rendering and file I/O operations.

## Features
- Full 108-card standard UNO deck.
- Support for all special cards: Skip, Reverse, Draw Two, Wild, and Wild Draw Four.
- Strict game rule validation (matching colors and numbers).
- Penalty for failing to call "UNO" when reaching 2 cards.
- Full console-based color rendering with Windows API.
- Game result persistence (saving and loading past game results to `GameResults.txt`).

## Class Overview
- `Card`: Represents an individual card (color and value).
- `Deck`: Manages the 108-card deck, shuffling, dealing, and repopulation.
- `Player`: Manages a player's hand.
- `DiscardPile`: Tracks the discard pile for top card visibility and deck repopulation.
- `ConsoleRenderer`: Handles colored rendering and console outputs.
- `GameRules`: Static logic for validating moves and UNO calls.
- `FileManager`: Handles reading and writing to `GameResults.txt`.
- `UnoGame`: The core orchestrator managing the game loop and turns.
- `Menu`: Initial entry point and game selection.

## How to Compile
You can compile this project using any modern C++ compiler. C++17 is recommended but not strictly required:

```bash
g++ -std=c++17 -o UNO_Game main.cpp Card.cpp Deck.cpp Player.cpp DiscardPile.cpp ConsoleRenderer.cpp GameRules.cpp FileManager.cpp UnoGame.cpp Menu.cpp
```

## How to Play
Run the compiled executable `UNO_Game.exe`. You will be presented with a menu to start a new game or exit.
During the game, input the corresponding index of the card in your hand you wish to play, or `0` to draw a card. Make sure to call UNO when prompted if you have exactly 2 cards remaining in your hand before playing one!
