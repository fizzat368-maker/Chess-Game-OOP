#include "Game.h"
#include "ConsoleUtils.h"
#include "Settings.h"
#include "SaveLoad.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>  // Make sure this is included

using namespace std;

Game::Game() : currentPlayer(WHITE), selectedPos(-1, -1),
pieceSelected(false), gameRunning(true),
needsRedraw(true) {
    board.initialize();
    currentMessage = "White's turn. Click a piece to select.";
}

void Game::start() {
    // Clear screen once at start
    ConsoleUtils::clearScreen();

    // Initial draw
    drawGameScreen();

    // Main game loop
    while (gameRunning) {
        // Check if we need to redraw
        if (needsRedraw) {
            drawGameScreen();
            needsRedraw = false;
        }

        // Handle mouse clicks
        int mouseX, mouseY;
        if (ConsoleUtils::getMouseClick(mouseX, mouseY)) {
            handleMouseClick(mouseX, mouseY);
            needsRedraw = true;  // Mark for redraw
        }

        // Handle keyboard input
        if (handleKeyboardInput()) {
            needsRedraw = true;  // Mark for redraw
        }

        // Small delay to prevent CPU overuse
        Sleep(30);
    }
}

void Game::drawGameScreen() {
    // Draw board with current state
    board.draw(selectedPos, validMoves);

    // Draw side menu
    drawSideMenu();
}

void Game::drawSideMenu() {
    int menuX = 70; // Position menu on right side

    // Clear the menu area first (partial clear)
    for (int row = 2; row <= 35; row++) {
        ConsoleUtils::gotoxy(menuX, row);
        cout << "                         "; // 25 spaces
    }

    // Title
    ConsoleUtils::gotoxy(menuX, 2);
    cout << "========================";
    ConsoleUtils::gotoxy(menuX, 3);
    cout << "     CHESS GAME INFO";
    ConsoleUtils::gotoxy(menuX, 4);
    cout << "========================";

    // Current player
    ConsoleUtils::gotoxy(menuX, 6);
    cout << "Current Player: ";
    if (currentPlayer == WHITE) {
        ConsoleUtils::setColor(15); // Bright white
        cout << "WHITE";
    }
    else {
        ConsoleUtils::setColor(8); // Gray
        cout << "BLACK";
    }
    ConsoleUtils::setColor(7); // Reset

    // Game status
    ConsoleUtils::gotoxy(menuX, 8);
    cout << "Status: ";
    ConsoleUtils::setColor(10); // Green
    cout << "ACTIVE";
    ConsoleUtils::setColor(7);

    // Selected piece info
    ConsoleUtils::gotoxy(menuX, 10);
    cout << "------------------------";

    if (pieceSelected) {
        Piece* piece = board.getPiece(selectedPos);
        if (piece) {
            ConsoleUtils::gotoxy(menuX, 11);
            cout << "Selected: ";
            ConsoleUtils::setColor(14); // Yellow
            cout << piece->getName();
            ConsoleUtils::setColor(7);

            ConsoleUtils::gotoxy(menuX, 12);
            char col = 'a' + selectedPos.col;
            int rowNum = 8 - selectedPos.row;
            cout << "At: " << col << rowNum;

            ConsoleUtils::gotoxy(menuX, 13);
            cout << "Valid Moves: " << validMoves.size();

            // Show first few valid moves
            if (!validMoves.empty()) {
                ConsoleUtils::gotoxy(menuX, 14);
                cout << "------------------------";

                int line = 15;
                for (size_t i = 0; i < validMoves.size() && i < 6; i++) {
                    ConsoleUtils::gotoxy(menuX, line++);
                    char colChar = 'a' + validMoves[i].col;
                    int rowNum2 = 8 - validMoves[i].row;
                    cout << "  " << colChar << rowNum2;
                }
            }
        }
    }
    else {
        ConsoleUtils::gotoxy(menuX, 11);
        cout << "No piece selected";
        ConsoleUtils::gotoxy(menuX, 12);
        cout << "Click a piece to select";
    }

    // Controls
    ConsoleUtils::gotoxy(menuX, 22);
    cout << "========================";
    ConsoleUtils::gotoxy(menuX, 23);
    cout << "       CONTROLS";
    ConsoleUtils::gotoxy(menuX, 24);
    cout << "========================";
    ConsoleUtils::gotoxy(menuX, 25);
    cout << "Mouse: Select & Move";
    ConsoleUtils::gotoxy(menuX, 26);
    cout << "S: Save Game";
    ConsoleUtils::gotoxy(menuX, 27);
    cout << "L: Load Game";
    ConsoleUtils::gotoxy(menuX, 28);
    cout << "ESC: Main Menu";

    // Current message
    ConsoleUtils::gotoxy(menuX, 30);
    cout << "------------------------";
    ConsoleUtils::gotoxy(menuX, 31);
    cout << "Message:";
    ConsoleUtils::gotoxy(menuX, 32);

    // Display message with appropriate color
    if (currentMessage.find("success") != string::npos) {
        ConsoleUtils::setColor(10); // Green for success
    }
    else if (currentMessage.find("fail") != string::npos ||
        currentMessage.find("Invalid") != string::npos) {
        ConsoleUtils::setColor(12); // Red for errors
    }
    else if (currentMessage.find("Selected") != string::npos) {
        ConsoleUtils::setColor(14); // Yellow for selections
    }
    else {
        ConsoleUtils::setColor(11); // Cyan for info
    }

    cout << currentMessage;

    // Clear any remaining characters from previous message
    int spacesNeeded = 25 - (int)currentMessage.length();
    for (int i = 0; i < spacesNeeded; i++) {
        cout << " ";
    }

    ConsoleUtils::setColor(7); // Reset color

    // Instructions
    ConsoleUtils::gotoxy(menuX, 34);
    cout << "Click on board to play!";
}

void Game::handleMouseClick(int x, int y) {
    Position clicked = board.screenToBoard(x, y);

    if (!clicked.isValid()) {
        // Clicked outside board
        if (pieceSelected) {
            pieceSelected = false;
            selectedPos = Position(-1, -1);
            validMoves.clear();
            currentMessage = "Piece deselected";
        }
        return;
    }

    // Process the click
    processClick(clicked);
}

void Game::processClick(Position pos) {
    Piece* clickedPiece = board.getPiece(pos);

    if (!pieceSelected) {
        // No piece selected yet
        if (clickedPiece && clickedPiece->getColor() == currentPlayer) {
            // Select this piece
            selectedPos = pos;
            validMoves = clickedPiece->getMoveHints(pos, &board);
            pieceSelected = true;

            char col = 'a' + selectedPos.col;
            int rowNum = 8 - selectedPos.row;

            // FIXED: Proper string concatenation
            string pieceName = clickedPiece->getName();
            currentMessage = "Selected " + pieceName + " at " + col + to_string(rowNum);
        }
        else if (clickedPiece) {
            // FIXED: Proper string concatenation
            string playerColor = (currentPlayer == WHITE) ? "white" : "black";
            currentMessage = "That's not your piece! Select a " + playerColor + " piece.";
        }
        else {
            currentMessage = "Select a piece to move";
        }
    }
    else {
        // Already have a piece selected
        if (pos == selectedPos) {
            // Clicked same piece - deselect
            pieceSelected = false;
            selectedPos = Position(-1, -1);
            validMoves.clear();
            currentMessage = "Piece deselected";
        }
        else {
            // Check if this is a valid move
            bool validMove = false;
            for (auto& hint : validMoves) {
                if (hint == pos) {
                    validMove = true;
                    break;
                }
            }

            if (validMove) {
                // Try to make the move
                if (board.movePiece(selectedPos, pos)) {
                    currentMessage = "Move successful!";
                    switchPlayer();
                }
                else {
                    currentMessage = "Move failed!";
                }

                // Clear selection
                pieceSelected = false;
                selectedPos = Position(-1, -1);
                validMoves.clear();
            }
            else {
                // Invalid move - check if clicked another friendly piece
                if (clickedPiece && clickedPiece->getColor() == currentPlayer) {
                    // Select new piece
                    selectedPos = pos;
                    validMoves = clickedPiece->getMoveHints(pos, &board);
                    pieceSelected = true;
                    currentMessage = "Selected different piece";
                }
                else {
                    currentMessage = "Invalid move!";
                    pieceSelected = false;
                    selectedPos = Position(-1, -1);
                    validMoves.clear();
                }
            }
        }
    }
}

bool Game::handleKeyboardInput() {
    // Check for S key (save)
    if (GetAsyncKeyState('S') & 0x8000) {
        saveCurrentGame();
        currentMessage = "Game saved successfully!";
        Sleep(300);
        return true;
    }

    // Check for L key (load)
    if (GetAsyncKeyState('L') & 0x8000) {
        if (loadSavedGame()) {
            currentMessage = "Game loaded successfully!";
        }
        else {
            currentMessage = "No saved game found!";
        }
        Sleep(300);
        return true;
    }

    // Check for ESC key (exit)
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
        gameRunning = false;
        Sleep(300);
        return true;
    }

    return false;
}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == WHITE) ? BLACK : WHITE;
    currentMessage = (currentPlayer == WHITE) ? "White's turn" : "Black's turn";
}

bool Game::loadSavedGame() {
    bool result = SaveLoad::loadGame(&board, currentPlayer, "chess_save.txt");
    if (result) {
        pieceSelected = false;
        selectedPos = Position(-1, -1);
        validMoves.clear();
        needsRedraw = true;
    }
    return result;
}

void Game::saveCurrentGame() {
    SaveLoad::saveGame(&board, currentPlayer, "chess_save.txt");
}