#include "../include/BishopPiece.h"
#include "../include/Board.h"

BishopPiece::BishopPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

BishopPiece::~BishopPiece() = default;

bool BishopPiece::isValidMove(const int &row, const int &col, const Board &board) {

    if (row == this->row && col == this->col) return false; // No movement

    // Ensure move is within board bounds
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;

    int rowDiff = std::abs(row - this->row);
    int colDiff = std::abs(col - this->col);

    // Check if it's a diagonal move
    if (rowDiff != colDiff) return false;

    // Check if path is clear
    if (!board.isPathClear(this->row, this->col, row, col)) return false;

    // Check if the destination square is occupied
    auto targetPiece = board.getPieceAt(row, col);
    if (targetPiece && targetPiece->getColor() == color) {
        return false; // Cannot capture a friendly piece
    }

    if (board.wouldLeaveKingInCheck(*this, row, col)) return false;

    return true;
}



void BishopPiece::moveTo(const int &row, const int &col, Board &board){
    if(!isValidMove(row, col, board)) throw invalidMoveException("Invalid move");
    
    board.capturePiece(row, col);

    board.movePiece(this->row, this->col, row, col);

    board.switchTurn();

    this->row = row;
    this->col = col;
}

ValidMoves BishopPiece::getValidMoves(const Board &board){
    
    ValidMoves validMoves;
    
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (isValidMove(r, c, board)) {
                validMoves.emplace_back(r, c);
            }
        }
    }
    return validMoves;
}

bool BishopPiece::isThreatening(const int &row, const int &col, const Board& board) const {
    if (std::abs(row - this->row) != std::abs(col - this->col)) return false;
    return board.isPathClear(this->row, this->col, row, col);
}
