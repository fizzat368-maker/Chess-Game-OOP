#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(PieceColor c);

    vector<Position> getMoveHints(Position pos, Board* board) override;
    bool isValidMove(Position src, Position dst, Board* board) override;
    string getName() const override;
};

#endif