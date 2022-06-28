#pragma once

#include "Board.h"
#include "Evaluator.h"
#include <random>
#include <iostream>
#include <limits>

class Intelligence {
	Board& board;
	const Evaluator& evaluator;

	std::random_device rd;
	std::mt19937 gen;

public:
	Intelligence(Board& board, const Evaluator& evaluator) : board(board), evaluator(evaluator), rd(), gen(rd()) {}

	const move getNextMove() {
		const piece currentPiece = board.getCurrentPiece();
		int bestScore = currentPiece == piece::first ?
			std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
		const auto allMoves = board.getAllMove();

		std::vector<move> bestMoves;

		for (const auto& m : allMoves) {
			if (!board.makeMove(m)) continue;
			int score = minmax();
			if (!board.undo(m)) throw "Undo must work";

			if (score == bestScore) {
				bestMoves.push_back(m);
			}

			if (currentPiece == piece::first) {
				if (score < bestScore) {
					bestMoves.clear();
					bestMoves.push_back(m);
					bestScore = score;
				}
			}
			else {
				if (score > bestScore) {
					bestMoves.clear();
					bestMoves.push_back(m);
					bestScore = score;
				}
			}
		}

		auto begin = bestMoves.begin();
		std::uniform_int_distribution<> dis(0, std::distance(begin, bestMoves.end()) - 1);
		std::advance(begin, dis(gen));
		return *begin;
	}

	int minmax() {
		const int boardScore = evaluator.score();
		const int moveCount = board.getCount();
		if (boardScore != 0 || moveCount == 9) {
			
			return boardScore;
		}

		const piece currentPiece = board.getCurrentPiece();

		int bestScore = currentPiece == piece::first ? 
			std::numeric_limits<int>::max() : std::numeric_limits<int>::min();
		const auto allMoves = board.getAllMove();

		for (const auto& m: allMoves) {
			if (!board.makeMove(m)) throw "Move must work";
			int score = minmax();
			if (!board.undo(m)) throw "Undo must work";

			if (currentPiece == piece::first) {
				if (score < bestScore) {
					bestScore = score;
				}
			}
			else {
				if (score > bestScore) {
					bestScore = score;
				}
			}
		}
		
		return bestScore;
	}

};
