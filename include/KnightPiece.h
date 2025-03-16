#ifndef KNIGHT_PIECE_H
#define KNIGHT_PIECE_H

#include "ChessPiece.h"

class KnightPiece : public ChessPiece {
public:

    inline static const int value = 3;


    KnightPiece() = delete;
    KnightPiece(int row, int col, std::string color);
    ~KnightPiece() noexcept;

    bool isValidMove(const int &row, const int &col, const Board &board) override;
    void moveTo(const int &row, const int& col) override;
};



#endif // !KNIGHT_PIECE_H