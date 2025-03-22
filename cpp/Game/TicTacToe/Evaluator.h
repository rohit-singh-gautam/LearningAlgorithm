#pragma once

#include "Board.h"


class Evaluator {
	const Board& board;

public:
	Evaluator(const Board& board) : board(board) {}

	int score() const {
		const auto winning { board.who_is_winning() };
		if (winning == piece::none) return 0;
		return static_cast<int>(board.getCount()) - 10;
	}
};