#include "../include/BishopPiece.h"
#include "../include/Board.h"

BishopPiece::BishopPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

BishopPiece::~BishopPiece() = default;

bool BishopPiece::isValidMove(const int &row, const int &col, Board &board) {

    if (isSamePosition(row, col)) return false; // No movement

    // Ensure move is within board bounds
    if (isOutOfBoard(row, col)) return false;

    // Check if it's a diagonal move
    if (!isDiagonalMove(row, col)) return false;

    // Check if path is clear
    if (!board.isPathClear(this->row, this->col, row, col)) return false;

    // Check if the destination square is occupied by friendly piece
    if (isOccupiedByTeamMate(row, col, board)) return false;
    
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

ValidMoves BishopPiece::getValidMoves(Board &board){
    
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


