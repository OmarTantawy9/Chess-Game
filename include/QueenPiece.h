#ifndef QUEEN_PIECE_H
#define QUEEN_PIECE_H

#include "ChessPiece.h"

class QueenPiece : public ChessPiece{
public:

    inline static const int value = 9;


    QueenPiece() = delete;
    QueenPiece(int row, int col, std::string color);
    ~QueenPiece() noexcept;

    bool isValidMove(const int &row, const int &col, const Board &board) override;
    bool isThreatening(const int &row, const int &col, const Board& board) const override;
    void moveTo(const int &row, const int& col, Board &board) override;
    ValidMoves getValidMoves(const Board &board) override;
};


#endif //  QUEEN_PIECE_H