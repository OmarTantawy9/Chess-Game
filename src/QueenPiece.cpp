#include "../include/QueenPiece.h"
#include "../include/Board.h"

QueenPiece::QueenPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

QueenPiece::~QueenPiece() = default;

bool QueenPiece::isValidMove(const int &row, const int &col, const Board &board) {

    if (row == this->row && col == this->col) return false; // No movement

    // Ensure the move is within the board bounds
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;

    int rowDiff = std::abs(row - this->row);
    int colDiff = std::abs(col - this->col);

    // Check if it's a valid queen move (straight-line or diagonal)
    bool isStraightMove = (row == this->row || col == this->col);
    bool isDiagonalMove = (rowDiff == colDiff);

    if (!isStraightMove && !isDiagonalMove) return false;

    // Check if path is clear
    if (!board.isPathClear(this->row, this->col, row, col)) return false;

    // Check if the destination square is occupied
    auto targetPiece = board.getPieceAt(row, col);
    if (targetPiece && targetPiece->getColor() == color) {
        return false; // Cannot capture a friendly piece
    }

    return true;
    
}

void QueenPiece::moveTo(const int &row, const int &col, Board &board){

    if(!isValidMove(row, col, board)) throw invalidMoveException("Invalid move");
    
    board.capturePiece(row, col);

    board.movePiece(this->row, this->col, row, col);

    board.switchTurn();

    this->row = row;
    this->col = col;
}


ValidMoves QueenPiece::getValidMoves(const Board &board){
    
    ValidMoves validMoves;
    
    static const int directions[8][2] = {
        {-1,  0}, {1,  0}, {0, -1}, {0,  1},  // Up, Down, Left, Right (Rook moves)
        {-1, -1}, {-1, 1}, {1, -1}, {1,  1}   // Diagonals (Bishop moves)
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