#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <climits>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Solution
{
    static int firstMissingPositive(vector<int>& nums) noexcept
    {
        // O(n) + O(n*log(n)) => O(n*log(n)) solution
        if (std::find(nums.begin(), nums.end(), 1) == nums.end()) return 1;
        std::sort(nums.begin(), nums.end());
        int i, n;
        for (i = 0, n = nums.size(); i < n - 1; ++i) {
            if (nums[i] <= 0)             continue;
            if (nums[i] == nums[i+1])     continue;
            if (nums[i] == nums[i+1] - 1) continue;
            break;
        }
        return nums[i] + 1;
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
    for (const auto& c : j)
        nums.push_back(c.get<int>());
    auto sol = Solution{}.firstMissingPositive(nums);
    std::cout << sol << std::endl;

    return 0;
}
