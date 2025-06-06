#include "../include/PawnPiece.h"
#include "../include/Board.h"

PawnPiece::PawnPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

PawnPiece::~PawnPiece() = default;

bool PawnPiece::isValidMove(const int &row, const int &col, Board &board) {
    
    if(isSamePosition(row, col)) return false;

    if(isOutOfBoard(row, col)) return false;

    if(isOccupiedByTeamMate(row, col, board)) return false;

    if(!canCapturePiece(row, col, board) && !isForwardMove(row, col, board)) return false;
    
    if(board.wouldLeaveKingInCheck(*this, row, col)) return false;
    
    return true;
}

void PawnPiece::moveTo(const int &row, const int &col, Board &board){

    if(!isValidMove(row, col, board)) throw invalidMoveException("Invalid move");
    
    board.capturePiece(row, col);

    board.movePiece(this->row, this->col, row, col);

    board.switchTurn();

    this->row = row;
    this->col = col;
}

ValidMoves PawnPiece::getValidMoves(Board &board){
    
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

    // bool PawnPiece::isForwardMove(const int &row, const int &col) const {
    //     int direction = (color == "white") ? -1 : 1;       // White moves up, black moves down
    //     int startRow = (color == "white") ? 6 : 1;         // Starting row for white and black pawns

    //     int rowDiff = row - this->row;
    //     int colDiff = col - this->col;

    //     // Must move in same column (no sideways movement)
    //     if (colDiff != 0) return false;

    //     if (board.getPieceAt(row, col)) return false;

    //     // Single forward move
    //     if (rowDiff == direction) return true;

    //     // Double forward move on first move only
    //     if (this->row == startRow && rowDiff == 2 * direction) return true;

    //     return false;     

    // }   

    bool PawnPiece::isForwardMove(const int &row, const int &col, const Board &board) const {
        int direction = (color == "white") ? -1 : 1;       // White moves up, black moves down
        int startRow = (color == "white") ? 6 : 1;         // Starting row for white and black pawns

        int rowDiff = row - this->row;
        int colDiff = col - this->col;

        // Must move in same column (no sideways movement)
        if (colDiff != 0) return false;

        // Cannot move forward into an occupied square
        if (board.getPieceAt(row, col)) return false;

        // Single forward move
        if (rowDiff == direction) return true;

        // Double forward move on first move only
        if (this->row == startRow && rowDiff == 2 * direction) {
            int intermediateRow = this->row + direction;
            if (!board.getPieceAt(intermediateRow, col)) {
                return true;
            }
    }

    return false;
}


bool PawnPiece::canCapturePiece(const int &row, const int &col, const Board &board) const {
    int direction = (color == "white") ? -1 : 1;  // White moves up, black moves down

    int rowDiff = row - this->row;
    int colDiff = col - this->col;

    // Must be moving diagonally forward by one square
    if (rowDiff != direction || std::abs(colDiff) != 1) return false;

    auto target = board.getPieceAt(row, col);
    if (target && target->getColor() != this->color) {
        return true;  // Valid capture
    }

    return false;
}