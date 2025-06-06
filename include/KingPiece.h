#ifndef KING_PIECE_H
#define KING_PIECE_H

#include "ChessPiece.h"

class KingPiece : public ChessPiece{
public:

    inline static const int value = 100;

    KingPiece() = delete;
    KingPiece(int row, int col, std::string color);
    ~KingPiece() noexcept;

    bool isValidMove(const int &row, const int &col, Board &board) override;
    void moveTo(const int &row, const int& col, Board &board) override;
    ValidMoves getValidMoves(Board &board) override;

private:
    inline bool isOneSquareOffset(const int &row, const int &col) const {
        int rowDiff = std::abs(row - this->row);
        int colDiff = std::abs(col - this->col);

        return rowDiff <= 1 && colDiff <= 1;
    }

};


#endif //  KING_PIECE_HK