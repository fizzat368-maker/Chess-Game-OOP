#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece {
public:
    Knight(PieceColor c);

    vector<Position> getMoveHints(Position pos, Board* board) override;
    bool isValidMove(Position src, Position dst, Board* board) override;
    string getName() const override;
};

#endif