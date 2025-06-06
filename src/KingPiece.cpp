#include "../include/KingPiece.h"
#include "../include/Board.h"


KingPiece::KingPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

KingPiece::~KingPiece() = default;

bool KingPiece::isValidMove(const int &row, const int &col, Board &board) {

    // Board bounds
    if(isOutOfBoard(row, col)) return false;

    if(!isOneSquareOffset(row, col)) return false;

    if(isOccupiedByTeamMate(row, col, board)) return false;

    if(board.wouldLeaveKingInCheck(*this, row, col)) return false;

    return true;
}

void KingPiece::moveTo(const int &row, const int &col, Board &board) {

    if(!isValidMove(row, col, board)) throw invalidMoveException("Invalid move");
    
    board.capturePiece(row, col);

    board.movePiece(this->row, this->col, row, col);

    board.switchTurn();

    this->row = row;
    this->col = col;
}

ValidMoves KingPiece::getValidMoves(Board &board){
    
    ValidMoves validMoves;

    static const int directions[8][2] = {
        {-1,  0}, {1,  0}, {0, -1}, {0,  1},  // Up, Down, Left, Right
        {-1, -1}, {-1, 1}, {1, -1}, {1,  1}   // Diagonals
    };

    for (const auto &dir : directions) {
        int newRow = this->row + dir[0];
        int newCol = this->col + dir[1];

        if (isValidMove(newRow, newCol, board)) {
            validMoves.emplace_back(newRow, newCol);
        }
    }
    
    return validMoves;
}