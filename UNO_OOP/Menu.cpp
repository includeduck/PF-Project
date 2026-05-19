#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu() {}

void Menu::show() {
    char choice;
    do {
        renderer.clearScreen();
        renderer.printMenu();

        cin >> choice;

        if (choice != '1' && choice != '2') {
            continue;
        }

        switch (choice) {
        case '1': {
            renderer.clearScreen();
            UnoGame game;
            game.start();
            break;
        }
        case '2':
            cout << "Exiting UNO..." << endl;
            return;
        default:
            cout << "Invalid choice!" << endl;
            break;
        }
        system("pause");
    } while (choice != '2');
}
