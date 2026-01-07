#include "Knight.h"
#include "Board.h"

Knight::Knight(PieceColor c) : Piece(c, c == WHITE ? 'N' : 'n') {}

vector<Position> Knight::getMoveHints(Position pos, Board* board) {
    vector<Position> moves;
    int offsets[][2] = { {-2,-1},{-2,1},{-1,-2},{-1,2},{1,-2},{1,2},{2,-1},{2,1} };

    for (auto& offset : offsets) {
        Position newPos(pos.row + offset[0], pos.col + offset[1]);
        if (newPos.isValid()) {
            Piece* target = board->getPiece(newPos);
            if (!target || target->getColor() != color)
                moves.push_back(newPos);
        }
    }
    return moves;
}

bool Knight::isValidMove(Position src, Position dst, Board* board) {
    auto hints = getMoveHints(src, board);
    for (auto& h : hints)
        if (h == dst) return true;
    return false;
}

string Knight::getName() const {
    return "Knight";
}