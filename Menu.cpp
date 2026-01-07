#include "Menu.h"
#include "ConsoleUtils.h"
#include <iostream>
using namespace std;

int Menu::showMainMenu() {
    ConsoleUtils::clearScreen();

    // Header
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 14); // Yellow
    cout << "=========================================\n";
    cout << "          CHESS GAME - MAIN MENU\n";
    cout << "=========================================\n\n";

    SetConsoleTextAttribute(hConsole, 11); // Cyan
    cout << "            SELECT AN OPTION\n";
    cout << "            -----------------\n\n";

    SetConsoleTextAttribute(hConsole, 7); // White
    cout << "    1. New Game\n";
    cout << "    2. How to Play\n";
    cout << "    3. Load Saved Game\n";
    cout << "    4. Exit\n\n";

    cout << "    Enter your choice (1-4): ";

    int choice;
    cin >> choice;

    // Clear input buffer
    cin.ignore(1000, '\n');

    return choice;
}