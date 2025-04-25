#include "../include/BoardGUI.h"
#include <array>
#include <map>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

BoardGUI::BoardGUI() 
    : window(sf::VideoMode({BOARD_SIZE * TILE_SIZE + (2 * GRAVEYARD_WIDTH), BOARD_SIZE * TILE_SIZE}), "Chess Board",
                            sf::Style::Titlebar | sf::Style::Close),
      whitePos(0, 0), 
      blackPos(0, 0),
      board() {

    if (!font.openFromFile("./fonts/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    if(!pieceMoveSound.openFromFile("./audio/move-self.wav")){
        std::cerr << "Error loading sound!" << std::endl;
        return;
    }

    loadTextures();

    std::vector<std::pair<std::string, sf::Vector2i>> initialPositions = {
        
        {"black-rook.png",   {0, 0}},       {"white-rook.png",   {0, 7}}, 
        {"black-rook.png",   {7, 0}},       {"white-rook.png",   {7, 7}},
        {"black-knight.png", {1, 0}},       {"white-knight.png", {1, 7}}, 
        {"black-knight.png", {6, 0}},       {"white-knight.png", {6, 7}},    
        {"black-bishop.png", {2, 0}},       {"white-bishop.png", {2, 7}},  
        {"black-bishop.png", {5, 0}},       {"white-bishop.png", {5, 7}},    
        {"black-queen.png",  {3, 0}},       {"white-queen.png",  {3, 7}},
        {"black-king.png",   {4, 0}},       {"white-king.png",   {4, 7}},  
        {"black-pawn.png",   {0, 1}},       {"white-pawn.png",   {0, 6}},  
        {"black-pawn.png",   {1, 1}},       {"white-pawn.png",   {1, 6}},    
        {"black-pawn.png",   {2, 1}},       {"white-pawn.png",   {2, 6}},    
        {"black-pawn.png",   {3, 1}},       {"white-pawn.png",   {3, 6}},
        {"black-pawn.png",   {4, 1}},       {"white-pawn.png",   {4, 6}},  
        {"black-pawn.png",   {5, 1}},       {"white-pawn.png",   {5, 6}},    
        {"black-pawn.png",   {6, 1}},       {"white-pawn.png",   {6, 6}},    
        {"black-pawn.png",   {7, 1}},       {"white-pawn.png",   {7, 6}}
          
    };

    for (auto& [filename, pos] : initialPositions) {
        pieces.emplace_back(textures[filename], pos);
    }

}

void BoardGUI::loadTextures() {
    std::vector<std::string> pieceFiles = {
        "black-rook.png", "black-knight.png", "black-bishop.png", "black-queen.png", "black-king.png", "black-pawn.png",
        "white-rook.png", "white-knight.png", "white-bishop.png", "white-queen.png", "white-king.png", "white-pawn.png"
    };

    for (const auto& file : pieceFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile("./images/" + file)) {
            throw std::runtime_error("Failed to load texture: " + file);
        }
        texture.setSmooth(true);
        textures[file] = std::move(texture);
    }
}


bool BoardGUI::display() {
    std::optional<ChessPiece> draggedPiece;  
    while (window.isOpen() && !board.isGameOver()) {

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                return false;
            } 
            else if (event->is<sf::Event::MouseButtonPressed>()) {
                draggedPiece = handleMousePress(sf::Mouse::getPosition(window));
            } 
            else if (event->is<sf::Event::MouseButtonReleased>()) {
                handleMouseRelease(sf::Mouse::getPosition(window));
                draggedPiece.reset();
            } 
            else if (event->is<sf::Event::MouseMoved>()) {
                handleMouseMove(sf::Mouse::getPosition(window));
            }
            else if(auto keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if(keyPressed->scancode == sf::Keyboard::Scancode::R) {
                    return true;
                }
            }
        }

        window.clear();
        drawGravyard();
        drawBoard(draggedPiece);
        window.display();
    }

    while(window.isOpen()){

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                return false;
            } 
            else if(auto keyPressed = event->getIf<sf::Event::KeyPressed>()){
                if(keyPressed->scancode == sf::Keyboard::Scancode::Enter
                   || keyPressed->scancode == sf::Keyboard::Scancode::NumpadEnter) {
                    return true;
                }
                else if(keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    return false;
                }
            }
        }

        // Create text for black graveyard
        sf::Text winnerText(font, board.getWinner() + " is the Winner!", 100);
        winnerText.setFillColor({242,244,245});

        auto center = winnerText.getGlobalBounds().size / 2.f;
        auto localBounds = center + winnerText.getLocalBounds().position;
        sf::Vector2f rounded = {round(localBounds.x), round(localBounds.y)};
        winnerText.setOrigin(rounded);
        winnerText.setPosition(sf::Vector2f{ window.getSize() / 2u });


        sf::RectangleShape square{{BOARD_SIZE * TILE_SIZE + (2 * GRAVEYARD_WIDTH), (BOARD_SIZE * TILE_SIZE) / 3}};
        
        center = square.getGlobalBounds().size / 2.f;
        localBounds = center + square.getLocalBounds().position;
        rounded = {round(localBounds.x), round(localBounds.y)};
        square.setOrigin(rounded);
        square.setPosition(sf::Vector2f{ window.getSize() / 2u });

        square.setFillColor({0,133,115, 225});

        window.clear();
        drawGravyard();
        drawBoard();
        window.draw(square);
        window.draw(winnerText);
        window.display();
    }

    return true;
}

void BoardGUI::drawBoard(const std::optional<ChessPiece> &draggedPiece) {

    
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            sf::RectangleShape square(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            square.setPosition({col * TILE_SIZE + GRAVEYARD_WIDTH, row * TILE_SIZE});
            square.setFillColor((row + col) % 2 == 0 ? sf::Color(171, 178, 191) : sf::Color(99,109,131));
            window.draw(square);
        }
    }

    if(draggedPiece){
        auto draggedPiecePtr = board.getPieceAt((*draggedPiece).position.y, (*draggedPiece).position.x);
        auto validMoves = draggedPiecePtr->getValidMoves(board);
        for (auto &[y, x] : validMoves) {
            sf::RectangleShape square{{TILE_SIZE, TILE_SIZE}};
            square.setPosition({x * TILE_SIZE + GRAVEYARD_WIDTH, y * TILE_SIZE});
            square.setFillColor({82,139,255, 120});
            window.draw(square);
        }
    }
    
    ChessPiece* draggedPiecePtr{nullptr};

    for (auto& piece : pieces) {
        if(draggedPiece
           && piece.position.x == draggedPiece->position.x 
           && piece.position.y == draggedPiece->position.y){
            draggedPiecePtr = &piece;
            continue;
           }
        window.draw(piece.sprite);
    }

    if(draggedPiecePtr){
        window.draw(draggedPiecePtr->sprite);
    }

    if(board.isGameOver()){

        static bool isFadding = true;
        static double fadeFactor = 1;

        auto capturedKing = board.findKing(board.getPlayerTurn());
        sf::RectangleShape square{{TILE_SIZE, TILE_SIZE}};
        square.setPosition({capturedKing->getCol() * TILE_SIZE + GRAVEYARD_WIDTH, capturedKing->getRow() * TILE_SIZE});
        
        fadeFactor += isFadding ? -0.005 : 0.005;
        
        if(fadeFactor <= 0){
            isFadding = false;
        }
        else if(fadeFactor >= 1){
            isFadding = true;
        }

        sf::Color color;
        
        square.setFillColor({254,112,112, 180 * fadeFactor});
        window.draw(square);
    }

}

void BoardGUI::drawGravyard(){

    // Draw the graveyard background
    sf::RectangleShape blackGraveyard(sf::Vector2f(GRAVEYARD_WIDTH, TILE_SIZE * 8));
    sf::RectangleShape whiteGraveyard(sf::Vector2f(GRAVEYARD_WIDTH, TILE_SIZE * 8));
    
    blackGraveyard.setFillColor({40,44,52}); 
    blackGraveyard.setPosition({0, 0}); 

    whiteGraveyard.setFillColor({40,44,52});
    whiteGraveyard.setPosition({(TILE_SIZE * BOARD_SIZE) + GRAVEYARD_WIDTH, 0}); 

    if (!font.openFromFile("./fonts/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    // Create text for black graveyard
    sf::Text blackGraveyardText(font, " \tBLACK\nGRAVEYARD", 35);
    blackGraveyardText.setPosition({GRAVEYARD_WIDTH + (TILE_SIZE * BOARD_SIZE) + (GRAVEYARD_WIDTH / 7), 50}); 
    blackGraveyardText.setFillColor({242,244,245});

    // Create text for white graveyard
    sf::Text whiteGraveyardText(font, " \tWHITE\nGRAVEYARD", 35);
    whiteGraveyardText.setPosition({GRAVEYARD_WIDTH / 7, 50});
    whiteGraveyardText.setFillColor({242,244,245});

    // Draw everything
    window.draw(whiteGraveyard);
    window.draw(blackGraveyard);
    window.draw(blackGraveyardText);
    window.draw(whiteGraveyardText);

}


std::optional<BoardGUI::ChessPiece> BoardGUI::handleMousePress(const sf::Vector2i &mousePos) {

    if(mousePos.x < GRAVEYARD_WIDTH || mousePos.x >= (GRAVEYARD_WIDTH + (TILE_SIZE * BOARD_SIZE))) return std::nullopt;

    for (size_t i = 0; i < pieces.size(); ++i) {
        if (pieces[i].sprite.getGlobalBounds().contains(window.mapPixelToCoords(mousePos))) {
            auto draggedPiecePtr = board.getPieceAt(pieces[i].position.y, pieces[i].position.x);
            if(draggedPiecePtr->getColor() != board.getPlayerTurn()) return std::nullopt;
            draggedPieceIndex = i;
            dragOffset = pieces[i].sprite.getPosition() - window.mapPixelToCoords(mousePos);
            return {pieces[i]};

        }
    }
    return std::nullopt;
}

void BoardGUI::highlightValidMoves(const ChessPiece &piece){
    
    auto draggedPiecePtr = board.getPieceAt(piece.position.y, piece.position.x);
    auto validMoves = draggedPiecePtr->getValidMoves(board);
    for (auto &[y, x] : validMoves) {
        sf::RectangleShape square;
        square.setPosition({y * TILE_SIZE + GRAVEYARD_WIDTH, x * TILE_SIZE});
        square.setFillColor({82,139,255});
        window.draw(square);
        std::cout << "Highlighted valid moves" << y << ","  << x << std::endl;

    }
    

}

void BoardGUI::handleMouseMove(const sf::Vector2i &mousePos) {
    if (draggedPieceIndex.has_value()) {
        pieces[*draggedPieceIndex].sprite.setPosition(window.mapPixelToCoords(mousePos) + dragOffset);
    }
}


void BoardGUI::handleMouseRelease(const sf::Vector2i &mousePos) {
    if (!draggedPieceIndex.has_value()) return;
    
    auto dropPos = window.mapPixelToCoords(mousePos);

    // Compute tile indices considering board offsets
    constexpr int BOARD_OFFSET_X = GRAVEYARD_WIDTH; // Shift due to left graveyard
    constexpr int BOARD_OFFSET_Y = 0;               // Assuming board is top-aligned

    int newX = (dropPos.x - BOARD_OFFSET_X) / TILE_SIZE;
    int newY = (dropPos.y - BOARD_OFFSET_Y) / TILE_SIZE;

    auto &draggedPiece = pieces[*draggedPieceIndex];
    auto oldPos = draggedPiece.position;


    // Ensure the move stays within board bounds
    if (newX < 0 || newX >= BOARD_SIZE || newY < 0 || newY >= BOARD_SIZE) {
        draggedPiece.sprite.setPosition({oldPos.x * TILE_SIZE + BOARD_OFFSET_X, oldPos.y * TILE_SIZE});
        draggedPieceIndex.reset();
        return;
    }

    // Get the moving piece
    auto movingPiecePtr = board.getPieceAt(oldPos.y, oldPos.x);
    if (!movingPiecePtr) {
        draggedPieceIndex.reset();
        return;
    }

    // Check if moving to the same position (cancel move)
    if (newX == oldPos.x && newY == oldPos.y) {
        draggedPiece.sprite.setPosition({oldPos.x * TILE_SIZE + BOARD_OFFSET_X, oldPos.y * TILE_SIZE});
        draggedPieceIndex.reset();
        return;
    }

    auto targetPiece = board.getPieceAt(newY, newX);

    try {
        std::cout << "(" << oldPos.y << ", " << oldPos.x << ") -> (" << newY << ", " << newX << ")" << std::endl;

        // Move the piece in the logic board
        movingPiecePtr->moveTo(newY, newX, board);
        

        // Handle capturing
        if (targetPiece) {
            auto getCapturedPiece = [&newX, &newY](const ChessPiece &capturedPiece) {
                return capturedPiece.position == sf::Vector2i{newX, newY};
            };

            auto capturedPieceIt = std::find_if(pieces.begin(), pieces.end(), getCapturedPiece);
            if (capturedPieceIt == pieces.end()) {
                std::cerr << "Captured piece not found" << std::endl;
                throw std::runtime_error("Captured piece not found");
            }

            // Add the captured piece to the appropriate graveyard
            if (targetPiece->getColor() == "white") {
                capturedPieceIt->position = getNextWhiteGraveyardPos();
                capturedPieceIt->sprite.setPosition({10 + ((GRAVEYARD_WIDTH / 3) * (capturedPieceIt->position.x)), 
                                                      TILE_SIZE * 2 + (TILE_SIZE * capturedPieceIt->position.y)});
            } else if (targetPiece->getColor() == "black") {
                capturedPieceIt->position = getNextBlackGraveyardPos();
                auto offset = GRAVEYARD_WIDTH + TILE_SIZE * BOARD_SIZE + 10;
                capturedPieceIt->sprite.setPosition({offset + ((GRAVEYARD_WIDTH / 3) * (capturedPieceIt->position.x)), 
                                                     TILE_SIZE * 2 + (TILE_SIZE * capturedPieceIt->position.y)});

            } else {
                throw std::runtime_error("Invalid color");
            }

            capturedPieceIt->sprite.setScale({0.6f, 0.6f});
            capturedPieceIt->isCaptured = true;
        }

        // Update the piece's graphical position
        draggedPiece.sprite.setPosition({newX * TILE_SIZE + BOARD_OFFSET_X, newY * TILE_SIZE});
        draggedPiece.position = {newX, newY};
        pieceMoveSound.play();

    } catch (const invalidMoveException &e) {
        std::cout << "Invalid move: (" << newY << ", " << newX << ")" << std::endl;
        draggedPiece.sprite.setPosition({oldPos.x * TILE_SIZE + BOARD_OFFSET_X, oldPos.y * TILE_SIZE});
        draggedPiece.position = oldPos;
    }

    

    draggedPieceIndex.reset();
}

sf::Vector2i BoardGUI::getNextWhiteGraveyardPos(){

    auto nextPos = whitePos;

    if(whitePos.x != 2){
        ++whitePos.x;  
    }
    else{
        whitePos.x = 0;
        ++whitePos.y;
    }

    return nextPos;
}


sf::Vector2i BoardGUI::getNextBlackGraveyardPos(){

    auto nextPos = blackPos;

    if(blackPos.x != 2){
        ++blackPos.x;  
    }
    else{
        blackPos.x = 0;
        ++blackPos.y;
    }

    return nextPos;
}