#include "Rook.h"
#include "Board.h"

Rook::Rook(PieceColor c) : Piece(c, c == WHITE ? 'R' : 'r') {}

vector<Position> Rook::getMoveHints(Position pos, Board* board) {
    vector<Position> moves;
    int dirs[][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

    for (auto& dir : dirs) {
        for (int i = 1; i < 8; i++) {
            Position newPos(pos.row + dir[0] * i, pos.col + dir[1] * i);
            if (!newPos.isValid()) break;

            Piece* target = board->getPiece(newPos);
            if (!target) {
                moves.push_back(newPos);
            }
            else {
                if (target->getColor() != color)
                    moves.push_back(newPos);
                break;
            }
        }
    }
    return moves;
}

bool Rook::isValidMove(Position src, Position dst, Board* board) {
    auto hints = getMoveHints(src, board);
    for (auto& h : hints)
        if (h == dst) return true;
    return false;
}

string Rook::getName() const {
    return "Rook";
}