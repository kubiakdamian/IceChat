#include "Menu.h"

namespace ClientApp {
    void Menu::printMenu() {
        cout << endl;
        cout << "1. Create room" << endl;
        cout << "2. Print rooms" << endl;
        cout << "3. Join room" << endl;
        cout << "4. Leave room" << endl;
        cout << "5. Send message" << endl;
        cout << "6. Print room's members" << endl;
        cout << "7. Send private message" << endl;
        cout << "8. Change username" << endl;
        cout << "0. Exit" << endl;
        cout << endl;
    }

    void Menu::getInput() {
        cin >> choice; 
        while (choice < 0 || choice > 8) {
            cout << "Enter number from 0 to 8." << endl;
            cin >> choice;
        }
    }

    int Menu::getChoice() {
        getInput();
        return choice;
    }
}