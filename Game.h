#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include <vector>
#include <string>  // Make sure this is included

class Game {
private:
    Board board;
    PieceColor currentPlayer;
    Position selectedPos;
    bool pieceSelected;
    std::vector<Position> validMoves;
    bool gameRunning;
    std::string currentMessage;
    bool needsRedraw;

public:
    Game();

    // Public interface methods
    void start();
    bool loadSavedGame();
    void saveCurrentGame();

private:
    // Private helper methods
    void drawGameScreen();
    void drawSideMenu();
    void handleMouseClick(int x, int y);
    void processClick(Position pos);
    void switchPlayer();
    bool handleKeyboardInput();
};

#endif