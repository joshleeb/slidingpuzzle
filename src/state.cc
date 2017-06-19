#include <algorithm>
#include <cmath>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "state.h"

state::state(std::vector<int> board) {
    this->board = board;
    this->board_width = (int) std::sqrt(board.size());

    if (board.size() <= 4) {
        throw std::invalid_argument("Board is too small");
    }
    if (std::pow(this->board_width, 2) != board.size()) {
        throw std::invalid_argument("Board is not a square");
    }
}

bool state::operator ==(const state &s) {
    return this->board == s.board;
}

void state::move_square(int square) {
    auto square_index = this->get_index(square);
    auto blank_index = this->get_index(BLANK);

    this->board[blank_index] = square;
    this->board[square_index] = BLANK;
}

std::vector<int> state::get_possible_moves() {
    auto moves = std::vector<int>();

    int blank_index = this->get_index(BLANK);
    int up_index = blank_index + this->board_width;

    // Up from blank.
    if (up_index >= 0 && (size_t) blank_index + this->board_width < this->board.size()) {
        moves.push_back(this->board[blank_index + this->board_width]);
    }

    // Down from blank.
    if (blank_index - this->board_width >= 0) {
        moves.push_back(this->board[blank_index - this->board_width]);
    }

    // Left from blank.
    if (blank_index % this->board_width > 0) {
        moves.push_back(this->board[blank_index - 1]);
    }

    // Right from blank.
    if (blank_index % this->board_width < this->board_width - 1) {
        moves.push_back(this->board[blank_index + 1]);
    }

    return moves;
}

int state::get_index(const int value) {
    auto it = std::find(this->board.begin(), this->board.end(), value);

    if (it == this->board.end()) return -1;
    return std::distance(this->board.begin(), it);
}

std::tuple<int, int> state::get_location(const int value) {
    auto index = this->get_index(value);

    return std::make_tuple(
        std::floor(index / this->board_width),  // x
        index % this->board_width               // y
    );
}

int state::get_fcost() {
    if (this->gcost == std::numeric_limits<int>::max()) return this->gcost;
    if (this->hcost == std::numeric_limits<int>::max()) return this->hcost;
    return this->gcost + this->hcost;
}

int state::get_board_width() {
    return this->board_width;
}