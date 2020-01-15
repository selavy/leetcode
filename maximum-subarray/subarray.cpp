#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>
#include <climits>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct Solution {
    // Kadane's algorithm
    static int maxSubArray(vector<int>& nums) noexcept {
        if (nums.empty()) return 0;
        int N = nums.size(), curr = nums[0], best = nums[0];
        for (int i = 1; i < N; ++i) {
            curr = std::max(nums[i], curr + nums[i]);
            best = std::max(best, curr);
        }
        return best;
    }


    // static int maxSubArray(vector<int>& nums) noexcept {
    //     if (nums.empty()) return 0;
    //     int result = INT_MIN;
    //     int N = nums.size();
    //     vector<int> A(N*N, 0);
    //     auto ix = [N](int x, int y) { return y*N + x; };
    //     for (int j = 0; j < N; ++j) {
    //         A[ix(j, j)] = nums[j];
    //         result = std::max(result, nums[j]);
    //         for (int i = j + 1; i < N; ++i) {
    //             assert((A[ix(i, j)] == nums[j] && A[ix(i-1, j)] == 0) || A[ix(i, j)] == 0);
    //             A[ix(i, j)] = A[ix(i-1, j)] + nums[i];
    //             result = std::max(result, A[ix(i, j)]);
    //         }
    //     }
    //     return result;
    // }
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " [FILE]" << std::endl;
        return 0;
    }
    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "error: unable to open input file: " << argv[1]
                  << std::endl;
        return 1;
    }
    json j;
    ifs >> j;
    vector<int> nums;
    for (auto& c : j) nums.push_back(c.get<int>());
    auto sol = Solution{}.maxSubArray(nums);
    std::cout << sol << std::endl;

    return 0;
}
