#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_set>


int findIsland(std::vector<std::vector<char>> &universe) {
    constexpr std::array<std::pair<int, int>, 4> directions {{
        {0, -1}, {0, 1}, {1, 0}, {-1, 0}
    }};
    int island_count { 0 };
    if (universe.empty()) return 0;
    const int rows = static_cast<int>(universe.size());
    const int cols = static_cast<int>(universe[0].size());

    for(int row { 0 }; row < rows; ++row) {
        for(int col { 0 }; col < cols; ++col) {
            if (universe[row][col] == 0) continue;

            std::stack<std::pair<int, int>> to_visit { };
            to_visit.push({row, col});
            universe[row][col] = 0;
            ++island_count;
            while(!to_visit.empty()) {
                auto visiting = to_visit.top();
                to_visit.pop();
                for(auto &direction: directions) {
                    const auto new_row = visiting.first + direction.first;
                    const auto new_col = visiting.second + direction.second;
                    if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols && universe[new_row][new_col] != 0) {
                        to_visit.push({new_row, new_col});
                        universe[new_row][new_col] = 0;
                    }
                }
            }

        }
    }

    return island_count;
}

std::ostream &operator<<(std::ostream &os, const std::vector<char> &values) {
    os << "{ ";
    for(auto &val: values) {
        os << static_cast<int>(val) << ' ';
    }
    return os << '}';
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<char>> &grid) {
    for(auto &row: grid) {
        os << row << "\n";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::pair<std::vector<std::vector<char>>, int> &test) {
    os << test.first;
    return os << "Expected Island: " << test.second << "\n";
}

int main(int, char**) {
    std::vector<std::pair<std::vector<std::vector<char>>, int>> tests {
        std::make_pair(
            std::vector<std::vector<char>> {{1, 1, 0}, {1, 0, 0}, {0, 0, 1}},
            2
        ),
        std::make_pair(
            std::vector<std::vector<char>> {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}},
            0
        ),
        std::make_pair(
            std::vector<std::vector<char>> {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}},
            1
        ),
        std::make_pair(
            std::vector<std::vector<char>> {{1, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}, {1, 0, 0, 1}},
            4
        ),
        std::make_pair(
            std::vector<std::vector<char>> {{1, 0, 0, 1}, {0, 1, 0, 0}, {0, 0, 1, 0}, {1, 0, 0, 1}},
            6
        ),

    };

    for(auto &test: tests) {
        std::cout << test;
        auto result = findIsland(test.first);
        std::cout << "Found Island: " << result << std::endl;
    }
    return 0;
}