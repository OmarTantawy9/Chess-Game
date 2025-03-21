#ifndef BISHOP_PIECE_H
#define BISHOP_PIECE_H

#include "ChessPiece.h"

class BishopPiece : public ChessPiece{
public:

    inline static const int value = 3;


    BishopPiece() = delete;
    BishopPiece(int row, int col, std::string color);
    ~BishopPiece() noexcept;

    bool isValidMove(const int &row, const int &col, const Board &board) override;
    void moveTo(const int &row, const int& col, Board &board) override;
};


#endif //  BISHOP_PIECE_H