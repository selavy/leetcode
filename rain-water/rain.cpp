#include <cstdio>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "json.hpp"

#define panic(fmt, ...) do { fprintf(stderr, "ERR: " fmt "\n", ##__VA_ARGS__); exit(1); } while(0)

using json = nlohmann::json;

#if 1

class Solution {
public:
    static int trap(std::vector<int>& height) {
        int r, l = 0, water = 0, n = height.size();
        while (l < n) {
            r = l + 1;
            while (r < n && height[r] <= height[l]) ++r;

            // // invariant: l < r AND height in range (l, r) is all lower than min(height[l], height[r])
            // int minh = std::min(height[l], r != n ? height[r] : height[n-1]);
            // printf("l=%d, r=%d, minh=%d\n", l, r, minh);
            // for (int i = l + 1; i < r; ++i) {
            //     if (height[i] < minh) {
            //         printf("\tcolumn: %d, minh: %d, height: %d, add: %d\n", i, minh, height[i], minh - height[i]);
            //         water += minh - height[i];
            //     }
            // }
            // l = r;

            if (r < n && height[r] >= height[l]) {
                int minh = std::min(height[l], height[r]);
                for (int i = l + 1; i < r; ++i) {
                    assert(i < n);
                    assert(height[i] <= minh);
                    water += minh - height[i];
                }
                l = r;
            } else { // handle falling off right edge
                // ++l;
                int minh = std::min(height[l], height[n-1]);
                for (int i = l + 1; i < n; ++i) {
                    if (minh > height[i])
                        water += minh - height[i];
                }
                break;
            }
        }
        return water;
    }
};

#else

#if 0
class Solution {
public:
    static int find(int x, const int* data, int n) noexcept {
        for (int i = 0; i < n; ++i) {
            if (data[i] >= x)
                return i;
        }
        return -1;
    }

    static int rfind(int x, const int* data, int n) noexcept {
        for (int i = n - 1; i >= 0; --i) {
            if (data[i] >= x)
                return i;
        }
        return -1;
    }

    int trap(std::vector<int>& height) {
        int water = 0;
        std::vector<int> levels = height;
        std::sort(levels.begin(), levels.end());
        levels.erase(std::unique(levels.begin(), levels.end()), levels.end());
        int prev = 0;
        for (int level : levels) {
            int l = find(level, height.data(), height.size());
            int r = rfind(level, height.data(), height.size());
            if (l == -1 || r == -1 || l >= r) {
                continue;
            }
            int diff = level - prev;
            for (int i = l + 1; i < r; ++i) {
                if (height[i] < level) {
                    water += diff;
                }
            }
            prev = level;
        }
        return water;
    }
};
#else
class Solution {
public:
    static int find(int x, const int* data, int n) noexcept {
        for (int i = 0; i < n; ++i) {
            if (data[i] >= x)
                return i;
        }
        return -1;
    }

    static int rfind(int x, const int* data, int n) noexcept {
        for (int i = n - 1; i >= 0; --i) {
            if (data[i] >= x)
                return i;
        }
        return -1;
    }

    int trap(std::vector<int>& height) {
        int water = 0;
        int maxh = *std::max_element(height.begin(), height.end());
        int minl = std::min(*std::min_element(height.begin(), height.end()), 0);
        for (int level = minl + 1; level <= maxh; ++level) {
            int l = find(level, height.data(), height.size());
            int r = rfind(level, height.data(), height.size());
            if (l == -1 || r == -1 || l >= r) {
                continue;
            }
            assert(l != -1);
            assert(r != -1);
            assert(l < r);
            // printf("level = %d, (%d, %d)\n", level, l, r);
            for (int i = l + 1; i < r; ++i) {
                if (height[i] < level) {
                    // printf("\t%d\n", i);
                    ++water;
                }
            }
        }
        return water;
    }
};
#endif
#endif

// ----------------------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s [FILE]\n", argv[0]);
        return 0;
    }

    const char* filename = argv[1];
    std::ifstream ifs(filename);
    if (!ifs) {
        panic("error: unable to open %s", filename);
    }

    json j;
    ifs >> j;

    if (!j.is_array()) {
        panic("error: invalid input");
    }

    std::vector<int> input;
    for (auto& row : j) {
        for (auto& c : row) {
            if (!c.is_number()) {
                panic("error: invalid input, expected number");
            }
            auto n = c.get<int>();
            input.push_back(n);
        }
    }

    printf("INPUT:\n");
    for (auto i : input) {
        printf("%d ", i);
    }
    printf("\n");
    int result = Solution{}.trap(input);
    printf("RESULT: %d\n", result);

    return 0;
}
