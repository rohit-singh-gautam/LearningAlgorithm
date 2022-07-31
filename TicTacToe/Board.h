#pragma once

#include <ostream>
#include <vector>
#include <assert.h>
#include <concepts>

enum class piece : uint8_t {
	none,
	first,
	second
};

std::ostream& operator<<(std::ostream& o, const piece p) {
	switch (p) {
	case piece::second:
		return o << 'o';
		
	case piece::first:
		return o << 'x';

	default:
		return o << ' ';
	}
}

struct move {
	move() : row(0), col(0) {}
	move(const move& m) : row(m.row), col(m.col) {}
	move(int row, int col) : row(row), col(col) {}
	int row;
	int col;

	move& operator=(const move& m) {
		row = m.row;
		col = m.col;
		return *this;
	}
};

std::ostream& operator<<(std::ostream& o, const move& m) {
	return o << '(' << m.row << ',' << m.col << ')';
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& o, const std::pair<T1, T2>& p) {
	return o << '{' << p.first << ' ' << p.second << '}';
}

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& a) {
	const auto len = a.size();
	if (len == 0) {
		return o << "Empty";
	}
	for (std::decay_t<decltype(len)> i{ 0 }; i < len - 1; ++i) {
		o << a[i] << ' ';
	}

	return o << a.back();
}

class Board {
public:
	static constexpr size_t rowcount = 3;
	static constexpr size_t colcount = 3;

private:
	union {
		piece store[rowcount][colcount];
		piece flat[rowcount * colcount];
		uint64_t value[2];
	};
	int count;

public:
	Board() : value { 0, 0 }, count(0) {}

	Board(const std::string &boardcode) : value { 0, 0 }, count(0) {
		for(int index = 0; index < boardcode.size(); ++index) {
			const auto ch {boardcode[index]};
			const auto current_piece {
				(!!(ch == 'x' or ch == 'X')) +
				(!!(ch == 'o' or ch == 'O')) * 2
			};
			flat[index] = static_cast<piece>(current_piece);
			count += !!static_cast<bool>(flat[index]);
		}
	}

	void reset() {
		value[0] = value[1] = 0;
		count = 0;
	}

	piece getCurrentPiece() const {
		if (count == 9) return piece::none;

		if (count % 2 == 0) return piece::first;
		else return piece::second;
	}

	bool makeMove(const move& m) {
		if (m.row < 0 || m.row >= rowcount || m.col < 0 || m.col >= colcount
			|| getCount() == 9 || store[m.row][m.col] != piece::none) {
			return false;
		}

		store[m.row][m.col] = getCurrentPiece();
		count++;
		return true;
	}

	bool undo(const move &m) {
		if (m.row < 0 || m.row >= rowcount || m.col < 0 || m.col >= colcount || store[m.row][m.col] == piece::none) {
			return false;
		}

		store[m.row][m.col] = piece::none;
		count--;
		return true;
	}

	int getCount() const {
		return count;
	}

	uint64_t getValue(std::integral auto index) const {
		return value[index];
	}

	std::vector<move> getAllMove() const {
		std::vector<move> moves;
		for (int row = 0; row < rowcount; row++) {
			for (int col = 0; col < colcount; col++) {
				if (store[row][col] == piece::none) {
					moves.push_back(move(row, col));
				}
			}
		}

		return moves;
	}

	const piece operator[](const move& m) const {
		return store[m.row][m.col];
	}

	piece who_is_winning() const {
		const auto value {getValue(0)};
		const auto value_high {getValue(1)};

		const auto result_vertical {
			(value & 0x00ffffff) & ((value >> 24) & 0x00ffffff) & ((value >> 48) | (value_high << 16))
		};
		const auto result_vertical_collected {
			(result_vertical & 0xff) | ((result_vertical >> 8) & 0xff) | (result_vertical >> 16)
		};

		const auto result_horizontal {
			((value & 0xff0000ff0000ff) & ((value >> 8) & 0xff0000ff0000ff) & (((value >> 16) & 0xff0000ff0000ff) | (value_high << 48)))
		};

		const auto result_horizontal_collected {
			(result_horizontal & 0xff) | ((result_horizontal >> 24) & 0xff) | (result_horizontal >> 48)
		};

		const auto result_diagnol1 {
			value & (value >> 32) & value_high & 0xff
		};

		const auto result_diagnol2 {
			(value >> 16) & (value >> 32) & (value >> 48) & 0xff
		};

		const auto result { result_vertical_collected | result_horizontal_collected | result_diagnol1 | result_diagnol2 };
		return static_cast<piece>(result);
	}
};

std::ostream& operator<<(std::ostream& o, const Board& board) {
	o << "#########" << std::endl;
	for (int row = 0; row < Board::rowcount; row++) {
		o << '#';
		for (int col = 0; col < Board::colcount; col++) {
			o << ' ' << board[move(row, col)];
		}
		o << " #" << std::endl;
	}
	o << "#########" << std::endl;

	if (board.getCount() != 9) {
		o << "Move: " << board.getCount() + 1;
		o << "; Turn: " << board.getCurrentPiece() << std::endl;
	}

	return o;
}