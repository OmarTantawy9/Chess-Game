#ifndef BOARD_GUI_H
#define BOARD_GUI_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <stdexcept>

#include "Board.h"

class BoardGUI {
    inline static const int BOARD_SIZE = 8;
    inline static const int TILE_SIZE = 100; // Each square is 100x100 pixels
    inline static const int GRAVEYARD_WIDTH = 300;
    sf::RenderWindow window;
    Board board;

    struct ChessPiece {
        sf::Sprite sprite;
        sf::Vector2i position; 
        bool isCaptured; 

        ChessPiece(const sf::Texture &texture, sf::Vector2i pos) : sprite(texture), position(pos), isCaptured(false) {
            sprite.setPosition({pos.x * TILE_SIZE + GRAVEYARD_WIDTH, pos.y * TILE_SIZE});
            sprite.setScale({0.8f, 0.8f}); // Adjust size
        }
    };

    std::vector<ChessPiece> pieces;
    std::vector<ChessPiece> whitePiecesGraveyard;
    std::vector<ChessPiece> blackPiecesGraveyard;

    std::unordered_map<std::string, sf::Texture> textures; // Texture cache

    std::optional<size_t> draggedPieceIndex = std::nullopt; // Track dragged piece
    sf::Vector2f dragOffset;

public:
    BoardGUI();
    void display();

private:
    void drawBoard();
    void drawGravyard();
    void loadTextures();

    void handleMousePress(const sf::Vector2i &mousePos);
    void handleMouseRelease(const sf::Vector2i &mousePos);
    void handleMouseMove(const sf::Vector2i &mousePos);
    sf::Vector2i getTilePosition(const sf::Vector2i &mousePos);
    sf::Vector2i getNextWhiteGraveyardPos();
    sf::Vector2i getNextBlackGraveyardPos();
};

#endif // BOARD_GUI_H
