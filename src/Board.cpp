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

    whiteKing = board[7][4];
    blackKing = board[0][4];

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

    int rowStep = (endRow > startRow) ? 1 : (endRow < startRow) ? -1 : 0;
    int colStep = (endCol > startCol) ? 1 : (endCol < startCol) ? -1 : 0;

    int currRow = startRow + rowStep;
    int currCol = startCol + colStep;

    while (currRow != endRow || currCol != endCol) {

        if (board[currRow][currCol]) {
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



bool Board::wouldLeaveKingInCheck(ChessPiece &piece, int newRow, int newCol) {

    auto capturedPiece = getPieceAt(newRow, newCol);

    auto oldRow = piece.getRow();
    auto oldCol = piece.getCol();

    auto king = getKing(piece.getColor());

    board[newRow][newCol] = board[oldRow][oldCol];
    board[oldRow][oldCol] = nullptr;

    piece.setRow(newRow);
    piece.setCol(newCol);

    auto isInCheckFlag = isInCheck(king);

    piece.setRow(oldRow);
    piece.setCol(oldCol);
    
    board[oldRow][oldCol] = board[newRow][newCol];
    board[newRow][newCol] = capturedPiece;


    return isInCheckFlag;
}

bool Board::isInCheck(const ChessPiecePtr &king) {


    auto nextTurnColor = king->getColor() == "white" ? "black" : "white";

    for(const auto &row : board) {
        for(const auto &piece : row) {
            if(!piece) continue;
            if(piece->getColor() != nextTurnColor) continue;
            
            auto validMoves = piece->getValidMoves(*this);
            
            auto inCheckMove = std::find_if(validMoves.begin(), validMoves.end(), [&king](const auto &p) {
                return king->getRow() == p.first && king->getCol() == p.second;
            });

            if(inCheckMove != validMoves.end()){
                std::cout << "Check!!!" << std::endl;
                return true;
            }
        }
    }

    return false;
}

bool Board::isGameOver() {
    // Get the current player's king
    auto king = isWhiteTurn ? whiteKing : blackKing;

    // Check if the king is in check
    if (!isInCheck(king)) {
        return false;  // Not in check, game continues
    }

    // Get all pieces of the current player
    for (const auto &row : board) {
        for (const auto &piece : row) {
            if (!piece || piece->getColor() != king->getColor()) {
                continue;
            }

            // Get all valid moves for this piece
            auto validMoves = piece->getValidMoves(*this);

            // If there's at least one valid move that gets out of check, it's not checkmate
            if (!validMoves.empty()) {
                return false;
            }
        }
    }

    // If we get here, no piece can make a valid move to get out of check - it's checkmate
    winner = isWhiteTurn ? "Black Player" : "White Player";
    return true;
}

// ChessPiecePtr Board::findKing(const std::string &kingColor) const {
//     for (const auto &pieces : board) {
//         for(const auto &piece : pieces){
//             if(piece && piece->getColor() == kingColor && typeid(*piece) == typeid(KingPiece)){
//                 return piece;
//             }
//         }
//     }
//     std::cerr << "didnt find king" << std::endl;
//     return {};
// }