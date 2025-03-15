#ifndef QUEEN_PIECE_H
#define QUEEN_PIECE_H

#include "ChessPiece.h"

class QueenPiece : public ChessPiece{
public:

    QueenPiece() = delete;
    QueenPiece(int row, int col, char symbol, std::string color);
    ~QueenPiece() noexcept;

    bool isValidMove(const int &row, const int &col) override;
    void moveTo(const int &row, const int& col) override;
};


#endif //  QUEEN_PIECE_H