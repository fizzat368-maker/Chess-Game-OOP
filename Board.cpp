#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "ConsoleUtils.h"
#include "Settings.h"
#include <iostream>
using namespace std;

// Constructor - initialize empty board
Board::Board() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = nullptr;
        }
    }
}

// Destructor - free all pieces
Board::~Board() {
    clearBoard();
}

// Initialize board with standard chess setup
void Board::initialize() {
    clearBoard();

    // Black pieces (top rows 0-1)
    grid[0][0] = new Rook(BLACK);
    grid[0][1] = new Knight(BLACK);
    grid[0][2] = new Bishop(BLACK);
    grid[0][3] = new Queen(BLACK);
    grid[0][4] = new King(BLACK);
    grid[0][5] = new Bishop(BLACK);
    grid[0][6] = new Knight(BLACK);
    grid[0][7] = new Rook(BLACK);

    // Black pawns
    for (int i = 0; i < 8; i++) {
        grid[1][i] = new Pawn(BLACK);
    }

    // White pieces (bottom rows 6-7)
    // White pawns
    for (int i = 0; i < 8; i++) {
        grid[6][i] = new Pawn(WHITE);
    }

    // White major pieces
    grid[7][0] = new Rook(WHITE);
    grid[7][1] = new Knight(WHITE);
    grid[7][2] = new Bishop(WHITE);
    grid[7][3] = new Queen(WHITE);
    grid[7][4] = new King(WHITE);
    grid[7][5] = new Bishop(WHITE);
    grid[7][6] = new Knight(WHITE);
    grid[7][7] = new Rook(WHITE);
}

// Get piece at position
Piece* Board::getPiece(Position pos) const {
    if (!pos.isValid()) {
        return nullptr;
    }
    return grid[pos.row][pos.col];
}

// Set piece at position
void Board::setPiece(Position pos, Piece* piece) {
    if (pos.isValid()) {
        grid[pos.row][pos.col] = piece;
    }
}

// Move piece from src to dst
bool Board::movePiece(Position src, Position dst) {
    // Validate positions
    if (!src.isValid() || !dst.isValid()) {
        return false;
    }

    // Get the piece to move
    Piece* piece = getPiece(src);
    if (!piece) {
        return false; // No piece at source
    }

    // Check if move is valid
    if (!piece->isValidMove(src, dst, this)) {
        return false;
    }

    // Handle capture if destination has piece
    Piece* target = getPiece(dst);
    if (target) {
        delete target; // Capture the piece
    }

    // Move the piece
    setPiece(dst, piece);
    setPiece(src, nullptr);

    return true;
}

// Draw the board with highlights
void Board::draw(Position selected, vector<Position> hints) const {
    // Board dimensions
    const int CELL_HEIGHT = 3;
    const int CELL_WIDTH = 6;
    const int BOARD_START_X = 4;
    const int BOARD_START_Y = 2;

    // Draw top coordinates
    ConsoleUtils::setColor(7);
    ConsoleUtils::gotoxy(BOARD_START_X, 0);
    cout << "    a     b     c     d     e     f     g     h    ";

    // Draw the chess board
    for (int boardRow = 0; boardRow < 8; boardRow++) {
        // Draw row number on left
        ConsoleUtils::gotoxy(0, boardRow * CELL_HEIGHT + BOARD_START_Y);
        cout << (8 - boardRow) << " ";

        for (int cellRow = 0; cellRow < CELL_HEIGHT; cellRow++) {
            for (int boardCol = 0; boardCol < 8; boardCol++) {
                Position pos(boardRow, boardCol);

                // Check if this position should be highlighted
                bool isHint = false;
                bool isSelected = (selected == pos);

                for (auto& hint : hints) {
                    if (hint == pos) {
                        isHint = true;
                        break;
                    }
                }

                // Determine background color
                int bgColor;
                if (isSelected) {
                    bgColor = BACKGROUND_RED | BACKGROUND_INTENSITY;
                }
                else if (isHint) {
                    bgColor = Settings::highlightColor;
                }
                else if ((boardRow + boardCol) % 2 == 0) {
                    bgColor = Settings::lightSquare;
                }
                else {
                    bgColor = Settings::darkSquare;
                }

                // Calculate screen position
                int screenX = boardCol * CELL_WIDTH + BOARD_START_X;
                int screenY = boardRow * CELL_HEIGHT + cellRow + BOARD_START_Y;

                ConsoleUtils::gotoxy(screenX, screenY);
                ConsoleUtils::setColor(bgColor);

                // Draw the cell
                for (int cellCol = 0; cellCol < CELL_WIDTH; cellCol++) {
                    if (cellRow == CELL_HEIGHT / 2 &&
                        cellCol == CELL_WIDTH / 2 &&
                        grid[boardRow][boardCol]) {

                        Piece* piece = grid[boardRow][boardCol];

                        // Set text color
                        int textColor;
                        if (piece->getColor() == WHITE) {
                            textColor = FOREGROUND_RED | FOREGROUND_GREEN |
                                FOREGROUND_BLUE | FOREGROUND_INTENSITY;
                        }
                        else {
                            textColor = 0;
                        }

                        ConsoleUtils::setColor(bgColor | textColor);
                        cout << piece->getSymbol();
                        ConsoleUtils::setColor(bgColor);
                    }
                    else {
                        cout << " ";
                    }
                }
            }
        }

        // Draw row number on right
        ConsoleUtils::setColor(7);
        ConsoleUtils::gotoxy(52, boardRow * CELL_HEIGHT + BOARD_START_Y);
        cout << (8 - boardRow);
    }

    // Draw bottom coordinates
    ConsoleUtils::setColor(7);
    ConsoleUtils::gotoxy(BOARD_START_X, 26);
    cout << "    a     b     c     d     e     f     g     h    ";

    ConsoleUtils::setColor(7);
}

// Convert screen coordinates to board position
Position Board::screenToBoard(int x, int y) const {
    const int BOARD_START_X = 4;
    const int BOARD_START_Y = 2;
    const int CELL_WIDTH = 6;
    const int CELL_HEIGHT = 3;

    // Adjust for board offset
    int relativeX = x - BOARD_START_X;
    int relativeY = y - BOARD_START_Y;

    // Check if click is before board starts
    if (relativeX < 0 || relativeY < 0) {
        return Position(-1, -1);
    }

    // Calculate board coordinates
    int boardCol = relativeX / CELL_WIDTH;
    int boardRow = relativeY / CELL_HEIGHT;

    // Validate bounds
    if (boardRow >= 0 && boardRow < 8 && boardCol >= 0 && boardCol < 8) {
        return Position(boardRow, boardCol);
    }

    return Position(-1, -1);
}

// Clear all pieces from board
void Board::clearBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (grid[i][j]) {
                delete grid[i][j];
                grid[i][j] = nullptr;
            }
        }
    }
}

// Check if position is occupied
bool Board::isPositionOccupied(Position pos) const {
    if (!pos.isValid()) return false;
    return (grid[pos.row][pos.col] != nullptr);
}

// Check if position is occupied by specific color
bool Board::isPositionOccupiedByColor(Position pos, PieceColor color) const {
    if (!pos.isValid()) return false;
    Piece* piece = grid[pos.row][pos.col];
    return (piece != nullptr && piece->getColor() == color);
}