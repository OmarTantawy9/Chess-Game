#include "../include/PawnPiece.h"
#include "../include/Board.h"

PawnPiece::PawnPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

PawnPiece::~PawnPiece() = default;

bool PawnPiece::isValidMove(const int &row, const int &col, const Board &board) {
    int direction = (this->color == "white") ? -1 : 1;  // White moves up (-1), Black moves down (+1)
    int startRow = (this->color == "white") ? 6 : 1;    // White starts at row 6, Black at row 1

    if (row == this->row && col == this->col) return false; // No movement

    // Ensure move is within board bounds
    if (row < 0 || row > 7 || col < 0 || col > 7) return false;

    int rowDiff = row - this->row;
    int colDiff = col - this->col;

    // Normal forward move (one square)
    if (colDiff == 0 && rowDiff == direction && !board.getPieceAt(row, col)) {
        return true;
    }

    // First move: Two squares forward
    if (colDiff == 0 && rowDiff == 2 * direction && this->row == startRow &&
        !board.getPieceAt(this->row + direction, col) &&
        !board.getPieceAt(row, col)) {
        return true;
    }

    // Capture move (diagonal)
    if (std::abs(colDiff) == 1 && rowDiff == direction) {
        auto targetPiece = board.getPieceAt(row, col);
        if (targetPiece && targetPiece->getColor() != color) {
            return true;  // Can capture enemy piece
        }
    }

    // // En Passant (special capture)
    // if (std::abs(colDiff) == 1 && rowDiff == direction) {
    //     if (board.isEnPassantMove(this->row, this->col, row, col, this->color)) {
    //         return true;
    //     }
    // }

    return false;
}

void PawnPiece::moveTo(const int &row, const int &col, Board &board){

    if(!isValidMove(row, col, board)) throw invalidMoveException("Invalid move");
    
    board.capturePiece(row, col);

    board.movePiece(this->row, this->col, row, col);

    board.switchTurn();

    this->row = row;
    this->col = col;
}

ValidMoves PawnPiece::getValidMoves(const Board &board){
    
    ValidMoves validMoves;
    
    static const int whiteMoves[4][2] = {{-1, 0}, {-2, 0}, {-1, -1}, {-1, 1}};
    static const int blackMoves[4][2] = {{1, 0}, {2, 0}, {1, -1}, {1, 1}};

    const int (*moves)[2] = (color == "white") ? whiteMoves : blackMoves;

    for (int i = 0; i < 4; ++i) {
        int newRow = this->row + moves[i][0];
        int newCol = this->col + moves[i][1];

        if (isValidMove(newRow, newCol, board)) {
            validMoves.emplace_back(newRow, newCol);
        }
    }


    return validMoves;
}
