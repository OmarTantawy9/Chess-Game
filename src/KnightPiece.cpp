#include "../include/KnightPiece.h"
#include "../include/Board.h"

KnightPiece::KnightPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

KnightPiece::~KnightPiece() = default;

bool KnightPiece::isValidMove(const int &row, const int &col, Board &board) {

    if (isSamePosition(row, col)) return false; // No movement

    // Ensure the move is within the board bounds
    if (isOutOfBoard(row, col)) return false;

    // Check if move follows the L-shape pattern
    if(!isLShapeMove(row, col)) return false;

    // Check if the destination square is occupied
    if (isOccupiedByTeamMate(row, col, board)) return false;
    
    if (board.wouldLeaveKingInCheck(*this, row, col)) return false;

    return true;
}

void KnightPiece::moveTo(const int &row, const int &col, Board &board){
    
    if(!isValidMove(row, col, board)) throw invalidMoveException("Invalid move");
    
    board.capturePiece(row, col);

    board.movePiece(this->row, this->col, row, col);

    board.switchTurn();

    this->row = row;
    this->col = col;
}

ValidMoves KnightPiece::getValidMoves(Board &board){
    
    ValidMoves validMoves;

    static const int moves[8][2] = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},  // Vertical moves
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}   // Horizontal moves
    };

    for (const auto &move : moves) {
        int newRow = this->row + move[0];
        int newCol = this->col + move[1];

        if (isValidMove(newRow, newCol, board)) {
            validMoves.emplace_back(newRow, newCol);
        }
    }

    return validMoves;
}
