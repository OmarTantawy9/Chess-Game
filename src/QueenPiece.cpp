#include "../include/QueenPiece.h"

QueenPiece::QueenPiece(int row, int col, char symbol, std::string color) 
    : ChessPiece(row, col, symbol, color) {}

QueenPiece::~QueenPiece() = default;

bool QueenPiece::isValidMove(const int &row, const int &col) {
    
}

void QueenPiece::moveTo(const int &row, const int &col){
    if(!isValidMove(row, col)) throw invalidMoveException("Invalid move");
    
    this->row = row;
    this->col = col;
}
