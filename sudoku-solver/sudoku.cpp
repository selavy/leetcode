#include <cstdio>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include "json.hpp"

#define panic(fmt, ...) do { fprintf(stderr, "ERR: " fmt "\n", ##__VA_ARGS__); exit(1); } while(0)

using json = nlohmann::json;

void print_board(const std::vector<std::vector<char>>& b) {
    for (int y = 0; y < 9; ++y) {
        if (y != 0 && y % 3 == 0) {
            printf("-------------------\n");
        }
        for (int x = 0; x < 9; ++x) {
            if (x != 0 && x % 3 == 0) {
                printf("|");
            }
            printf("%c ", b[y][x]);
        }
        printf("\n");
    }
}

// -----------------------------------------------------------------------------------------------

struct masks_t {
    uint16_t  row[9];
    uint16_t  col[9];
    uint16_t  box[9];
};

constexpr uint16_t ALLNUMS = 0x1ffu;
constexpr int lsb(uint32_t x) { return __builtin_ctz(x); }
constexpr int ix(int x, int y) { return y*9 + x; }
constexpr int bi(int x, int y) { return (y / 3)*3 + (x / 3); }

static void init(const std::vector<std::vector<char>>& brd, masks_t* m) noexcept {
    for (int i = 0; i < 9; ++i) {
        m->row[i] = ALLNUMS;
        m->col[i] = ALLNUMS;
        m->box[i] = ALLNUMS;
    }
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            if (brd[y][x] != '.') {
                int n = brd[y][x] - '1';
                m->row[x]        &= ~(1u << n);
                m->col[y]        &= ~(1u << n);
                m->box[bi(x, y)] &= ~(1u << n);
            }
        }
    }
}

static void easy(std::vector<std::vector<char>>& brd, masks_t* m) noexcept {
    for (int y = 0; y < 9; ++y) {
        for (int x = 0; x < 9; ++x) {
            if (brd[y][x] != '.') continue;
            uint16_t msk = m->row[x] & m->col[y] & m->box[bi(x, y)];
            if ((msk & (msk - 1)) == 0) {
                int n = lsb(msk);
                brd[y][x] = '1' + n;
                m->row[x]        &= ~(1u << n);
                m->col[y]        &= ~(1u << n);
                m->box[bi(x, y)] &= ~(1u << n);
            }
        }
    }
}

static bool solve(std::vector<std::vector<char>>& brd, masks_t* m) noexcept {
    int y, x;
    for (y = 0; y < 9; ++y) {
        for (x = 0; x < 9; ++x) {
            if (brd[y][x] == '.') goto continue_solving;
        }
    }
    return true;

continue_solving:
    int b = bi(x, y);
    uint16_t posmoves = m->row[x] & m->col[y] & m->box[b];
    while (posmoves > 0) {
        int n = lsb(posmoves);
        brd[y][x] = '1' + n;
        m->row[x] &= ~(1u << n);
        m->col[y] &= ~(1u << n);
        m->box[b] &= ~(1u << n);
        if (solve(brd, m))
            return true;
        else {
            m->row[x] |= 1u << n;
            m->col[y] |= 1u << n;
            m->box[b] |= 1u << n;
        }
        posmoves &= posmoves - 1;
    }
    brd[y][x] = '.';
    return false;
}

class Solution {
    public:
        static void solveSudoku(std::vector<std::vector<char>>& board) {
            masks_t masks;
            init(board, &masks);
            easy(board, &masks);
            if (!solve(board, &masks)) {
                printf("Failed :(\n");
            }
        }
};

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

    if (!j.is_array() || !j.size()) {
        panic("error: invalid input");
    }

    std::vector<std::vector<char>> input;
    for (auto& row : j) {
        if (!row.is_array() || row.size() != 9) {
            panic("error: invalid input");
        }
        std::vector<char> r;
        r.reserve(row.size());
        for (auto& c : row) {
            if (!c.is_string()) {
                panic("error: invalid input, expected string");
            }
            // TODO: how to check string's length
            auto s = c.get<std::string>();
            if (s.size() != 1) {
                panic("error: invalid input, expected string with length 1");
            }
            r.push_back(s[0]);
        }
        input.emplace_back(std::move(r));
    }

    printf("INPUT:\n");
    print_board(input);
    Solution s;
    s.solveSudoku(input);
    printf("SOLUTION:\n");
    print_board(input);

    return 0;
}
