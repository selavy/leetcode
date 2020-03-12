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
    static vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) noexcept
    {
        int n = intervals.size();
        int x = newInterval[0];
        int y = newInterval[1];
        int i, j;
        for (i = 0; i < n; ++i) {
            if (intervals[i][0] <= x && x <= intervals[i][1]) {
                break;
            }
        }
        if (i == n) {
            intervals.emplace_back(newInterval);
            return intervals;
        }

        for (j = i + 1; j < n; ++j) {
            if (!(y > intervals[j][1]))
                break;
        }

        intervals.erase(intervals.begin()+i+1, intervals.begin()+j);

        if (x < intervals[i][0]) {
        } else if (x > intervals[i][0]) {
        } else {
        }

        // int n = 2*intervals.size();
        // auto ix = [&intervals](int i) -> int { return intervals[i/2][i%2]; };
        // int l, r;
        // for (l = 0; l < n; l+=2) {
        //     if (!(ix(l) < newInterval[0]))
        //         break;
        // }
        // for (r = n - 1; r >= 0; --r) {
        //     if (!(newInterval[1] < ix(r)))
        //         break;
        // }

        // if (l == n) {
        //     intervals.emplace_back(newInterval);
        //     return intervals;
        // } else if (l % 2 == 1) {
        //     intervals[l/2][1] = newInterval[0];
        // }

        // if (r == n) {
        //     intervals.back()[1] = newInterval[1];
        // } else if (r % 2 == 1) {
        //     intervals[r/2][1] = newInterval[1];
        // }

        // printf("l = %d, r = %d\n", l, r);
        return intervals;
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

    vector<vector<int>> intervals;
    for (const auto& row : j) {
        intervals.emplace_back();
        for (auto i : row)
            intervals.back().push_back(i.get<int>());
    }

    ifs >> j;
    vector<int> newInterval;
    for (auto i : j) {
        newInterval.push_back(i.get<int>());
    }

    auto sol = Solution{}.insert(intervals, newInterval);
    printf("[");
    for (const auto& row : sol) {
        printf("[");
        for (auto i : row)
            printf("%d,", i);
        printf("],");
    }
    printf("]\n");

    return 0;
}
