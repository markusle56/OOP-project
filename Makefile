# This section compiles the main game executable
chess: main.cpp Game.cpp Board.cpp Piece.cpp
	g++ -std=c++17 main.cpp Game.cpp Board.cpp Piece.cpp Move.cpp Pawn.cpp -o chess -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system 

# This section compiles the game and runs the executable at the same time
chess_run: main.cpp Game.cpp Board.cpp Piece.cpp
	g++ -std=c++17 main.cpp Game.cpp Board.cpp Piece.cpp Move.cpp Pawn.cpp -o chess -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system 
	./chess
# This section forcefully removes the chess executable
clear:
	rm -f chess

