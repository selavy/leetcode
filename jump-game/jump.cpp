#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <climits>
#include <cstdint>
#include <cinttypes>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Solution
{
    static bool canJump(const vector<int>& nums) noexcept
    {
        int N = nums.size();
        if (N <= 1) return true;
        int dest = N - 1, cur = 0, idx = 0;
        for (int i = 0; i < N; ++i) {
            cur = std::max(cur, i + nums[i]);
            if (i == idx) {
                idx = cur;
                if (cur >= dest) {
                    return true;
                }
            }
        }
        return false;
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

    vector<int> nums;
    std::cout << "[ ";
    for (auto& c : j) {
        nums.push_back(c.get<int>());
        std::cout << c.get<int>() << " ";
    }
    std::cout << "]\n";
    auto sol = Solution{}.canJump(nums);
    std::cout << "RESULT: " << std::boolalpha << sol << std::endl;

    ifs >> j;
    bool expect = j.get<bool>();
    std::cout << "EXPECT: " << std::boolalpha << expect << std::endl;

    if (sol != expect)
        std::cout << "\n!!! INCORRECT !!!\n\n";
    std::cout << std::endl;

    return 0;
}
