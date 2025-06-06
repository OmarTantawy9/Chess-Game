#include "../include/RookPiece.h"
#include "../include/Board.h"

RookPiece::RookPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

RookPiece::~RookPiece() = default;

bool RookPiece::isValidMove(const int &row, const int &col, Board &board) {

    if (isSamePosition(row, col)) return false; // No movement

    // Ensure the move is within the board bounds
    if (isOutOfBoard(row, col)) return false;

    // Rook moves only in a straight line (either same row or same column)
    if (!isStarightMove(row, col)) return false;

    // Check if path is clear (no pieces in the way)
    if (!board.isPathClear(this->row, this->col, row, col)) return false;

    // Check if the destination square is occupied
    auto targetPiece = board.getPieceAt(row, col);
    if (isOccupiedByTeamMate(row, col, board)) return false;  // Cannot capture a friendly piece

    if (board.wouldLeaveKingInCheck(*this, row, col)) return false;

    return true;
}

void RookPiece::moveTo(const int &row, const int &col, Board &board) {

    if(!isValidMove(row, col, board)) throw invalidMoveException("Invalid move");
    
    board.capturePiece(row, col);

    board.movePiece(this->row, this->col, row, col);

    board.switchTurn();

    this->row = row;
    this->col = col;
}


ValidMoves RookPiece::getValidMoves(Board &board){
    
    ValidMoves validMoves;
    
    static const int directions[4][2] = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}  // Up, Down, Left, Right
    };

    for (const auto &dir : directions) {
        int newRow = this->row + dir[0];
        int newCol = this->col + dir[1];

        while (newRow >= 0 && newRow < 8 && newCol >= 0 && newCol < 8) {
            if (isValidMove(newRow, newCol, board)) {
                validMoves.emplace_back(newRow, newCol);
            } else {
                break;  // Stop if the move is invalid (blocked or out of bounds)
            }

            newRow += dir[0];
            newCol += dir[1];
        }
    }
    
    return validMoves;
}