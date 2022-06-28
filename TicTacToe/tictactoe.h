#include <iostream>


class tictactoe {
public:
    enum class piece {
        empty,
        x,
        o
    };

    static constexpr size_t max_row { 3 };
    static constexpr size_t max_col { 3 };
    static constexpr size_t max_move { 9 };

private:
    piece board[max_row][max_col] { piece::empty };
    size_t current_move { 0 };

    static constexpr int max_score { 48 };
    static constexpr int multiplier[] { 0, -1, 1 };
    static constexpr auto get_multiplier(const piece turn) {
        return multiplier[static_cast<size_t>(turn)];
    }
    auto get_score() {
        return get_multiplier(who_is_winning()) * 
                (max_score - static_cast<int>(get_current_move()));
    }

public:

    bool make_move(const std::pair<size_t, size_t> &pos) {
        auto &curr_pos { board[pos.first][pos.second]};
        if (curr_pos != piece::empty) return false;
        curr_pos = get_current_piece();
        ++current_move;
        return true;
    }

    void undo_move_fast(const std::pair<size_t, size_t> &pos) {
        board[pos.first][pos.second] = piece::empty;
        --current_move;
    }
    
    int get_current_move() const { return current_move; }
    piece get_current_piece() const { return static_cast<piece>(current_move % 2 + 1); }

    bool game_over() const { return get_current_move() == max_move; }

    piece who_is_winning() const {
        // Horizontal
        for(size_t row {0}; row < max_row; ++row) {
            auto &cols { board[row] };
            if (cols[0] == cols[1] and cols[1] == cols[2] and cols[0] != piece::empty) return cols[0];
        }

        // Vertical
        for(size_t col {0}; col < max_col; ++col) {
            if (board[0][col] == board[1][col] and board[1][col] == board[2][col] and board[0][col] != piece::empty)
                return board[0][col];
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != piece::empty) return board[0][0];
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != piece::empty) return board[0][2];
        return piece::empty;
    }

    bool auto_move() {
        if (get_current_move() == max_move) return false;
        auto next_move = get_next_move();
        return make_move(next_move);
    }

    std::pair<size_t, size_t> get_next_move(const int depth = 9)
    {
        const auto curr_piece { get_current_piece() };
        int score { get_multiplier(curr_piece) * 1000 * -1 };
        std::pair<size_t, size_t> next_pos {0, 0};
        for(size_t row {0}; row < max_row; ++row) {
            for(size_t col {0}; col < max_col; ++col) {
                auto &curr_pos {board[row][col]};
                if (curr_pos == piece::empty) {
                    curr_pos = curr_piece;
                    ++current_move;
                    const auto next_score { get_min_max(depth - 1) };
                    if (curr_piece == piece::x) {
                        if (next_score < score) {
                            next_pos = {row, col};
                            score = next_score;
                        }
                    } else {
                        if (next_score > score) {
                            next_pos = {row, col};
                            score = next_score;
                        }
                    }
                    curr_pos = piece::empty;
                    --current_move;
                }
            }
        }
        return next_pos;
    }

    int get_min_max(const int depth) {
        auto board_score { get_score() };
        if (board_score or !depth or current_move == max_move) {
            return board_score;
        }
        const auto curr_piece { get_current_piece() };
        int score { get_multiplier(curr_piece) * 1000 * -1 };
        int empty_count { 0 };
        for(size_t row {0}; row < max_row; ++row) {
            for(size_t col {0}; col < max_col; ++col) {
                auto &curr_pos {board[row][col]};
                if (curr_pos == piece::empty) {
                    ++empty_count;
                    curr_pos = curr_piece;
                    ++current_move;
                    const auto next_score { get_min_max(depth - 1) };
                    score = curr_piece == piece::x ?
                        std::min(score, next_score) : std::max(score, next_score);
                    curr_pos = piece::empty;
                    --current_move;
                }
            }
        }
        if (empty_count == 0) return 0;
        return score;
    }

private:
    friend std::ostream &operator<<(std::ostream &os, const tictactoe &engine);
};

std::ostream &operator<<(std::ostream &os, const tictactoe::piece piece) {
    switch(piece) {
        default:
        case tictactoe::piece::empty:
            return os << ' ';
        
        case tictactoe::piece::x:
            return os << 'x';

        case tictactoe::piece::o:
            return os << 'o';
    }
}

inline std::ostream &operator<<(std::ostream &os, const tictactoe &engine) {
    os << "#########\n";
    for(size_t row { 0 }; row < tictactoe::max_row; ++row) {
        os << "#";
        for(size_t col { 0 }; col < tictactoe::max_col; ++col) {
            os << ' ' << engine.board[row][col];
        }
        os << " #\n";
    }
    os << "#########\n";

    if (engine.game_over()) {
		const auto whoIsWinning = engine.who_is_winning();
		os << "GAME OVER - ";
		if (whoIsWinning == tictactoe::piece::empty) {
			os << "DRAW" << std::endl;
		}
		else {
			os << "WINNING: " << whoIsWinning << std::endl;
		}
	}

    return os;
}