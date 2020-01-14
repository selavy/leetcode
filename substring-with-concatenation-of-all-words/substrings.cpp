#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <vector>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

class Solution {
public:
    static int totalWordsLength(const vector<string>& ws) noexcept {
        return ws.empty() ? 0 : ws.size() * ws[0].size();
    }

    static bool startsWith(string_view sv, const std::string& word) noexcept {
        return sv.compare(0, word.size(), word.c_str()) == 0;
    }

    static bool isPerm(string_view str, vector<string> words) noexcept {
        int pos = 0;
        while (!str.empty()) {
            auto found = std::find_if(words.begin(), words.end(),
                [str](const string& word) { return startsWith(str, word); }
            );
            if (found == words.end())
                return false;
            str.remove_prefix(found->size());
            words.erase(found);
        }
        return words.empty();
    }

    static vector<int> findSubstring(string s, vector<string>& words) noexcept {
        vector<int> results;
        if (words.empty() || s.empty())
            return results;
        std::size_t len = totalWordsLength(words);
        int N = s.size() - len + 1;
        for (int pos = 0; pos < N; ++pos) {
            string_view ss{&s[pos], len};
            if (isPerm(ss, words)) {
                results.push_back(pos);
            }
        }
        return results;
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
    for (auto i : result)
        std::cout << i << ",";
    std::cout << "]\n";
    return 0;
}
