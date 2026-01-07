#include "ConsoleUtils.h"
#include "Settings.h"
#include "Menu.h"
#include "Game.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
    // Set console window size FIRST
    system("mode con: cols=100 lines=40");
    system("title Chess Game");

    // Initialize console utilities
    ConsoleUtils::init();
    ConsoleUtils::enableMouseInput();
    Settings::setDefaults();

    // Hide cursor
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(console, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(console, &cursorInfo);

    // Main game loop
    bool running = true;

    while (running) {
        // Show main menu
        int choice = Menu::showMainMenu();

        switch (choice) {
        case 1: { // New Game
            Game game;
            game.start();  // Now this should work
            break;
        }

        case 2: { // How to Play
            Settings::showSettingsMenu();
            break;
        }

        case 3: { // Load Game
            Game game;
            if (game.loadSavedGame()) {
                game.start();
            }
            else {
                cout << "\n    No saved game found!\n";
                cout << "    Press any key to continue...";
                cin.ignore();
                cin.get();
            }
            break;
        }

        case 4: { // Exit
            running = false;
            break;
        }

        default:
            cout << "\n    Invalid choice! Press any key...";
            cin.ignore();
            cin.get();
            break;
        }
    }

    // Exit message
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10); // Green

    cout << "\n\n\n";
    cout << "    =======================================\n";
    cout << "            THANKS FOR PLAYING!\n";
    cout << "    =======================================\n\n";

    SetConsoleTextAttribute(hConsole, 7); // White
    cout << "    Press any key to exit...";

    cin.ignore();
    cin.get();

    return 0;
}