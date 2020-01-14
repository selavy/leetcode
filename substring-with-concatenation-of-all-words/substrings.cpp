#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Solution {
   public:
    using Counter = unordered_map<string_view, int>;

    static bool allZero(const Counter& c) noexcept {
        for (const auto& p : c)
            if (p.second != 0) return false;
        return true;
    }

    static void pp(const Counter& c) noexcept {
        for (auto&& p : c) {
            std::cout << p.first << "=" << p.second << ", ";
        }
        std::cout << "\n";
    }

    static vector<int> findSubstring(string s, vector<string>& words) noexcept {
        vector<int> results;
        auto wlen = words[0].size();
        auto nwords = words.size();
        auto tlen = wlen * nwords;
        auto slen = s.size();
        size_t l, r;
        string_view sv{s};
        for (size_t i = 0; i < wlen; ++i) {
            Counter counter;
            for (const auto& word : words)
                counter[word] += 1;
            l = r = i;
            while (r + wlen <= slen) {
                counter[sv.substr(r, wlen)] -= 1;
                r += wlen;
                if ((r - l) > tlen) {
                    counter[sv.substr(l, wlen)] += 1;
                    l += wlen;
                }
                if ((r - l) == tlen && allZero(counter)) results.push_back(l);

                if ((r - l) == tlen) {
                    std::cout << sv.substr(l, tlen) << " -- "; //  << std::endl;
                    pp(counter);
                }
            }
            std::cout << "\n\n";
        }
        return results;
    }
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " [FILE]" << std::endl;
        return 0;
    }
    std::ifstream ifs(argv[1]);
    if (!ifs) {
        std::cerr << "error: unable to open " << argv[0] << std::endl;
        return 1;
    }
    json j;
    ifs >> j;
    auto s = j.get<string>();
    ifs >> j;
    vector<string> words;
    for (auto& w : j) {
        words.push_back(w.get<string>());
    }
    auto result = Solution{}.findSubstring(s, words);
    std::cout << "[";
    for (auto i : result) std::cout << i << ",";
    std::cout << "]\n";
    return 0;
}
