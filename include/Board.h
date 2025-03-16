#ifndef BOARD_H
#define BOARD_H

#include "ChessPiece.h"
#include <vector>
#include <memory>

using ChessPiecePtr = std::shared_ptr<ChessPiece>;

class Board {

    std::vector<std::vector<ChessPiecePtr>> board;
    std::vector<ChessPiecePtr> whiteGraveYard;
    std::vector<ChessPiecePtr> blackGraveYard;

public:
    Board();
    ~Board();

    void capturePiece(int row, int col);

    inline std::weak_ptr<ChessPiece> getPieceAt(const int &row, const int &col) const { 
        return board[row][col]; 
    }

    bool isPathClear(int startRow, int startCol, int endRow, int endCol) const;

};



#endif //  BOARD_H