#pragma once 

#include <vector>
#include "Context.h"

class Level {
	public:
		int normalized;
		int rows;
		int columns;
		std::vector<std::vector<int>> board;
		Level(int n, int r, int c);
		~Level();
		void printBoard();

		void showGridLines(int cx, int cy);
};
