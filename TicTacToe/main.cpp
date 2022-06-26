#include "TicTacToeEngine.h"
#include <iostream>

int main(int argc, char* argv[]) {
	TicTacToeEngine engine;

	while (!engine.gameOver()) {
		int row;
		int col;

		while(true) {
			std::cout << engine;
			std::cout << "Enter row: ";
			std::cin >> row;
			std::cout << "Enter col: ";
			std::cin >> col;

			if (engine.makeMove(move(row, col))) break;
			std::cout << "Unable to move (" << row << ',' << col << ')' << std::endl;
		}
		if (engine.gameOver()) break;
		std::cout << engine;
		if (!engine.autoMove()) {
			std::cout << "Unable to auto move" << std::endl;
		}
	}

	std::cout << engine;
	return 0;
}