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
    bool isThreatening(const int &row, const int &col, const Board& board) const override;
    void moveTo(const int &row, const int& col, Board &board) override;
    ValidMoves getValidMoves(const Board &board) override;

};



#endif // !KNIGHT_PIECE_H