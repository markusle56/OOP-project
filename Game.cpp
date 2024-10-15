#include "Game.h"
#include <string>

// Initialize game settings
Game::Game(): window(sf::VideoMode(800,800), "Magic Chess"), isWhiteTurn(true), gameOver(false), selectedPiece(nullptr), subWindowOpen(false), stage(0) {}

// Destructor
Game::~Game() {}

// Setup the board
void Game::init() {
    board.setupBoard();
}

// Main game loop
void Game::run() {
    while (window.isOpen()) {
        handleInput(); // Process inputs
        update();      // Update game state
        render();      // Draw game elements
    }
}


void Game::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event)) // Poll for events
    {
        if (event.type == sf::Event::Closed) { // Close window event
            window.close();
        }
        
        // Check if the game is in the intro stage
        if (stage == 0) { 
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                stage = 1; // Move to game start when Enter is pressed
            }

        // Handle input during the main gameplay stage
        } else if (stage == 1) {
            if (event.type == sf::Event::MouseButtonPressed) { // Mouse click event
                if (event.mouseButton.button == sf::Mouse::Left) { // Left mouse button clicked
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;
                    int X = mouseX / 100; // Convert mouse X coordinate to grid X
                    int Y = mouseY / 100; // Convert mouse Y coordinate to grid Y
                    if (selectedPiece == nullptr) { // No piece selected
                        selectedPiece = board.getPieceAt(X, Y); // Select piece at clicked position
                        if (selectedPiece && selectedPiece->getIsWhite() == isWhiteTurn) {
                            possibleMoves = selectedPiece->getPossibleMoves(board); // Get valid moves
                        } else {
                            selectedPiece = nullptr; // Deselect if invalid
                        }
                    } else { // A piece is already selected
                        if (selectedPiece->getX() == X && selectedPiece->getY() == Y) {
                            selectedPiece = nullptr; // Deselect if clicked on same piece
                        } else {
                            for (auto & move : possibleMoves) { // Check if valid move
                                if (move.endX == X && move.endY == Y) {
                                    move.execute(board); // Execute move
                                    isWhiteTurn = !isWhiteTurn; // Switch turn
                                    selectedPiece = nullptr; // Deselect piece
                                    break;
                                }
                            }
                        }
                        if (selectedPiece == nullptr) {
                            possibleMoves.clear(); // Clear possible moves after turn
                        }
                    }
                }
            }

        // Handle input during the game over stage
        } else if (stage == 2 || stage == 3) { 
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y) {
                resetGame(); // Reset game if 'Y' is pressed
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
                window.close(); // Close game if 'N' is pressed
            }
        }
    }
}



void Game::update()
{   
    // Check if a piece can be promoted and the promotion window is not open
    if (board.canPromote() && !subWindowOpen) {
        subWindow.create(sf::VideoMode(600, 200), "Promote"); // Create promotion window
        subWindowOpen = true; // Mark promotion window as open
        selectedPiece = board.canPromote(); // Get the piece to be promoted
    }
    
    // Check if the current player is in checkmate
    if (board.isCheck(isWhiteTurn) == sf::Vector2i(-2, -2)) { // If checkmate
        gameOver = true; // Mark game as over
        if (isWhiteTurn) {
            stage = 2; // Black wins
        } else {
            stage = 3; // White wins
        }
        return; // Exit function to stop further updates
    }
}

void Game::render()
{   
    if (stage == 0) { // Intro screen
        window.clear(sf::Color::White); // Clear window with white background
        sf::Texture introTexture; 
        if (!introTexture.loadFromFile("IMG/Intro.png")) { // Load intro image
            std::cout << "ERROR! Cannot load intro image" << std::endl;
            return;
        }
        sf::Sprite intro(introTexture);
        window.draw(intro); // Draw intro image
        
        window.display(); // Display contents

    } else if (stage == 1) { // Main game rendering
        window.clear(sf::Color::White); // Clear window with white background

        board.drawBoard(window); // Draw the chessboard

        // Check if a king is in check
        sf::Vector2i kingPosition = board.isCheck(isWhiteTurn);
        if (kingPosition.x >= 0) { // If king is in check
            Piece* king = board.getPieceAt(kingPosition.x, kingPosition.y); 
            king->draw_background(window, "red"); // Highlight king in red
        }
        
        if (selectedPiece) {
            selectedPiece->draw_background(window, "yellow"); // Highlight selected piece in yellow
        }

        board.drawPieces(window); // Draw all pieces on the board
        
        // Highlight possible moves
        for (auto move : possibleMoves) {
            move.draw(window); // Draw possible moves for selected piece
        }

        window.display(); // Display game contents

        // Handle promotion window if it's open
        if (subWindowOpen) {
            drawPromote(subWindow); // Render promotion window
        }

    } else if (stage == 2 || stage == 3) { // Game over screens
        sf::Texture outtroTexture; 
        std::string filePath = (stage == 2) ? "IMG/blackWin.png" : "IMG/whiteWin.png"; // Select win image
        if (!outtroTexture.loadFromFile(filePath)) { // Load win image
            std::cout << "ERROR! Cannot load outro image" << std::endl;
            return;
        }
        sf::Sprite outtro(outtroTexture);
        window.draw(outtro); // Draw win image
        
        window.display(); // Display win screen
    }
}


void Game::drawPromote(sf::RenderWindow & subWindow) {
    // Load the textures (every time the function is called, but only when needed)
    sf::Texture queenTexture, rookTexture, bishopTexture, knightTexture, backgroundTexture;
    if (!backgroundTexture.loadFromFile("IMG/promote_page.png")) {
        std::cout<<"Error loading background!"<<std::endl;
        return;
    }
    if (selectedPiece->getIsWhite()) {
        if (!queenTexture.loadFromFile("IMG/Queen_W.png") ||
            !rookTexture.loadFromFile("IMG/Brook_W.png") ||
            !bishopTexture.loadFromFile("IMG/Bishop_W.png") ||
            !knightTexture.loadFromFile("IMG/Knight_W.png")) {
            std::cout << "Error loading promotion textures!" << std::endl;
            return;
        } 
    } else {
        if (!queenTexture.loadFromFile("IMG/Queen_B.png") ||
            !rookTexture.loadFromFile("IMG/Brook_B.png") ||
            !bishopTexture.loadFromFile("IMG/Bishop_B.png") ||
            !knightTexture.loadFromFile("IMG/Knight_B.png")) {
            std::cout << "Error loading promotion textures!" << std::endl;
            return;
        } 
    }

    // Create sprites using the textures
    sf::Sprite queen(queenTexture);
    sf::Sprite rook(rookTexture);
    sf::Sprite bishop(bishopTexture);
    sf::Sprite knight(knightTexture);
    sf::Sprite background(backgroundTexture);

    // Scale and position the sprites
    queen.setScale(0.15, 0.15);
    rook.setScale(0.15, 0.15);
    bishop.setScale(0.15, 0.15);
    knight.setScale(0.15, 0.15);

    queen.setPosition(50, 70);
    rook.setPosition(190, 70);
    bishop.setPosition(330, 70);
    knight.setPosition(470, 70);

    // Event loop for the subwindow
    sf::Event event;
    while (subWindow.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            subWindow.close();
            subWindowOpen = false;
            return;
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(subWindow);
            if (!selectedPiece) {
                std::cout<<"ERROR DID NOT SEE PAWN TO PROMOTED"<<std::endl;
            }
            // Check if user clicked on one of the pieces
            if (queen.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                board.promote(selectedPiece, "Queen");
                selectedPiece = nullptr;
                subWindow.close();
                subWindowOpen = false;
                return;  // End the promotion window
            } else if (rook.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                board.promote(selectedPiece, "Rook");
                selectedPiece = nullptr;                
                subWindow.close();
                subWindowOpen = false;
                return;
            } else if (bishop.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                board.promote(selectedPiece, "Bishop");
                selectedPiece = nullptr;
                subWindow.close();
                subWindowOpen = false;
                return;
            } else if (knight.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                board.promote(selectedPiece, "Knight");
                selectedPiece = nullptr;
                subWindow.close();
                subWindowOpen = false;
                return;
            }
        }
    }

    // Draw the subwindow contents (sprites)
    subWindow.clear();
    subWindow.draw(background);
    subWindow.draw(queen);
    subWindow.draw(rook);
    subWindow.draw(bishop);
    subWindow.draw(knight);
    subWindow.display();
}


void Game::resetGame() {

    board.setupBoard();           // Reset the chessboard to the initial setup
    isWhiteTurn = true;           // Set the turn to white
    selectedPiece = nullptr;      // Deselect any selected piece
    possibleMoves.clear();        // Clear all possible moves
    gameOver = false;             // Reset the game over flag
    subWindowOpen = false;        // Close the promotion window if open
    stage = 1;                    // Set the game stage to the main game phase
}
