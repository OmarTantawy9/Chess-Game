#ifndef KING_PIECE_H
#define KING_PIECE_H

#include "ChessPiece.h"

class KingPiece : public ChessPiece{
public:

    KingPiece() = delete;
    KingPiece(int row, int col, char symbol, std::string color);
    ~KingPiece() noexcept;

    bool isValidMove(const int &row, const int &col) override;
    void moveTo(const int &row, const int& col) override;
};


#endif //  KING_PIECE_HK