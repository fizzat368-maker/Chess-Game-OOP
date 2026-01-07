#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece {
public:
    King(PieceColor c);

    vector<Position> getMoveHints(Position pos, Board* board) override;
    bool isValidMove(Position src, Position dst, Board* board) override;
    string getName() const override;
};

#endif