#include "../include/BishopPiece.h"

BishopPiece::BishopPiece(int row, int col, char symbol, std::string color) 
    : ChessPiece(row, col, symbol, color) {}

BishopPiece::~BishopPiece() = default;

bool BishopPiece::isValidMove(const int &row, const int &col) {
    
}

void BishopPiece::moveTo(const int &row, const int &col){
    if(!isValidMove(row, col)) throw invalidMoveException("Invalid move");
    
    this->row = row;
    this->col = col;
}
