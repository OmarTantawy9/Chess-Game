#ifndef PAWN_PIECE_H
#define PAWN_PIECE_H

#include "ChessPiece.h"

class PawnPiece : public ChessPiece{
public:

    PawnPiece() = delete;
    PawnPiece(int row, int col, char symbol, std::string color);
    ~PawnPiece() noexcept;


    bool isValidMove(const int &row, const int &col) override;
    void moveTo(const int &row, const int& col) override;
};


#endif //  PAWN_PIECE_H