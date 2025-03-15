#include "../include/RookPiece.h"

RookPiece::RookPiece(int row, int col, char symbol, std::string color) 
    : ChessPiece(row, col, symbol, color) {}

RookPiece::~RookPiece() = default;

bool RookPiece::isValidMove(const int &row, const int &col) {
    
}

void RookPiece::moveTo(const int &row, const int &col){
    if(!isValidMove(row, col)) throw invalidMoveException("Invalid move");
    
    this->row = row;
    this->col = col;
}
