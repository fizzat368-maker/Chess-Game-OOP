#include "Settings.h"
#include "ConsoleUtils.h"
#include <iostream>
#include <windows.h>
using namespace std;

int Settings::boardSize = 2;
int Settings::lightSquare = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
int Settings::darkSquare = BACKGROUND_BLUE | BACKGROUND_GREEN;
int Settings::highlightColor = BACKGROUND_GREEN | BACKGROUND_INTENSITY;

void Settings::setDefaults() {
    boardSize = 2;
    lightSquare = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE; // White
    darkSquare = BACKGROUND_BLUE | BACKGROUND_GREEN;                    // Cyan
    highlightColor = BACKGROUND_GREEN | BACKGROUND_INTENSITY;           // Bright Green
}

void Settings::showSettingsMenu() {
    bool running = true;

    while (running) {
        ConsoleUtils::clearScreen();

        // Header
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 14); // Yellow
        cout << "=========================================\n";
        cout << "           GAME INSTRUCTIONS\n";
        cout << "=========================================\n\n";

        SetConsoleTextAttribute(hConsole, 11); // Cyan
        cout << "           HOW TO PLAY CHESS\n";
        cout << "           =================\n\n";

        SetConsoleTextAttribute(hConsole, 7); // White

        // Game Rules
        cout << "1. GAME OVERVIEW\n";
        cout << "   -------------\n";
        cout << "   - Chess is a two-player strategy game\n";
        cout << "   - White moves first, then players alternate\n";
        cout << "   - Objective: Checkmate opponent's king\n";
        cout << "   - Each player has 16 pieces\n\n";

        // Piece Movements
        cout << "2. PIECE MOVEMENTS\n";
        cout << "   ---------------\n";
        cout << "   Pawn (P/p):\n";
        cout << "   - Moves forward one square\n";
        cout << "   - Captures diagonally\n";
        cout << "   - First move: can move two squares\n\n";

        cout << "   Rook (R/r):\n";
        cout << "   - Moves horizontally or vertically\n";
        cout << "   - Any number of squares\n\n";

        cout << "   Knight (N/n):\n";
        cout << "   - Moves in L-shape (2 squares one way, 1 square other way)\n";
        cout << "   - Can jump over other pieces\n\n";

        cout << "   Bishop (B/b):\n";
        cout << "   - Moves diagonally\n";
        cout << "   - Any number of squares\n\n";

        cout << "   Queen (Q/q):\n";
        cout << "   - Moves any direction\n";
        cout << "   - Any number of squares (most powerful piece)\n\n";

        cout << "   King (K/k):\n";
        cout << "   - Moves one square in any direction\n";
        cout << "   - Must be protected at all times\n\n";

        // Game Rules
        cout << "3. SPECIAL RULES\n";
        cout << "   -------------\n";
        cout << "   - Check: King is under attack\n";
        cout << "   - Checkmate: King is attacked and cannot escape\n";
        cout << "   - Stalemate: No legal moves but king not in check\n";
        cout << "   - Castling: King and rook move together\n";
        cout << "   - En passant: Special pawn capture\n";
        cout << "   - Promotion: Pawn reaches opposite side becomes Queen\n\n";

        // Game Controls
        cout << "4. CONTROLS (This Game)\n";
        cout << "   --------------------\n";
        cout << "   ARROW KEYS: Move cursor on board\n";
        cout << "   SPACE: Select piece / Make move\n";
        cout << "   S: Save current game\n";
        cout << "   L: Load saved game\n";
        cout << "   R: Restart game\n";
        cout << "   ESC: Return to menu\n\n";

        // Game Interface
        cout << "5. GAME INTERFACE\n";
        cout << "   --------------\n";
        cout << "   - Yellow square: Current cursor position\n";
        cout << "   - Green squares: Valid moves for selected piece\n";
        cout << "   - Board coordinates: a-h (columns), 1-8 (rows)\n";
        cout << "   - White pieces: UPPERCASE letters\n";
        cout << "   - Black pieces: lowercase letters\n\n";

        // Notation
        cout << "6. CHESS NOTATION\n";
        cout << "   --------------\n";
        cout << "   - Each square has unique name (e.g., e4, d5)\n";
        cout << "   - Columns: a to h (left to right)\n";
        cout << "   - Rows: 1 to 8 (bottom to top)\n";
        cout << "   - Move format: Piece + square (e.g., Nf3 = Knight to f3)\n\n";

        // Strategy Tips
        cout << "7. BASIC STRATEGY\n";
        cout << "   --------------\n";
        cout << "   - Control the center of the board\n";
        cout << "   - Develop knights and bishops early\n";
        cout << "   - Castle early to protect king\n";
        cout << "   - Don't move the same piece multiple times early\n";
        cout << "   - Connect your rooks\n";
        cout << "   - Protect your king at all times\n";
        cout << "   - Look for checks, captures, and threats\n\n";

        // Winning Conditions
        cout << "8. WINNING THE GAME\n";
        cout << "   ----------------\n";
        cout << "   - Checkmate opponent's king\n";
        cout << "   - Opponent resigns\n";
        cout << "   - Opponent runs out of time (in timed games)\n\n";

        SetConsoleTextAttribute(hConsole, 12); // Red
        cout << "IMPORTANT RULES:\n";
        SetConsoleTextAttribute(hConsole, 7);
        cout << "- You cannot move into check\n";
        cout << "- You must get out of check if your king is attacked\n";
        cout << "- You cannot castle through check\n";
        cout << "- Pawns capture differently than they move\n\n";

        // Back option
        SetConsoleTextAttribute(hConsole, 14); // Yellow
        cout << "=========================================\n";
        cout << "Press B to go back to Main Menu...\n";

        // Wait for B key
        while (true) {
            if (GetAsyncKeyState('B') & 0x8000) {
                running = false;
                break;
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
                running = false;
                break;
            }
            Sleep(50);
        }
    }
}