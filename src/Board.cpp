#include "../include/Board.h"

#include "../include/KingPiece.h"
#include "../include/QueenPiece.h"
#include "../include/RookPiece.h"
#include "../include/BishopPiece.h"
#include "../include/KnightPiece.h"
#include "../include/PawnPiece.h"

Board::Board() : board(8, std::vector<ChessPiecePtr>(8)) {

    board[0][0] = std::make_shared<RookPiece> (0, 0, "black");
    board[0][7] = std::make_shared<RookPiece> (0, 7, "black");
    board[0][1] = std::make_shared<KnightPiece> (0, 1, "black");
    board[0][6] = std::make_shared<KnightPiece> (0, 6, "black");
    board[0][2] = std::make_shared<BishopPiece> (0, 2, "black");
    board[0][5] = std::make_shared<BishopPiece> (0, 5, "black");
    board[0][3] = std::make_shared<QueenPiece>(0, 3, "black");
    board[0][4] = std::make_shared<KingPiece>(0, 4, "black");

    for(int col = 0; col < 8 ; ++col){
        board[1][col] = std::make_shared<PawnPiece>(1, col , "black");
        board[6][col] = std::make_shared<PawnPiece>(6, col , "white");
    }

    board[7][0] = std::make_shared<RookPiece>(7, 0, "white");
    board[7][7] = std::make_shared<RookPiece>(7, 7, "white");
    board[7][1] = std::make_shared<KnightPiece>(7, 1, "white");
    board[7][6] = std::make_shared<KnightPiece>(7, 6, "white");
    board[7][2] = std::make_shared<BishopPiece>(7, 2, "white");
    board[7][5] = std::make_shared<BishopPiece>(7, 5, "white");
    board[7][3] = std::make_shared<QueenPiece>(7, 3, "white");
    board[7][4] = std::make_shared<KingPiece>(7, 4, "white");

};

Board::~Board() = default;

void Board::capturePiece(int row, int col){
    if(board[row][col]->getColor() == "black"){
        blackGraveYard.push_back(std::move(board[row][col]));
     }else {
          whiteGraveYard.push_back(std::move(board[row][col]));
    }
}
bool Board::isPathClear(int startRow, int startCol, int endRow, int endCol) const {
    int rowStep = (endRow > startRow) ? 1 : -1;
    int colStep = (endCol > startCol) ? 1 : -1;

    int currRow = startRow + rowStep;
    int currCol = startCol + colStep;

    while (currRow != endRow || currCol != endCol) {
        if(getPieceAt(currRow, currCol).lock()) {
            return false;  // Path is blocked
        }
        currRow += rowStep;
        currCol += colStep;
    }

    return true;
}