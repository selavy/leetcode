#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

void print(const vector<vector<int>>& m)
{
    int N = m.size();
    std::cout << "[\n";
    for (int i = 0; i < N; ++i) {
        std::cout << "\t[ ";
        for (int j = 0; j < N; ++j) {
            // std::cout << m[i][j];
            printf("%2d ", m[i][j]);
            if (j != N - 1)
                std::cout << ",";
        }
        std::cout << "]\n";
        if (i != N - 1)
            std::cout << ",";
    }
    std::cout << "\n]\n";
}

struct Solution
{
    static void rotate(vector<vector<int>>& matrix) noexcept
    {
        int tmp, N = matrix.size();
        for (int j = 0; j < N / 2; ++j) {
            for (int i = j; i < N - j - 1; ++i) {
                tmp              = matrix[j][i];
                matrix[j    ][i    ] = matrix[N-1-i][j    ];
                matrix[N-1-i][j    ] = matrix[N-1-j][N-1-i];
                matrix[N-1-j][N-1-i] = matrix[i    ][N-1-j];
                matrix[i    ][N-1-j] = tmp;
            }
        }
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
    for (auto&& row : j) {
        matrix.emplace_back();
        for (auto&& c : row) {
            matrix.back().emplace_back(c.get<int>());
        }
    }

    print(matrix);
    Solution{}.rotate(matrix);
    print(matrix);

    return 0;
}
