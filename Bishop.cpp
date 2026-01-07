
#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(PieceColor c) : Piece(c, c == WHITE ? 'B' : 'b') {}

vector<Position> Bishop::getMoveHints(Position pos, Board* board) {
    vector<Position> moves;
    int dirs[][2] = { {-1,-1}, {-1,1}, {1,-1}, {1,1} };

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

bool Bishop::isValidMove(Position src, Position dst, Board* board) {
    auto hints = getMoveHints(src, board);
    for (auto& h : hints)
        if (h == dst) return true;
    return false;
}

string Bishop::getName() const {
    return "Bishop";
}