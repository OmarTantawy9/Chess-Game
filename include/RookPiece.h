#ifndef ROOK_PIECE_H
#define ROOK_PIECE_H

#include "ChessPiece.h"

class RookPiece : public ChessPiece{
public:

    RookPiece() = delete;
    RookPiece(int row, int col, char symbol, std::string color);
    ~RookPiece() noexcept;


    bool isValidMove(const int &row, const int &col) override;
    void moveTo(const int &row, const int& col) override;
};


#endif //  ROOK_PIECE_H