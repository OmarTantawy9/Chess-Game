#include "../include/ChessPiece.h"
#include "../include/BoardGUI.h"
#include "../include/PawnPiece.h"
#include "../include/Board.h"

#include <iostream>

int main() {

    std::unique_ptr<BoardGUI> boardGUI = std::make_unique<BoardGUI>();

    while(boardGUI->display()){
        boardGUI = std::make_unique<BoardGUI>();
    }

    return 0;
}