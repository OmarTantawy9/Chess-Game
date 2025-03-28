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
    
    public:
    ChessPiece() = delete;
    ChessPiece(int row, int col, std::string color);
    virtual ~ChessPiece() noexcept;

    virtual bool isValidMove(const int &row, const int &col, const Board &board) = 0;
    virtual void moveTo(const int &row, const int &col, Board &board) = 0;
    virtual ValidMoves getValidMoves(const Board &board) = 0; 

    std::string getColor(){
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