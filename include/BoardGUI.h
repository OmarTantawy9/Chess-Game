#ifndef BOARD_GUI_H
#define BOARD_GUI_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <optional>

#include "Board.h"

class BoardGUI {
    inline static const int BOARD_SIZE = 8;
    inline static const int TILE_SIZE = 100;
    inline static const int GRAVEYARD_WIDTH = 300;
    
    sf::Font font;
    sf::RenderWindow window;
    sf::Vector2i whitePos;
    sf::Vector2i blackPos;

    Board board;

    struct ChessPiece {
        sf::Sprite sprite;
        sf::Vector2i position; 
        bool isCaptured; 

        ChessPiece(const sf::Texture &texture, const sf::Vector2i &pos) : sprite(texture), position(pos), isCaptured(false) {
            sprite.setPosition({pos.x * TILE_SIZE + GRAVEYARD_WIDTH, pos.y * TILE_SIZE});
            sprite.setScale({0.8f, 0.8f}); // Adjust size
        }

        ChessPiece(const sf::Sprite &sprite, const sf::Vector2i &pos, const bool &isCaptured) 
        : sprite(sprite), position(pos), isCaptured(isCaptured) {}

    };

    std::vector<ChessPiece> pieces;

    std::unordered_map<std::string, sf::Texture> textures; // Texture cache

    std::optional<size_t> draggedPieceIndex = std::nullopt; // Track dragged piece
    sf::Vector2f dragOffset;

public:
    BoardGUI();
    bool display();

private:
    void drawBoard(const std::optional<ChessPiece> &draggedPiece = std::nullopt);
    void drawGravyard();
    void loadTextures();
    void highlightValidMoves(const ChessPiece &piece);

    std::optional<ChessPiece> handleMousePress(const sf::Vector2i &mousePos);
    void handleMouseRelease(const sf::Vector2i &mousePos);
    void handleMouseMove(const sf::Vector2i &mousePos);
    sf::Vector2i getNextWhiteGraveyardPos();
    sf::Vector2i getNextBlackGraveyardPos();
};

#endif // BOARD_GUI_H
