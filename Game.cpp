#include "Game.h"
#include <string>

Game::Game(): window(sf::VideoMode(800,800), "Magic Chess"), isWhiteTurn(true), gameOver(false), selectedPiece(nullptr), subWindowOpen(false), stage(0) {
};

Game::~Game() {}

void Game::init()
{
    board.setupBoard();
}

void Game::run()
{
    while (window.isOpen())
    {
        handleInput();
        update();
        render();
    }
}

void Game::handleInput()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed) {
            window.close();
        }
       if (stage == 0) { 
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                stage = 1; 
            }

       } else if (stage == 1) {
            if(event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;
                    int X = mouseX / 100;
                    int Y = mouseY / 100;
                    if (selectedPiece == nullptr) {
                        selectedPiece = board.getPieceAt(X,Y);
                        if (selectedPiece && selectedPiece->getIsWhite() == isWhiteTurn) {
                            possibleMoves = selectedPiece->getPossibleMoves(board);
                        } else {
                            selectedPiece = nullptr;
                        }
                    } else {
                        if (selectedPiece->getX() == X &&  selectedPiece->getY() == Y) {
                            selectedPiece = nullptr;
                        } else {
                            for (auto & move : possibleMoves) {
                                if (move.endX == X && move.endY == Y) {
                                    move.execute(board);
                                    isWhiteTurn = !isWhiteTurn;
                                    selectedPiece = nullptr;
                                    break;
                                }
                            }
                        }
                        if (selectedPiece == nullptr) {
                            possibleMoves.clear();
                        }
                    }
                }
            }
       } else if (stage == 2 || stage == 3) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Y) {
                resetGame();
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::N) {
                window.close();
            }

       }

    }
}


void Game::update()
{   
    if (board.canPromote() && !subWindowOpen) {
        subWindow.create(sf::VideoMode(600,200), "Promote");
        subWindowOpen = true;
        selectedPiece = board.canPromote();
        
    }
    if(board.isCheck(isWhiteTurn) == sf::Vector2i(-2,-2)) {
        gameOver = true;
        if (isWhiteTurn) {
            stage = 2; 
            // black win 
        } else {
            stage = 3;
        }
        return;
    }
}

void Game::render()
{   
    if (stage == 0) {
        window.clear(sf::Color::White);
        sf::Texture introTexture; 
        if (!introTexture.loadFromFile("IMG/Intro.png")) {
            std::cout<<"ERROR! Can not load intro image"<<std::endl;
            return; 
        }
        sf::Sprite intro(introTexture);
        window.draw(intro);
       
        window.display();

    } else if (stage == 1) {
        window.clear(sf::Color::White);

        board.drawBoard(window);

        sf::Vector2i kingPosition = board.isCheck(isWhiteTurn);
        if (kingPosition.x >= 0 ){
            Piece * king = board.getPieceAt(kingPosition.x,kingPosition.y);
            king->draw_background(window, "red");
        }
        if(selectedPiece) {
            selectedPiece->draw_background(window, "yellow");
        }
        board.drawPieces(window);
        for (auto move : possibleMoves) {
            move.draw(window);
        } 
        window.display();

        if (subWindowOpen) {drawPromote(subWindow);}
    } else if (stage == 2 || stage == 3) {
        sf::Texture outtroTexture; 
        std::string filePath;
        if (stage == 2) {
            filePath = "IMG/blackWin.png";
        } else {
            filePath = "IMG/whiteWin.png";
        }
        if (!outtroTexture.loadFromFile(filePath)) {
            std::cout<<"ERROR! Can not load outtro image"<<std::endl;
            return;
        }
        sf::Sprite outtro(outtroTexture);
        window.draw(outtro);
       
        window.display();
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

    board.setupBoard();           
    isWhiteTurn = true;      
    selectedPiece = nullptr;    
    possibleMoves.clear();      
    gameOver = false;             
    subWindowOpen = false;      
    stage = 1;                 
}