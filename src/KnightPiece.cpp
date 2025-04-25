#include "../include/KnightPiece.h"
#include "../include/Board.h"

KnightPiece::KnightPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

KnightPiece::~KnightPiece() = default;

bool KnightPiece::isValidMove(const int &row, const int &col, const Board &board) {

    if (row == this->row && col == this->col) return false; // No movement

    // Ensure the move is within the board bounds
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;

    int rowDiff = std::abs(row - this->row);
    int colDiff = std::abs(col - this->col);

    // Check if move follows the L-shape pattern
    bool isLShape = (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    if (!isLShape) return false;

    // Check if the destination square is occupied
    auto targetPiece = board.getPieceAt(row, col);
    if (targetPiece && targetPiece->getColor() == color) {
        return false; // Cannot capture a friendly piece
    }

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

ValidMoves KnightPiece::getValidMoves(const Board &board){
    
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

bool KnightPiece::isThreatening(const int &row, const int &col, const Board& board) const {
    int rowDiff = std::abs(row - this->row);
    int colDiff = std::abs(col - this->col);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}
