#include "../include/Board.h"

#include "../include/KingPiece.h"
#include "../include/QueenPiece.h"
#include "../include/RookPiece.h"
#include "../include/BishopPiece.h"
#include "../include/KnightPiece.h"
#include "../include/PawnPiece.h"

#include <iostream>

Board::Board() : board(8, std::vector<ChessPiecePtr>(8)), isWhiteTurn(true), isGameOverFlag(false), winner() {


    board[0][0] = std::make_shared<RookPiece>  (0, 0, "black");
    board[0][7] = std::make_shared<RookPiece>  (0, 7, "black");
    board[0][1] = std::make_shared<KnightPiece>(0, 1, "black");
    board[0][6] = std::make_shared<KnightPiece>(0, 6, "black");
    board[0][2] = std::make_shared<BishopPiece>(0, 2, "black");
    board[0][5] = std::make_shared<BishopPiece>(0, 5, "black");
    board[0][3] = std::make_shared<QueenPiece> (0, 3, "black");
    board[0][4] = std::make_shared<KingPiece>  (0, 4, "black");

    for(int col = 0; col < 8 ; ++col){
        board[1][col] = std::make_shared<PawnPiece>(1, col , "black");
        board[6][col] = std::make_shared<PawnPiece>(6, col , "white");
    }

    board[7][0] = std::make_shared<RookPiece>  (7, 0, "white");
    board[7][7] = std::make_shared<RookPiece>  (7, 7, "white");
    board[7][1] = std::make_shared<KnightPiece>(7, 1, "white");
    board[7][6] = std::make_shared<KnightPiece>(7, 6, "white");
    board[7][2] = std::make_shared<BishopPiece>(7, 2, "white");
    board[7][5] = std::make_shared<BishopPiece>(7, 5, "white");
    board[7][3] = std::make_shared<QueenPiece> (7, 3, "white");
    board[7][4] = std::make_shared<KingPiece>  (7, 4, "white");

};

Board::~Board() = default;

void Board::capturePiece(int row, int col){

    if(!board[row][col]) return;

    if(typeid(*board[row][col]) == typeid(KingPiece)){
        isGameOverFlag = true;
        winner = board[row][col]->getColor() == "white" ? "Black Player" : "White Player"; 
    }

    if(board[row][col]->getColor() == "black"){
        blackGraveYard.push_back(std::move(board[row][col]));
     }else {
          whiteGraveYard.push_back(std::move(board[row][col]));
    }
}


bool Board::isPathClear(int startRow, int startCol, int endRow, int endCol) const {

    if (startRow == endRow && startCol == endCol) return false; // Same position

    int rowStep = (endRow > startRow) ? 1 : (endRow < startRow) ? -1 : 0;
    int colStep = (endCol > startCol) ? 1 : (endCol < startCol) ? -1 : 0;

    int currRow = startRow + rowStep;
    int currCol = startCol + colStep;

    while (currRow != endRow || currCol != endCol) {

        if (getPieceAt(currRow, currCol)) {
            return false;  // Path is blocked
        }

        currRow += rowStep;
        currCol += colStep;

        // Ensure we stop properly for straight-line movements
        if ((rowStep == 0 && currCol == endCol) || (colStep == 0 && currRow == endRow)) {
            break;
        }
    }

    return true;
}

bool Board::isUnderAttack(int row, int col, const std::string &color) const {
    for (const auto &pieces : board) {
        for(const auto &piece : pieces){
            if (piece && piece->getColor() == color && piece->isThreatening(row, col, *this)) {
                return true;
            }
        }
    }
    return false;
}

bool Board::wouldLeaveKingInCheck(const ChessPiece &piece, int newRow, int newCol) const {
    
    auto tempBoard = *this;

    auto oldRow = piece.getRow();
    auto oldCol = piece.getCol();

    auto capturedPiece = tempBoard.board[newRow][newCol];
    tempBoard.board[newRow][newCol] = tempBoard.board[oldRow][oldCol];

    auto king = findKing(piece.getColor());

    auto res = tempBoard.isUnderAttack(king->getRow(), king->getCol(), king->getColor());

    tempBoard.board[oldRow][oldCol] = tempBoard.board[newRow][newCol];
    
    tempBoard.board[newRow][newCol] = capturedPiece;

    return res;
}

ChessPiecePtr Board::findKing(const std::string &kingColor) const {
    for (const auto &pieces : board) {
        for(const auto &piece : pieces){
            if(piece && piece->getColor() == kingColor && typeid(*piece) == typeid(KingPiece)){
                return piece;
            }
        }
    }
    return {};
}