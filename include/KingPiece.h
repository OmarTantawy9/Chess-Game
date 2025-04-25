#ifndef KING_PIECE_H
#define KING_PIECE_H

#include "ChessPiece.h"

class KingPiece : public ChessPiece{
public:

    inline static const int value = 100;

    KingPiece() = delete;
    KingPiece(int row, int col, std::string color);
    ~KingPiece() noexcept;

    bool isValidMove(const int &row, const int &col, const Board &board) override;
    bool isThreatening(const int &row, const int &col, const Board& board) const override;
    void moveTo(const int &row, const int& col, Board &board) override;
    ValidMoves getValidMoves(const Board &board) override;

};


#endif //  KING_PIECE_HK