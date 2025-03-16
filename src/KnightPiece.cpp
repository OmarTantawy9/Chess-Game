#include "../include/KnightPiece.h"
#include "../include/Board.h"

KnightPiece::KnightPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

KnightPiece::~KnightPiece() = default;

bool KnightPiece::isValidMove(const int &row, const int &col, const Board &board) {

    // Ensure the move is within the board bounds
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;

    int rowDiff = std::abs(row - this->row);
    int colDiff = std::abs(col - this->col);

    // Check if move follows the L-shape pattern
    bool isLShape = (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    if (!isLShape) return false;

    // Check if the destination square is occupied
    auto targetPiece = board.getPieceAt(row, col);
    if (!targetPiece.expired() && targetPiece.lock()->getColor() == color) {
        return false; // Cannot capture a friendly piece
    }

    return true;
}

void KnightPiece::moveTo(const int &row, const int &col){
    // if(!isValidMove(row, col)) throw invalidMoveException("Invalid move");
    
    this->row = row;
    this->col = col;
}
