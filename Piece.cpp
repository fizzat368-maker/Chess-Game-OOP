#include "Piece.h"

Piece::Piece(PieceColor c, char s) : color(c), symbol(s) {}

Piece::~Piece() {}

PieceColor Piece::getColor() const {
    return color;
}

char Piece::getSymbol() const {
    return symbol;
}