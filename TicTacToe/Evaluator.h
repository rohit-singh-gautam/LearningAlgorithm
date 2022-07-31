#pragma once

#include "Board.h"


class Evaluator {
	const Board& board;

public:
	Evaluator(const Board& board) : board(board) {}

	int score() const {
		int moveScoreSecond = 10 - board.getCount();
		int moveScoreFirst = -moveScoreSecond;
		auto winning { board.who_is_winning() };
		return moveScoreFirst * (winning == piece::first) + moveScoreSecond * (winning == piece::second);
	}
};