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
    static bool isMatch(string text, string pat) noexcept
    {
        // DP Solution:
        // 2-d, A[i][j] => does text [0,i) match with pat [0,j)?
        // A[i][j] <= {
        //     if pat[j-1] = '?':       A[i-1][j-1]; // pattern is a single-char wildcard, carry forward
        //     if pat[j-1] = text[i-1]: A[i-1][j-1]; // pattern matches text char, carry forward
        //     if pat[j-1] = '*':       A[i-1][j] || A[i][j-1]; // wildcard, either consume a text char or a pattern char
        // }
        // A[0][0] <= true;                      (empty pat matches empty text)
        // A[0][j] <= (pat = '*') && A[0][j-1]; (handle pat starting with *'s)
        int N = text.size() + 1;
        int M = pat.size() + 1;
        vector<int> A(N*M, 0);
        auto ix = [N,M](int i, int j)
        {
            assert(0 <= i && i < N);
            assert(0 <= j && j < M);
            return i*M + j;
        };
        A[ix(0,0)] = true;
        for (int j = 1; j < M; ++j)
            A[ix(0,j)] = pat[j-1] == '*' && A[ix(0,j-1)];
        for (int i = 1; i < N; ++i) {
            for (int j = 1; j < M; ++j) {
                if (pat[j-1] == '?' || pat[j-1] == text[i-1])
                    A[ix(i,j)] = A[ix(i-1,j-1)];
                else if (pat[j-1] == '*')
                    A[ix(i,j)] = A[ix(i-1,j)] || A[ix(i,j-1)];
            }
        }
        return A[ix(N-1,M-1)];
    }

    // static bool matchstar(const char* pat, const char* str) noexcept
    // {
    //     while (pat[0] == '*')
    //         ++pat;
    //     do {
    //         if (match(pat, str))
    //             return true;
    //     } while (*str++ != '\0');
    //     return false;
    // }

    // static bool match(const char* pat, const char* str) noexcept
    // {
    //     if (pat[0] == '\0')
    //         return str[0] == '\0';
    //     else if (pat[0] == '*')
    //         return matchstar(pat + 1, str);
    //     else if (str[0] != '\0' && (pat[0] == '?' || pat[0] == str[0]))
    //         return match(pat + 1, str + 1);
    //     return false;
    // }

    // static bool isMatch(string s, string p) noexcept
    // {
    //     return match(p.c_str(), s.c_str());
    // }
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

#if 1
    vector<tuple<string, string, bool>> cases = {
        // string   , pattern   , expect
        { "aa"       , "aa"     , true  },
        { "aa"       , "a"      , false },
        { "aa"       , "*"      , true  },
        { ""         , "*"      , true  },
        { ""         , "?"      , false },
        { "aaaa"     , "b*"     , false },
        { "adceb"    , "*a*b"   , true  },
        { "adcebe"   , "*a*b"   , false },
        { "acdcb"    , "a*c?b"  , false },
        { "cb"       , "?a"     , false },
        { ""         , "*?"     , false },
        { "a"        , "*?"     , true  },
        { "aa"       , "*?"     , true  },
        { "ho"       , "ho**"   , true  },
        { "ho"       , "ho***"  , true  },
        { "hoh"      , "ho***h" , true  },
        { "hoj"      , "ho***h" , false },
        { "hoj"      , "***ho*h", false },
        { "hoh"      , "**ho*h" , true  },
        { "hoh"      , "***ho*h", true  },
    };

    for (auto&& c : cases) {
        auto str = std::get<0>(c);
        auto pat = std::get<1>(c);
        auto exp = std::get<2>(c);
        bool res = Solution{}.isMatch(str, pat);
        if (res != exp) {
            printf("\n\n!!!! FAILED !!!!\n");
            printf("string  = '%s'\n", str.c_str());
            printf("pattern = '%s'\n", pat.c_str());
            printf("result  = %s\n", (res ? "true" : "false"));
            printf("expect  = %s\n", (exp ? "true" : "false"));
            printf("\n");
        }
        // assert(res == exp);
    }
#endif

    json j;
    ifs >> j;
    auto s = j.get<string>();
    ifs >> j;
    auto p = j.get<string>();

    auto sol = Solution{}.isMatch(s, p);
    std::cout << (sol ? "true" : "false") << std::endl;

    return 0;
}
