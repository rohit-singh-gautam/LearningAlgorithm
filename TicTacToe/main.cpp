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

void boardtest() {
	Board boards[] {
		{"xxx o  o "},
		{"o  xxx  o"},
		{"o   o xxx"},
		{"x ox  xo "},
		{"ox  x  xo"},
		{"o x ox  x"},
		{"o x xox  "},
		{"x oox   x"},
		{"ooo x xx "},
		{" x ooox x"},
		{"  x xxooo"},
		{"o xoxxo  "},
		{"xox ox o "},
		{"xxo xo  o"},
		{"ox  oxx o"},
		{"x o oxo x"},
		{"xoxxoxoxo"},
	};

	for(auto &board: boards) {
		Evaluator evaluator { board };
		std::cout << board;
		int score = evaluator.score();
		if (score < 0) std::cout << "First winning\n";
		else if (score > 0) std::cout << "Second winning\n";
		std::cout << std::endl;
	}

}

int main(int argc, char* argv[]) {
	test<tictactoe>();
	//test<TicTacToeEngine>();
	//boardtest();

	return 0;
}