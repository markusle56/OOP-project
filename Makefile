# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 
LDFLAGS = -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-system 
INCLUDES = -I/opt/homebrew/opt/sfml/include


# Source files and output executable
SRCS = main.cpp Game.cpp Board.cpp Piece.cpp Move.cpp Pawn.cpp King.cpp Bishop.cpp Rook.cpp Queen.cpp Knight.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = chess

# Default build
all: $(TARGET)

# Compile the target executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $(TARGET) $(INCLUDES) $(LDFLAGS)

# Compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Run the game
run: $(TARGET)
	./$(TARGET)

# Debug build
debug: CXXFLAGS += -g
debug: all

# Release build
release: CXXFLAGS += -O2
release: all

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean debug release run chess chess_run
