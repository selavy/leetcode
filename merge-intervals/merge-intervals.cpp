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
    static vector<vector<int>> merge(vector<vector<int>>& intervals) noexcept
    {
        std::sort(
            intervals.begin(),
            intervals.end(),
            [](const vector<int>& lhs, const vector<int>& rhs)
            {
                return lhs[0] < rhs[0];
            }
        );
        vector<vector<int>> result;
        for (const auto& ival : intervals) {
            if (result.empty() || result.back()[1] < ival[0])
                result.push_back(ival);
            else
                result.back()[1] = std::max(result.back()[1], ival[1]);
        }
        return result;

        // std::sort(intervals.begin(),
        //         intervals.end(),
        //         [](const vector<int>& lhs, const vector<int>& rhs)
        //         {
        //             return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
        //         });
        // auto it = intervals.begin();
        // while (it != intervals.end()) {
        //     auto nt = it + 1;
        //     if (nt == intervals.end())
        //         break;
        //     if ((*it)[1] < (*nt)[0]) {
        //         ++it;
        //     } else {
        //         (*nt)[0] = std::min((*it)[0], (*nt)[0]);
        //         (*nt)[1] = std::max((*it)[1], (*nt)[1]);
        //         it = intervals.erase(it);
        //     }
        // }

        // return intervals;
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
    for (const auto vs : j) {
        intervals.emplace_back();
        for (auto v : vs)
            intervals.back().push_back(v.get<int>());
    }

    auto sol = Solution{}.merge(intervals);
    printf("[");
    for (const auto vs : sol) {
        printf("[%d,%d],", vs[0], vs[1]);
    }
    printf("]\n");

    return 0;
}
