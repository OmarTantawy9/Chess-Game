#include "../include/BoardGUI.h"

int main() {

    std::unique_ptr<BoardGUI> boardGUI = std::make_unique<BoardGUI>();

    while(boardGUI->display()){
        boardGUI = std::make_unique<BoardGUI>();
    }

    return 0;
}