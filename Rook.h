#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(PieceColor c);

    vector<Position> getMoveHints(Position pos, Board* board) override;
    bool isValidMove(Position src, Position dst, Board* board) override;
    string getName() const override;
};

#endif