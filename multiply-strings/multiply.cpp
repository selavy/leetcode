#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cassert>

class Solution
{
public:
    std::string multiply(std::string num1, std::string num2) {
        // "grade school" method
        // TODO: karatsuba algorihm
        int n1 = num1.size();
        int n2 = num2.size();
        int n3 = n1 + n2;
        std::string rv(n3, '0');

        int a, b, c, d, e, k, r;
        for (int i = 0; i < n2; ++i) {
            assert(n2 - 1 - i >= 0);
            a = num2[n2 - 1 - i] - '0';
            c = 0;
            assert(0 <= a && a <= 9);
            int j;
            for (j = 0; j < n1; ++j) {
                assert(n1 - 1 - j >= 0);
                b = num1[n1 - 1 - j] - '0';
                assert(0 <= b && b <= 9);
                r = a * b + c;
                assert(0 <= r && r <= 99);
                c = r / 10;
                d = r % 10;
                assert(0 <= c && c <= 9);
                assert(0 <= d && d <= 9);

                k = (n3 - 1) - i - j;
                e = (rv[k] - '0') + d;
                d = e % 10;
                e = e / 10;
                assert(0 <= d && d <= 9);
                assert(0 <= e && e <= 9);
                rv[k] = d + '0';
                for (k = k - 1; e > 0; --k) {
                    assert(k >= 0);
                    d = rv[k] - '0' + e;
                    e = d / 10;
                    d = d % 10;
                    rv[k] = d + '0';
                }
            }

            // propogate final carry if needed
            if (c > 0) {
                k = (n3 - 1) - i - j;
                assert(k >= 0);
                e = (rv[k] - '0') + c;
                d = e % 10;
                e = e / 10;
                assert(0 <= d && d <= 9);
                assert(0 <= e && e <= 9);
                rv[k] = d + '0';
                for (k = k - 1; e > 0; --k) {
                    assert(k >= 0);
                    d = rv[k] - '0' + e;
                    e = d / 10;
                    d = d % 10;
                    rv[k] = d + '0';
                }
            }
        }

        // remove leading zeros
        int i;
        for (i = 0; i < n3 - 1; ++i) {
            if (rv[i] != '0') break;
        }
        rv.erase(rv.begin(), rv.begin() + i);

        return rv;
    }
};

int main(int argc, char** argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [FILE]\n", argv[0]);
        return 0;
    }

    const char* filename = argv[1];
    std::ifstream ifs(filename);
    if (!ifs) {
        fprintf(stderr, "Unable to open '%s'\n", filename);
        exit(1);
    }

    std::string num1, num2, expect;
    ifs >> num1;
    ifs >> num2;
    ifs >> expect;

    std::string result = Solution{}.multiply(num1, num2);
    std::cout << result << std::endl;

    if (result != expect) {
        std::cout << "WRONG\nExpected: " << expect << "\nActual  : " << result << "\n";
        exit(1);
    }

    return 0;
}
