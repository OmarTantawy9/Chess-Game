#include "../include/KingPiece.h"
#include "../include/Board.h"


KingPiece::KingPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

KingPiece::~KingPiece() = default;

bool KingPiece::isValidMove(const int &row, const int &col, const Board &board) {

    int rowDiff = std::abs(row - this->row);
    int colDiff = std::abs(col - this->col);

    // Ensure within board bounds
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;

    // King moves only one square in any direction
    if (!(rowDiff <= 1 && colDiff <= 1) || (rowDiff == 0 && colDiff == 0)) {
        return false;
    }

    // Check destination square
    auto targetPiece = board.getPieceAt(row, col);     // maybe implement a callback
    if (!targetPiece.expired() && targetPiece.lock()->getColor() == color) {
        return false; // Cannot capture a friendly piece
    }

    
}

void KingPiece::moveTo(const int &row, const int &col){
    // if(!isValidMove(row, col)) throw invalidMoveException("Invalid move");
    
    this->row = row;
    this->col = col;
}
