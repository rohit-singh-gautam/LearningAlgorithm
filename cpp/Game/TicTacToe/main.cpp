#include "tictactoe.h"
#include "TicTacToeEngine.h"
#include <iostream>

// Return true if game is over
bool MakeMove(auto &engine, bool human) {
	if (human) {
		int row { };
		int col { };

		while(true) {
			std::cout << engine;
			std::cout << "Enter row col: ";
			std::cin >> row;
			std::cin >> col;

			if (engine.make_move({row, col})) break;
			std::cout << "Unable to move (" << row << ',' << col << ") try again" << std::endl;
		}
	} else {
		if (!engine.auto_move()) {
			std::cout << "Unable to auto move" << std::endl;
		}
	}
	std::cout << engine;
	return engine.game_over();
}

template <typename ttt>
void test(bool firstHuman, bool secondHuman) {
	ttt engine;

	while (true) {
		if (MakeMove(engine, firstHuman)) break;
		if (MakeMove(engine, secondHuman)) break;
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
		auto score = evaluator.score();
		if (score < 0) std::cout << "First winning\n";
		else if (score > 0) std::cout << "Second winning\n";
		std::cout << std::endl;
	}

}

void DisplayUsage() {
	std::cout << "Usage: tictactoe [test]" << std::endl;
	std::cout << "Usage: tictactoe [algo1|algo2] [player 1 [computer|human]] [player2 [computer|human]]" << std::endl;
	std::cout << "Example: tictactoe human computer" << std::endl;
	std::cout << "Example: tictactoe algo1 human computer" << std::endl;
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args(argv, argv + argc);
	if (args.size() == 2) {
		if (args[1] != "test") {
			DisplayUsage();
			return 0;
		}
		boardtest();
		return 0;
	} else if (args.size() == 3) {
		if (args[1] != "computer" and args[1] != "human" and args[2] != "computer" and args[2] != "human") {
			DisplayUsage();
			return 0;
		}
		auto firstPlayer = args[1] == "human";
		auto secondPlayer = args[2] == "human";
		test<TicTacToeEngine>(firstPlayer, secondPlayer);
		return 0;
	} else if (args.size() == 4) {
		if (args[1] != "algo1" and args[1] != "algo2" and args[2] != "computer" and args[2] != "human" and args[3] != "computer" and args[3] != "human") {
			DisplayUsage();
			return 0;
		}
		auto firstPlayer = args[2] == "human";
		auto secondPlayer = args[3] == "human";
		if (args[1] == "algo1") {
			test<TicTacToeEngine>(firstPlayer, secondPlayer);
		} else {
			std::cout << "Algo 2" << std::endl;
			test<tictactoe>(firstPlayer, secondPlayer);
		}
		return 0;
	}
	DisplayUsage();
	return 0;
}