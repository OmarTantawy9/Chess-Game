#ifndef KNIGHT_PIECE_H
#define KNIGHT_PIECE_H

#include "ChessPiece.h"

class KnightPiece : public ChessPiece {
public:

    inline static const int value = 3;


    KnightPiece() = delete;
    KnightPiece(int row, int col, std::string color);
    ~KnightPiece() noexcept;

    bool isValidMove(const int &row, const int &col, Board &board) override;
    void moveTo(const int &row, const int& col, Board &board) override;
    ValidMoves getValidMoves(Board &board) override;


private:
    inline bool isLShapeMove(const int &row, const int &col) const {
        int rowDiff = std::abs(row - this->row);
        int colDiff = std::abs(col - this->col);

        return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
    }

};



#endif // !KNIGHT_PIECE_H