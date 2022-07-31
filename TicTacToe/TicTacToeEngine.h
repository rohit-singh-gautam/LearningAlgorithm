#pragma once
#include "Board.h"
#include "Evaluator.h"
#include "Intelligence.h"

class TicTacToeEngine {
	Board board;
	Evaluator evaluator;
	Intelligence intelligence;

public:
	TicTacToeEngine() : board(), evaluator(board), intelligence(board, evaluator) {
		board.reset();
	}

	void reset() {
		board.reset();
	}

	piece getCurrentPlayer() const {
		return board.getCurrentPiece();
	}

	bool make_move(const move& m) {
		return board.makeMove(m);
	}

	bool auto_move() {
		const auto m = intelligence.getNextMove();
		return board.makeMove(m);
	}

	bool game_over() const {
		return board.getCount() == 9 || evaluator.score() != 0;
	}

	piece who_is_winning() const {
		int score = evaluator.score();
		if (score > 0) return piece::second;
		if (score < 0) return piece::first;
		return piece::none;
	}

	friend std::ostream& operator<<(std::ostream& o, const TicTacToeEngine& e);
};

std::ostream& operator<<(std::ostream& o, const TicTacToeEngine& e) {
	o << e.board;
	if (e.game_over()) {
		const auto whoIsWinning = e.who_is_winning();
		o << "GAME OVER - ";
		if (whoIsWinning == piece::none) {
			o << "DRAW" << std::endl;
		}
		else {
			o << "WINNING: " << whoIsWinning << std::endl;
		}
	}
	return o;
}
