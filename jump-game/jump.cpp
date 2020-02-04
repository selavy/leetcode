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
    static int jump(const vector<int>& nums) noexcept
    {
        int N = nums.size();
        if (N <= 1) return 0;
        int dest = N - 1, cur = 0, idx = 0, hops = 0;
        for (int i = 0; i < N; ++i) {
            cur = std::max(cur, i + nums[i]);
            if (i == idx) {
                idx = cur;
                ++hops;
                if (cur >= dest) break;
            }
        }
        return hops;
    }

    struct Comp {
        bool operator()(pair<int, int> lhs, pair<int, int> rhs) noexcept
        {
            // return lhs.second > rhs.second && lhs.first > rhs.first;
            // return lhs.first > rhs.first && lhs.second > rhs.second;
            return (lhs.first * lhs.second) < (rhs.first * rhs.second);
        }
    };

    static void push(vector<pair<int, int>>& q, int pos, int hops) noexcept
    {
        // printf("\tPUSH(%d,%d)\n", pos, hops);
        q.emplace_back(pos, hops);
        std::push_heap(q.begin(), q.end(), Comp{});
    }

    static pair<int, int> pop(vector<pair<int, int>>& q) noexcept
    {
        auto result = q[0];
        std::pop_heap(q.begin(), q.end(), Comp{});
        q.pop_back();
        return result;
    }

    static int jump3(const vector<int>& nums) noexcept
    {
        //          pos, hops
        int N = nums.size();
        printf("N = %d\n", N-1);
        if (N <= 1) return 0;
        vector<pair<int, int>> q;
        q.emplace_back(0, 0);
        while (!q.empty()) {
            auto&& [pos, hops] = pop(q);
            printf("Visiting (%d,%d) with jumps %d\n", pos, hops, nums[pos]);
            assert(0 <= pos && pos < N);
            for (int i = nums[pos]; i > 0; --i) {
                if (pos + i >= (N-1))
                    return hops + 1;
                push(q, pos + i, hops + 1);
            }
        }
        assert(false);
        return 0;
    }

    static int jump2(const vector<int>& nums) noexcept
    {
        int N = nums.size();
        vector<int64_t> A(N, INT_MAX);
        assert(A.size() == N);
        A[0] = 0;
        for (int i = 0; i < N; ++i) {
             for (int t = 1; t <= nums[i]; ++t) {
                 if (!(i+t < N)) break;
                 A[i+t] = std::min(A[i+t], A[i]+1);
             }
        }
        return A[N-1];
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
    for (auto& c : j)
        nums.push_back(c.get<int>());
    auto sol = Solution{}.jump(nums);
    std::cout << sol << std::endl;

    return 0;
}
