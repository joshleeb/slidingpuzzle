#pragma once

#include <memory>
#include <deque>

#include "state.h"

#define MOVEMENT_COST 1

typedef int (*puzzle_heuristic)(state &s1, state &s2);

class puzzle {
    std::shared_ptr<state> init;
    std::shared_ptr<state> goal;

    // Count of nodes expanded in A* search.
    int expanded_nodes;

    // Construct the path from the A* search tree.
    std::deque<state> construct_path();

    public:
    puzzle(std::shared_ptr<state> init, std::shared_ptr<state> goal);

    bool is_solvable();
    std::deque<state> solve(puzzle_heuristic heuristic);

    int get_expanded_nodes();
};