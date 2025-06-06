#ifndef PAWN_PIECE_H
#define PAWN_PIECE_H

#include "ChessPiece.h"

class PawnPiece : public ChessPiece{

    bool isFirstMove = true;
    
public:

    inline static const int value = 1;
    

    PawnPiece() = delete;
    PawnPiece(int row, int col, std::string color);
    ~PawnPiece() noexcept;

    bool isValidMove(const int &row, const int &col, Board &board) override;
    bool NewFunction(const int &row, const int &col, const Board &board, int dir, int startRow, bool &retFlag);
    void moveTo(const int &row, const int& col, Board &board) override;
    ValidMoves getValidMoves(Board &board) override;


private:
    // bool isForwardMove(const int &row, const int &col) const;
    bool isForwardMove(const int &row, const int &col, const Board &board) const;
    bool canCapturePiece(const int &row, const int &col, const Board &board) const;
};


#endif //  PAWN_PIECE_H