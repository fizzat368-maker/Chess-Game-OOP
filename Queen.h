#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece {
public:
    Queen(PieceColor c);

    vector<Position> getMoveHints(Position pos, Board* board) override;
    bool isValidMove(Position src, Position dst, Board* board) override;
    string getName() const override;
};

#endif