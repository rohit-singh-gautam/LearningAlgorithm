#pragma once

#include "Board.h"


class Evaluator {
	const Board& board;

public:
	Evaluator(const Board& board) : board(board) {}

	auto score() const {
		const auto moveScoreSecond = 10 - board.getCount();
		const auto moveScoreFirst = -moveScoreSecond;
		const auto winning { board.who_is_winning() };
		return moveScoreFirst * (winning == piece::first) + moveScoreSecond * (winning == piece::second);
	}
};