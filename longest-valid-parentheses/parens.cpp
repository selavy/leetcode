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
    // static int longestValidParentheses(string s) noexcept
    // {
    //     size_t result = 0;
    //     for (size_t i = 0, N = s.size(); i < N; ++i) {
    //         int count = 0;
    //         for (size_t j = i; j < N; ++j) {
    //             count += s[j] == '(' ? 1 : -1;
    //             if (count < 0)
    //                 break;
    //             if (count == 0)
    //                 result = std::max(result, j - i + 1);
    //         }
    //     }
    //     return result;
    // }

    static int longestValidParentheses(string s) noexcept
    {
        int N = s.size();
        int result = 0;
        int l = 0;      // left scan index [l, i]
        int r = N - 1;  // right scan index [N - i - 1, j]
        int count_l = 0;
        int count_r = 0;
        for (int i = 0; i < N; ++i) {
            // is [l, i] valid?
            count_l += (s[i] == '(') ? 1 : -1;
            if (count_l == 0) {
                result = std::max(result, i - l + 1);
            } else if (count_l < 0) { // too many ')'
                l = i + 1;
                count_l = 0;
            }

            // is [j, r] valid?
            int j = N - i - 1;
            count_r += (s[j] == '(') ? 1 : -1;
            if (count_r == 0) {
                result = std::max(result, r - j + 1);
            } else if (count_r > 0) {
                r = j - 1;
                count_r = 0;
            }
        }
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

    auto sol = Solution{}.longestValidParentheses(j.get<string>());
    std::cout << sol << std::endl;

    return 0;
}
