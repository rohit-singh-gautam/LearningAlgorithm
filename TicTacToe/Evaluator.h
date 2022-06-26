#pragma once

#include "Board.h"


class Evaluator {
	const Board& board;

public:
	Evaluator(const Board& board) : board(board) {}

	int score() const {
		int moveScoreSecond = 10 - board.getCount();
		int moveScoreFirst = -moveScoreSecond;
		piece currentPiece = board.getCurrentPiece();
		int s = 0;


	
		for (int row = 0; row < Board::rowcount; row++) {
			if (board[move(row, 0)] != piece::none && board[move(row, 0)] == board[move(row, 1)] && board[move(row, 1)] == board[move(row, 2)]) {
				s = board[move(row, 0)] == piece::first ? moveScoreFirst : moveScoreSecond;
			}
		}

		for (int col = 0; col < Board::colcount; col++) {
			if (board[move(0, col)] != piece::none && board[move(0, col)] == board[move(1, col)] && board[move(1, col)] == board[move(2, col)]) {
				s = board[move(0, col)] == piece::first ? moveScoreFirst : moveScoreSecond;
			}
		}

		if (board[move(1, 1)] != piece::none) {
			if (board[move(0, 0)] == board[move(1, 1)] && board[move(1, 1)] == board[move(2, 2)]) {
				s = board[move(1, 1)] == piece::first ? moveScoreFirst : moveScoreSecond;
			}

			if (board[move(0, 2)] == board[move(1, 1)] && board[move(1, 1)] == board[move(2, 0)]) {
				s = board[move(1, 1)] == piece::first ? moveScoreFirst : moveScoreSecond;
			}
		}

		return s;
	}
};