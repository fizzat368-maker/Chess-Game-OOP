#include "King.h"
#include "Board.h"

King::King(PieceColor c) : Piece(c, c == WHITE ? 'K' : 'k') {}

vector<Position> King::getMoveHints(Position pos, Board* board) {
    vector<Position> moves;
    int dirs[][2] = { {-1,0},{1,0},{0,-1},{0,1},{-1,-1},{-1,1},{1,-1},{1,1} };

    for (auto& dir : dirs) {
        Position newPos(pos.row + dir[0], pos.col + dir[1]);
        if (newPos.isValid()) {
            Piece* target = board->getPiece(newPos);
            if (!target || target->getColor() != color)
                moves.push_back(newPos);
        }
    }
    return moves;
}

bool King::isValidMove(Position src, Position dst, Board* board) {
    auto hints = getMoveHints(src, board);
    for (auto& h : hints)
        if (h == dst) return true;
    return false;
}

string King::getName() const {
    return "King";
}