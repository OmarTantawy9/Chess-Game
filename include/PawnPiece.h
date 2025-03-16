#ifndef PAWN_PIECE_H
#define PAWN_PIECE_H

#include "ChessPiece.h"

class PawnPiece : public ChessPiece{
    
public:

    inline static const int value = 1;

    PawnPiece() = delete;
    PawnPiece(int row, int col, std::string color);
    ~PawnPiece() noexcept;


    bool isValidMove(const int &row, const int &col, const Board &board) override;
    void moveTo(const int &row, const int& col) override;
};


#endif //  PAWN_PIECE_H