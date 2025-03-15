#include "../include/KnightPiece.h"

KnightPiece::KnightPiece(int row, int col, char symbol, std::string color) 
    : ChessPiece(row, col, symbol, color) {}

KnightPiece::~KnightPiece() = default;

bool KnightPiece::isValidMove(const int &row, const int &col) {
    
}

void KnightPiece::moveTo(const int &row, const int &col){
    if(!isValidMove(row, col)) throw invalidMoveException("Invalid move");
    
    this->row = row;
    this->col = col;
}
