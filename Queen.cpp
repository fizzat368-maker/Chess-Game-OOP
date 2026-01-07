#include "Queen.h"
#include "Board.h"

Queen::Queen(PieceColor c) : Piece(c, c == WHITE ? 'Q' : 'q') {}

vector<Position> Queen::getMoveHints(Position pos, Board* board) {
    vector<Position> moves;
    int dirs[][2] = { {-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1} };

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

bool Queen::isValidMove(Position src, Position dst, Board* board) {
    auto hints = getMoveHints(src, board);
    for (auto& h : hints)
        if (h == dst) return true;
    return false;
}

string Queen::getName() const {
    return "Queen";
}