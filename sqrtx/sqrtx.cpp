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
    static int mySqrt(int x) noexcept
    {
        double guess = 1;
        while (std::fabs(x - guess*guess) > 0.5) {
            printf("guess = %0.2f, guess ^ 2 = %0.2f\n", guess, guess*guess);
            guess = (guess + x / guess) / 2;
        }
        return guess;
    }

    static int mySqrt2(int x) noexcept
    {
        return std::sqrt(x);
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

    auto sol = Solution{}.mySqrt(j.get<int>());
    std::cout << sol << std::endl;
    auto sol2 = Solution{}.mySqrt2(j.get<int>());
    std::cout << sol2 << std::endl;

    return 0;
}
