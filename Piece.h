#ifndef PIECE_H
#define PIECE_H
#include "Position.h"
#include <vector>
#include <string>
using namespace std;

class Board;

enum PieceColor { WHITE, BLACK };

class Piece {
protected:
    PieceColor color;
    char symbol;

public:
    Piece(PieceColor c, char s);
    virtual ~Piece();

    PieceColor getColor() const;
    char getSymbol() const;

    virtual vector<Position> getMoveHints(Position pos, Board* board) = 0;
    virtual bool isValidMove(Position src, Position dst, Board* board) = 0;
    virtual string getName() const = 0;
};

#endif