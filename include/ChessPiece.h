#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <string>

class ChessPiece {

protected:
    int row;
    int col;
    char symbol;
    std::string color;
    
    public:
    ChessPiece() = delete;
    ChessPiece(int row, int col, char symbol, std::string color);
    virtual ~ChessPiece() noexcept;

    virtual bool isValidMove(const int &row, const int &col) = 0;
    virtual void moveTo(const int &row, const int &col) = 0;
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