#ifndef ROOK_PIECE_H
#define ROOK_PIECE_H

#include "ChessPiece.h"

class RookPiece : public ChessPiece{
public:

    inline static const int value = 5;


    RookPiece() = delete;
    RookPiece(int row, int col, std::string color);
    ~RookPiece() noexcept;


    bool isValidMove(const int &row, const int &col, const Board &board) override;
    void moveTo(const int &row, const int& col, Board &board) override;
};


#endif //  ROOK_PIECE_H