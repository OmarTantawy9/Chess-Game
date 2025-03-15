#ifndef BOARD_GUI_H
#define BOARD_GUI_H

#include <SFML/Graphics.hpp>
#include <unordered_map>


class BoardGUI {

    // Chessboard size
    inline static const int BOARD_SIZE = 8;
    inline static const int TILE_SIZE = 100; // Each square is 100x100 pixels
    sf::RenderWindow window;
    std::unordered_map<std::string, sf::Texture> pieceTextures;
    std::unordered_map<std::string, sf::Sprite> pieceSprites;

public:
    BoardGUI();


    void display();

};



#endif //  BOARD_GUI_H