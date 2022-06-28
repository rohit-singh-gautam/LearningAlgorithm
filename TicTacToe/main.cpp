#include "tictactoe.h"
#include "TicTacToeEngine.h"
#include <iostream>

template <typename ttt>
void test() {
	ttt engine;

	while (!engine.game_over()) {
		int row;
		int col;

		while(true) {
			std::cout << engine;
			std::cout << "Enter row: ";
			std::cin >> row;
			std::cout << "Enter col: ";
			std::cin >> col;

			if (engine.make_move({row, col})) break;
			std::cout << "Unable to move (" << row << ',' << col << ')' << std::endl;
		}
		if (engine.game_over()) break;
		std::cout << engine;
		if (!engine.auto_move()) {
			std::cout << "Unable to auto move" << std::endl;
		}
	}

	std::cout << engine;
}

int main(int argc, char* argv[]) {
	test<tictactoe>();
	test<TicTacToeEngine>();

	return 0;
}