#ifndef BOARD_H
#define BOARD_H

#include "ChessPiece.h"
#include "KingPiece.h"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include <utility>

using ChessPiecePtr = std::shared_ptr<ChessPiece>;

class Board {

    std::vector<std::vector<ChessPiecePtr>> board;
    std::vector<ChessPiecePtr> whiteGraveYard;
    std::vector<ChessPiecePtr> blackGraveYard;
    ChessPiecePtr whiteKing;
    ChessPiecePtr blackKing;
    bool isWhiteTurn;
    bool isGameOverFlag;
    std::string winner;

public:
    Board();
    ~Board();

    void capturePiece(int row, int col);

    inline ChessPiecePtr getPieceAt(const int &row, const int &col) const { 
        return board[row][col]; 
    }

    inline std::string getPlayerTurn() const { return isWhiteTurn ? "white" : "black" ;}
    inline ChessPiecePtr getKing(const std::string &kingColor) {return kingColor == "white" ? whiteKing : blackKing;}
    
    inline void switchTurn(){isWhiteTurn = !isWhiteTurn;} 
    inline std::string getWinner() const { return winner;}  
    
    bool isInCheck(const ChessPiecePtr &king);


    bool isGameOver() {

        return false;
    }  



    bool isPathClear(int startRow, int startCol, int endRow, int endCol) const;
    // bool isUnderAttack(int row, int col, const std::string &color) const;
    bool wouldLeaveKingInCheck(ChessPiece &piece, int newRow, int newCol);
    ChessPiecePtr findKing(const std::string &kingColor) const;

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