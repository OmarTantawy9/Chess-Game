#include "../include/ChessPiece.h"

ChessPiece::ChessPiece(int row, int col, char symbol, std::string color) 
    : row(row), col(col), symbol(symbol), color(color) {}
ChessPiece::~ChessPiece() = default;