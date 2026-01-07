#include "SaveLoad.h"
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <fstream>
#include <iostream>
using namespace std;

bool SaveLoad::saveGame(Board* board, PieceColor currentPlayer, string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not save game!\n";
        return false;
    }

    // Save current player
    file << (currentPlayer == WHITE ? "WHITE" : "BLACK") << endl;

    // Save board pieces as symbols
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* piece = board->getPiece(Position(i, j));
            if (piece) {
                file << piece->getSymbol();
            }
            else {
                file << '.';
            }
        }
        file << endl;
    }

    file.close();
    cout << "Game saved successfully!\n";
    return true;
}

bool SaveLoad::loadGame(Board* board, PieceColor& currentPlayer, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not load game!\n";
        return false;
    }

    string player;
    file >> player;
    currentPlayer = (player == "WHITE") ? WHITE : BLACK;
    file.ignore(); // skip newline

    // Clear existing board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Piece* p = board->getPiece(Position(i, j));
            if (p) delete p;
            board->setPiece(Position(i, j), nullptr);
        }
    }

    // Read board lines
    string line;
    for (int i = 0; i < 8; i++) {
        if (!getline(file, line)) break;
        for (int j = 0; j < 8; j++) {
            char symbol = line[j];
            Piece* piece = nullptr;
            switch (symbol) {
            case 'P': piece = new Pawn(WHITE); break;
            case 'p': piece = new Pawn(BLACK); break;
            case 'R': piece = new Rook(WHITE); break;
            case 'r': piece = new Rook(BLACK); break;
            case 'N': piece = new Knight(WHITE); break;
            case 'n': piece = new Knight(BLACK); break;
            case 'B': piece = new Bishop(WHITE); break;
            case 'b': piece = new Bishop(BLACK); break;
            case 'Q': piece = new Queen(WHITE); break;
            case 'q': piece = new Queen(BLACK); break;
            case 'K': piece = new King(WHITE); break;
            case 'k': piece = new King(BLACK); break;
            case '.': piece = nullptr; break;
            }
            board->setPiece(Position(i, j), piece);
        }
    }

    file.close();
    cout << "Game loaded successfully!\n";
    return true;
}
