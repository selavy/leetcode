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
    static vector<int> spiralOrder(vector<vector<int>>& matrix) noexcept
    {
        vector<int> result;
        if (matrix.empty() || matrix[0].empty())
            return result;
        int M = matrix.size();
        int N = matrix[0].size();

        int x0 = 0, x1 = N; // x = [x0, x1)
        int y0 = 0, y1 = M; // y = [y0, y1)

#if 0
        while (x1 - x0 > 1 && y1 - y0 > 1) {
            // top left -> top right
            for (int x = x0; x < x1; ++x) {
                result.push_back(matrix[y0][x]);
            }

            // top right -> bottom right
            for (int y = y0 + 1; y < y1; ++y) {
                result.push_back(matrix[y][x1-1]);
            }

            // bottom right -> bottom left
            for (int x = x1 - 2; x >= x0; --x) {
                result.push_back(matrix[y1-1][x]);
            }

            // bottom right -> top left - 1
            for (int y = y1 - 2; y > y0; --y) {
                result.push_back(matrix[y][x0]);
            }

            x0++; x1--;
            y0++; y1--;
        }

        // top left -> top right
        for (int x = x0; x < x1; ++x) {
            result.push_back(matrix[y0][x]);
        }

        // top right -> bottom right
        for (int y = y0 + 1; y < y1; ++y) {
            result.push_back(matrix[y][x1-1]);
        }
#endif

#if 1
        while (x0 < x1 && y0 < y1) {
            // top left -> top right
            for (int x = x0; x < x1; ++x) {
                result.push_back(matrix[y0][x]);
            }

            // top right -> bottom right
            for (int y = y0 + 1; y < y1; ++y) {
                result.push_back(matrix[y][x1-1]);
            }

            if (y1 - y0 > 1) {
                // bottom right -> bottom left
                for (int x = x1 - 2; x >= x0; --x) {
                    result.push_back(matrix[y1-1][x]);
                }

                if (x1 - x0 > 1) {
                    // bottom right -> top left - 1
                    for (int y = y1 - 2; y > y0; --y) {
                        result.push_back(matrix[y][x0]);
                    }
                }
            }

            x0++; x1--;
            y0++; y1--;
        }
#endif

        return result;
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

    json j;
    ifs >> j;

    vector<vector<int>> matrix;
    std::cout << "[\n";
    for (const auto& row : j) {
        matrix.emplace_back();
        std::cout << "\t[";
        for (auto x : row) {
            std::cout << " " << x << ",";
            matrix.back().emplace_back(x);
        }
        std::cout << " ],\n";
    }
    std::cout << "]\n";

    auto sol = Solution{}.spiralOrder(matrix);
    std::cout << "RESULT : [ ";
    for (auto x : sol)
        std::cout << x << " ";
    std::cout << "]\n";

    ifs >> j;
    vector<int> correct;
    for (auto e : j)
        correct.push_back(e);
    std::cout << "CORRECT: [ ";
    for (auto x : correct)
        std::cout << x << " ";
    std::cout << "]\n";

    if (!std::equal(correct.begin(), correct.end(), sol.begin(), sol.end()))
        std::cout << "!!! INCORRECT !!!\n\n";

    return 0;
}
