#ifndef BOARD_H
#define BOARD_H

#include "ChessPiece.h"
#include <vector>
#include <memory>
#include <iostream>

using ChessPiecePtr = std::shared_ptr<ChessPiece>;

class Board {

    std::vector<std::vector<ChessPiecePtr>> board;
    std::vector<ChessPiecePtr> whiteGraveYard;
    std::vector<ChessPiecePtr> blackGraveYard;

public:
    Board();
    ~Board();

    void capturePiece(int row, int col);

    inline ChessPiecePtr getPieceAt(const int &row, const int &col) const { 
        return board[row][col]; 
    }

    // inline ChessPiecePtr getChessPtr(const int &row, const int &col) const{
    //     return board[row][col];
    // }

    bool isPathClear(int startRow, int startCol, int endRow, int endCol) const;

    inline void movePiece(const int &oldRow, const int &oldCol, const int &newRow, const int &newCol){
        board[newRow][newCol] = std::move(board[oldRow][oldCol]); 
    }

    inline std::vector<std::vector<ChessPiecePtr>>& getPieces(){
        return board;
    }

    inline void print(){
        for(const auto &row : board){
            for (const auto &piece : row) {
                if(piece) std::cout << ". "; 
                else std::cout << "  ";  
            }
            std::cout << std::endl;   

        }
    }

};



#endif //  BOARD_H