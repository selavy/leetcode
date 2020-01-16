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
        int N = nums.size();
        for (int i = 0; i < N; ++i) {
            for (;;) {
                if (!(1 <= nums[i] && nums[i] <= N))
                    break;
                if (nums[i] == i + 1)
                    break;
                if (nums[i] == nums[nums[i]-1])
                    break;
                std::swap(nums[i], nums[nums[i]-1]);
            }
        }
        for (int i = 0; i < N; ++i) {
            if (nums[i] != i + 1)
                return i + 1;
        }
        return N+1;
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
