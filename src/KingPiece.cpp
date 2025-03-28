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
    if (targetPiece && targetPiece->getColor() == color) {
        return false; // Cannot capture a friendly piece
    }

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

ValidMoves KingPiece::getValidMoves(const Board &board){
    
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