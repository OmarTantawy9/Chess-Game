#include "../include/KingPiece.h"
#include "../include/Board.h"


KingPiece::KingPiece(int row, int col, std::string color) 
    : ChessPiece(row, col, color) {}

KingPiece::~KingPiece() = default;

bool KingPiece::isValidMove(const int &row, const int &col, const Board &board) {

    // Board bounds
    if (row < 0 || row > 7 || col < 0 || col > 7)
        return false;

    int rowDiff = std::abs(row - this->row);
    int colDiff = std::abs(col - this->col);

    auto target = board.getPieceAt(row, col);
    if (target && target->getColor() == color)
        return false; // Can't capture own piece

    std::string opponentColor = (color == "white") ? "black" : "white";

    // 1-square move
    if ((rowDiff <= 1 && colDiff <= 1) && !(rowDiff == 0 && colDiff == 0)) {
        if (board.isUnderAttack(row, col, opponentColor)) return false;
        if (board.wouldLeaveKingInCheck(*this, row, col)) return false;
        return true;
    }

    // Castling logic
    if (row == this->row && (col == 2 || col == 6)) {
        bool isKingside = col == 6;
        bool isQueenside = col == 2;

        // 1. Can we castle?
        // if (!board.canCastle(color, isKingside ? "king" : "queen")) return false;

        // 2. Path must be clear
        int step = isKingside ? 1 : -1;
        for (int c = this->col + step; c != col + step; c += step) {
            if (board.getPieceAt(row, c) != nullptr) return false;
        }

        // 3. Squares must not be under attack (including current, through, and destination)
        for (int c : {this->col, this->col + step, col}) {
            if (board.isUnderAttack(row, c, opponentColor)) return false;
        }

        return true;
    }

    return false;
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

bool KingPiece::isThreatening(const int &row, const int &col, const Board& board) const {
    int rowDiff = std::abs(row - this->row);
    int colDiff = std::abs(col - this->col);
    return rowDiff <= 1 && colDiff <= 1 && !(rowDiff == 0 && colDiff == 0);
}
