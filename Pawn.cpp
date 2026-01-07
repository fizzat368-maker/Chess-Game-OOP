#include "Pawn.h"
#include "Board.h"
#include <vector>
using namespace std; 

Pawn::Pawn(PieceColor c) : Piece(c, c == WHITE ? 'P' : 'p') {}

vector<Position> Pawn::getMoveHints(Position pos, Board* board) {
    vector<Position> moves;
    int direction = (color == WHITE) ? -1 : 1;
    int startRow = (color == WHITE) ? 6 : 1;

    Position forward(pos.row + direction, pos.col);
    if (forward.isValid() && !board->getPiece(forward))
        moves.push_back(forward);

    if (pos.row == startRow) {
        Position twoForward(pos.row + 2 * direction, pos.col);
        if (twoForward.isValid() && !board->getPiece(twoForward) && !board->getPiece(forward))
            moves.push_back(twoForward);
    }

    Position captureLeft(pos.row + direction, pos.col - 1);
    if (captureLeft.isValid()) {
        Piece* target = board->getPiece(captureLeft);
        if (target && target->getColor() != color)
            moves.push_back(captureLeft);
    }

    Position captureRight(pos.row + direction, pos.col + 1);
    if (captureRight.isValid()) {
        Piece* target = board->getPiece(captureRight);
        if (target && target->getColor() != color)
            moves.push_back(captureRight);
    }

    return moves;
}

bool Pawn::isValidMove(Position src, Position dst, Board* board) {
    auto hints = getMoveHints(src, board);
    for (auto& h : hints)
        if (h == dst) return true;
    return false;
}

string Pawn::getName() const {
    return "Pawn";
}