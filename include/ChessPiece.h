#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <string>
#include <vector>
#include <utility>

using ValidMoves = std::vector<std::pair<int, int>>;

class Board;

class ChessPiece {

protected:
    int row;
    int col;
    std::string color;

    inline bool isSamePosition(const int &row, const int &col) const {
        return this->row == row && this->col == col;
    }

    inline bool isOutOfBoard(const int &row, const int &col) const {
        return row < 0 || row > 7 || col < 0 || col > 7;
    }

    inline bool isStarightMove(const int &row, const int &col) const {
        return this->row == row || this->col == col;
    }

    inline bool isDiagonalMove(const int &row, const int &col) const {
        int rowDiff = std::abs(row - this->row);
        int colDiff = std::abs(col - this->col);

        return rowDiff == colDiff;
    }

    bool isOccupiedByTeamMate(const int &row, const int &col, const Board &board) const;
    
    public:
    ChessPiece() = delete;
    ChessPiece(int row, int col, std::string color);
    virtual ~ChessPiece() noexcept;

    virtual bool isValidMove(const int &row, const int &col, Board &board) = 0;
    virtual void moveTo(const int &row, const int &col, Board &board) = 0;
    virtual ValidMoves getValidMoves(Board &board) = 0; 

    inline int getRow() const {return row;}
    inline int getCol() const {return col;}

    inline void setRow(const int& row) {this->row = row;}
    inline void setCol(const int& col) {this->col = col;}
    std::string getColor() const{
        return color;
    }

};

class invalidMoveException : public std::exception {
    std::string message;
public:
    invalidMoveException(std::string message) : message(message) {}

    const char* what() const noexcept override{
        return message.c_str();
    }
};


#endif //  CHESS_PIECE_H