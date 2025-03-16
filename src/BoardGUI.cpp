#include "../include/BoardGUI.h"

#include <array>
#include <map>
#include <string>

BoardGUI::BoardGUI() : window {sf::VideoMode({(BOARD_SIZE) * TILE_SIZE, (BOARD_SIZE) * TILE_SIZE}), "Chess Board"} {

    std::array<std::string, 6> pieceNames = {"pawn", "rook", "knight", "bishop", "queen", "king"};
    for (const auto& piece : pieceNames) {
        for (const auto& color : {"white", "black"}) {
            std::string pieceKey = color + std::string("-") + piece; 
            std::string filename = "./images/" + pieceKey + ".png"; // e.g., "white-pawn.png"
            if (!pieceTextures[pieceKey].loadFromFile(filename)) {
                throw std::runtime_error("Error loading texture"); 
            }
            
            pieceTextures[pieceKey].setSmooth(true); 
            pieceSprites.emplace(pieceKey, pieceTextures[pieceKey]);
            pieceSprites.at(pieceKey).setScale(sf::Vector2f(0.8f, 0.8f));
        }
    }
}


void BoardGUI::display() {
    while (window.isOpen()) {
        // sf::Event event{sf::Event::Closed};
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            window.clear();

            // Draw the chessboard
            for (int row = 0; row < BOARD_SIZE; row++) {
                for (int col = 0; col < BOARD_SIZE; col++) {
                    sf::RectangleShape square(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                    square.setPosition({col * TILE_SIZE, row * TILE_SIZE});
                    square.setFillColor((row + col) % 2 == 0 ? sf::Color(171, 178, 191) : sf::Color(99,109,131)); // Light & Dark squares
                    window.draw(square);
                }
            }

            pieceSprites.at("black-rook").setPosition({0, 0});
            window.draw(pieceSprites.at("black-rook"));

            pieceSprites.at("black-rook").setPosition({7 * TILE_SIZE, -5});
            window.draw(pieceSprites.at("black-rook"));

            pieceSprites.at("black-knight").setPosition({1 * TILE_SIZE, -5});
            window.draw(pieceSprites.at("black-knight"));


            pieceSprites.at("black-knight").setPosition({6 * TILE_SIZE, -5});
            window.draw(pieceSprites.at("black-knight"));
            
            pieceSprites.at("black-bishop").setPosition({2 * TILE_SIZE, -5});
            window.draw(pieceSprites.at("black-bishop"));


            pieceSprites.at("black-bishop").setPosition({5 * TILE_SIZE, -5});
            window.draw(pieceSprites.at("black-bishop"));


            pieceSprites.at("black-queen").setPosition({3  * TILE_SIZE, -5});
            window.draw(pieceSprites.at("black-queen"));

            pieceSprites.at("black-king").setPosition({4  * TILE_SIZE, -5});
            window.draw(pieceSprites.at("black-king"));


            for(int col = 0; col < pieceTextures.size() ; ++col){
                pieceSprites.at("black-pawn").setPosition({col * TILE_SIZE, TILE_SIZE - 5});
                window.draw(pieceSprites.at("black-pawn"));
            }


            pieceSprites.at("white-rook").setPosition({0, 7 * TILE_SIZE - 5});
            window.draw(pieceSprites.at("white-rook"));

            pieceSprites.at("white-rook").setPosition({7 * TILE_SIZE, 7 * TILE_SIZE - 5});
            window.draw(pieceSprites.at("white-rook"));

            pieceSprites.at("white-knight").setPosition({1 * TILE_SIZE, 7 * TILE_SIZE - 5});
            window.draw(pieceSprites.at("white-knight"));


            pieceSprites.at("white-knight").setPosition({6 * TILE_SIZE, 7 * TILE_SIZE - 5});
            window.draw(pieceSprites.at("white-knight"));
            
            pieceSprites.at("white-bishop").setPosition({2 * TILE_SIZE, 7 * TILE_SIZE - 5});
            window.draw(pieceSprites.at("white-bishop"));


            pieceSprites.at("white-bishop").setPosition({5 * TILE_SIZE, 7 * TILE_SIZE - 5});
            window.draw(pieceSprites.at("white-bishop"));


            pieceSprites.at("white-queen").setPosition({3  * TILE_SIZE, 7 * TILE_SIZE - 5});
            window.draw(pieceSprites.at("white-queen"));

            pieceSprites.at("white-king").setPosition({4  * TILE_SIZE, 7 * TILE_SIZE - 5});
            window.draw(pieceSprites.at("white-king"));


            for(int col = 0; col < pieceTextures.size() ; ++col){
                pieceSprites.at("white-pawn").setPosition({col * TILE_SIZE, 6 * TILE_SIZE -  5});
                window.draw(pieceSprites.at("white-pawn"));
            }


            window.display();
        }
    }
}
