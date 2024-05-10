all:
	clang++ -std=c++11 -I./include/SDL2 -L./lib/SDL2 -lsdl2 ./src/main.cpp ./src/grid.cpp ./src/simulation.cpp -o ./program
