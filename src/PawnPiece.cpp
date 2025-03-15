#include "../include/PawnPiece.h"

PawnPiece::PawnPiece(int row, int col, char symbol, std::string color) 
    : ChessPiece(row, col, symbol, color) {}

PawnPiece::~PawnPiece() = default;

bool PawnPiece::isValidMove(const int &row, const int &col) {
    
}

void PawnPiece::moveTo(const int &row, const int &col){
    if(!isValidMove(row, col)) throw invalidMoveException("Invalid move");
    
    this->row = row;
    this->col = col;
}
