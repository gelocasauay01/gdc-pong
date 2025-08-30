
all:
	g++ src/main.cpp src/game/*.cpp src/engine/*.cpp -o game -Iinclude -Llib -lSDL3 -lSDL3_ttf