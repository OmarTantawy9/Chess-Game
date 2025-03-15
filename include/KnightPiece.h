#ifndef KNIGHT_PIECE_H
#define KNIGHT_PIECE_H

#include "ChessPiece.h"

class KnightPiece : public ChessPiece {
public:

    KnightPiece() = delete;
    KnightPiece(int row, int col, char symbol, std::string color);
    ~KnightPiece() noexcept;

    bool isValidMove(const int &row, const int &col) override;
    void moveTo(const int &row, const int& col) override;
};



#endif // !KNIGHT_PIECE_H