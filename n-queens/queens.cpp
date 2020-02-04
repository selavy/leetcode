#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Solution
{
    static bool islegal(const vector<string>& board, const int r, const int c)
    {
        const int n = board.size();
        for (int i = 0; i < n; ++i) {
            if (board[r][i] != '.')
                return false;
            if (board[i][c] != '.')
                return false;
            if (r + i < n && c + i < n && board[r+i][c+i] != '.')
                return false;
            if (r - i >= 0 && c - i >= 0 && board[r-i][c-i] != '.')
                return false;
            if (r + i < n && c - i >= 0 && board[r+i][c-i] != '.')
                return false;
            if (r - i >= 0 && c + i < n && board[r-i][c+i] != '.')
                return false;
        }
        return true;
    }

    static void solve(vector<string>& board, int r, int n, vector<vector<string>>& sols)
    {
        if (r >= n) {
            sols.emplace_back(board);
        } else {
            for (int i = 0; i < n; ++i) {
                if (islegal(board, r, i)) {
                    board[r][i] = 'Q';
                    solve(board, r+1, n, sols);
                    board[r][i] = '.';
                }
            }
        }
    }

    static vector<vector<string>> solveNQueens(int n) noexcept
    {
        vector<vector<string>> sols;
        vector<string> board(n, string(n, '.'));
        solve(board, 0, n, sols);
        return sols;
    }
};

int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " [FILE]" << std::endl;
        return 0;
    }

    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "error: unable to open input file: " << argv[1] << std::endl;
        return 1;
    }

    auto print = [](const vector<string>& board)
    {
        std::cout << "  [\n";
        for (const auto& row : board) {
            std::cout << "    \"" << row << "\",\n";
        }
        std::cout << "  ],\n";
    };
    {
        vector<tuple<vector<string>, pair<int, int>, bool>> checks = {
            {
                {
                    "....",
                    "....",
                    "....",
                    "....",
                },
                { 0, 0 }, // { row, col }
                true
            },
            {
                {
                    "....",
                    "....",
                    "....",
                    "....",
                },
                { 0, 1 }, // { row, col }
                true
            },
            {
                {
                    "Q...",
                    "....",
                    "....",
                    "....",
                },
                { 0, 1 }, // { row, col }
                false
            },
            {
                {
                    "Q...",
                    "....",
                    "....",
                    "....",
                },
                { 1, 0 }, // { row, col }
                false
            },
            {
                {
                    ".Q..",
                    "...Q",
                    "....",
                    "....",
                },
                { 2, 0 }, // { row, col }
                true
            },
        };

        for (auto&& t : checks) {
            auto& board = std::get<0>(t);
            auto coords = std::get<1>(t);
            auto expect = std::get<2>(t);
            auto result = Solution::islegal(board, coords.first, coords.second);
            if (result != expect) {
                std::cout << "!!! FAILED !!!\n";
                print(board);
                std::cout << "row = " << coords.first << ", col = " << coords.second << "\n";
                board[coords.first][coords.second] = 'Q';
                std::cout << "\n\n";
                print(board);
                std::cout << "\n\n";
                std::cout << "Expected: " << (expect ? "true" : "false") << "\n";
                std::cout << "Result  : " << (result ? "true" : "false") << "\n";
            }
            assert(result == expect);
        }
        printf("Passed.\n");
    }

    json j;
    ifs >> j;


    auto sols = Solution{}.solveNQueens(j.get<int>());
    std::cout << "[\n";
    for (const auto& sol : sols) {
        print(sol);
    }
    std::cout << "]\n";

    return 0;
}
