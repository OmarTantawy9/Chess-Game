#include "../include/PawnPiece.h"
#include "../include/Board.h"

PawnPiece::PawnPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

PawnPiece::~PawnPiece() = default;

bool PawnPiece::isValidMove(const int &row, const int &col, const Board &board) {
    int dir = (color == "white") ? -1 : 1;
    int startRow = (color == "white") ? 6 : 1;

    if (row < 0 || row > 7 || col < 0 || col > 7 || (row == this->row && col == this->col)) return false;

    int rowDiff = row - this->row;
    int colDiff = col - this->col;

    auto forwardOne = board.getPieceAt(row, col);
    auto forwardTwo = board.getPieceAt(this->row + dir, col);

    // Normal forward
    if (colDiff == 0 && rowDiff == dir && !forwardOne) {
        return !board.wouldLeaveKingInCheck(*this, row, col);
    }

    // Double move
    if (colDiff == 0 && rowDiff == 2 * dir && this->row == startRow &&
        !forwardTwo && !forwardOne) {
        return !board.wouldLeaveKingInCheck(*this, row, col);
    }

    // Capture
    if (std::abs(colDiff) == 1 && rowDiff == dir) {
        auto target = board.getPieceAt(row, col);
        if (target && target->getColor() != color) {
            return !board.wouldLeaveKingInCheck(*this, row, col);
        }

        // // En Passant
        // if (board.isEnPassantPossible(this->row, this->col, row, col)) {
        //     return true;
        // }
    }

    return false;
}


// // En Passant (special capture)
    // if (std::abs(colDiff) == 1 && rowDiff == direction) {
    //     if (board.isEnPassantMove(this->row, this->col, row, col, this->color)) {
    //         return true;
    //     }
    // }

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

bool PawnPiece::isThreatening(const int &row, const int &col, const Board& board) const {
    int dir = (this->color == "white") ? -1 : 1;
    return (row == this->row + dir) && (std::abs(col - this->col) == 1);
}

