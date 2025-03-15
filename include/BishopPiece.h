#ifndef BISHOP_PIECE_H
#define BISHOP_PIECE_H

#include "ChessPiece.h"

class BishopPiece : public ChessPiece{
public:

    BishopPiece() = delete;
    BishopPiece(int row, int col, char symbol, std::string color);
    ~BishopPiece() noexcept;

    bool isValidMove(const int &row, const int &col) override;
    void moveTo(const int &row, const int& col) override;
};


#endif //  BISHOP_PIECE_H