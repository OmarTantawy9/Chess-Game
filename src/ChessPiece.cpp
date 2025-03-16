#include "../include/ChessPiece.h"

ChessPiece::ChessPiece(int row, int col, std::string color) 
    : row(row), col(col), color(color) {}
ChessPiece::~ChessPiece() = default;