#include "../include/ChessPiece.h"
#include "../include/Board.h"

ChessPiece::ChessPiece(int row, int col, std::string color) 
    : row(row), col(col), color(color) {}
ChessPiece::~ChessPiece() = default;

bool ChessPiece::isOccupiedByTeamMate(const int &row, const int &col, const Board &board) const{
    std::cout << row << " " << col << std::endl;
    auto targetPiece = board.getPieceAt(row, col);
    return targetPiece && targetPiece->getColor() == color;
}