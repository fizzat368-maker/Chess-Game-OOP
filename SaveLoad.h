#ifndef SAVELOAD_H
#define SAVELOAD_H
#include <string>
using namespace std;

class Board;
enum PieceColor;

class SaveLoad {
public:
    static bool saveGame(Board* board, PieceColor currentPlayer, string filename);
    static bool loadGame(Board* board, PieceColor& currentPlayer, string filename);
};

#endif