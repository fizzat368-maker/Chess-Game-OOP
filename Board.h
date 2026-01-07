#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Position.h"
#include <vector>

class Board {
private:
    Piece* grid[8][8];  // 8x8 chess board

public:
    // Constructor and Destructor
    Board();
    ~Board();

    // Initialize board with starting position
    void initialize();

    // Piece management
    Piece* getPiece(Position pos) const;
    void setPiece(Position pos, Piece* piece);

    // Game actions
    bool movePiece(Position src, Position dst);

    // Display functions
    void draw(Position selected, std::vector<Position> hints) const;

    // Input conversion
    Position screenToBoard(int x, int y) const;

    // Utility functions
    void clearBoard();
    bool isPositionOccupied(Position pos) const;
    bool isPositionOccupiedByColor(Position pos, PieceColor color) const;

private:
    // Helper functions for drawing
    void drawBoardBackground() const;
    void drawPieces() const;
    void drawCoordinates() const;
};

#endif