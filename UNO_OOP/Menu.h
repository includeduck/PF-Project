#ifndef MENU_H
#define MENU_H

#include "ConsoleRenderer.h"
#include "UnoGame.h"

class Menu {
private:
    ConsoleRenderer renderer;

public:
    Menu();

    // Display the main menu and handle user choice
    void show();
};

#endif
