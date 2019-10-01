#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <cassert>
#include <climits>

#include <signal.h>
#include <setjmp.h>

jmp_buf env;

void fpehandler(int sig, siginfo_t* info, void* uc)
{
    fprintf (stderr,
            "Caught signal no. %d; code: %d (FPE_INTDIV would be %d)\n",
            sig, info->si_code, FPE_INTDIV);
    longjmp(env, 1);
}

class Solution {
public:
    static int divide(int dividend, int divisor) noexcept
    {
        int sign = 1;
        if (dividend < 0) {
            sign     *= -1;
            dividend *= -1;
        }
        if (divisor < 0) {
            sign    *= -1;
            divisor *= -1;
        }

        // invariant: dividend = divisor * quotient + remainder
        int quotient  = 0;
        int remainder = dividend;
        while (remainder >= divisor) {
            assert((divisor*quotient + remainder) == dividend);
            remainder -= divisor;
            ++quotient;
            assert((divisor*quotient + remainder) == dividend);
        }

        return sign*quotient;
    }
};

int main(int argc, char** argv)
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags     = SA_SIGINFO;
    sa.sa_sigaction = &fpehandler;
    // sa.sa_handler   = SIG_IGN;
    sigaction(SIGFPE, &sa, NULL);

    std::vector<std::pair<int, int>> vs = {
        { 1, 1 },
        { 3, 1 },
        { 9, 3 },
        { 9, -3 },
        { 12, 5 },
        { -12, -5 },
        { INT_MIN, -1 },
    };

    // std::cout << (INT_MIN / -1) << std::endl;
    // std::cout << (INT_MIN / -2) << std::endl;

    for (auto v : vs) {
        int expect = 0;
        if (setjmp(env) == 0) {
            expect = v.first / v.second;
        } else {
            expect = INT_MAX;
        }
        int actual = Solution::divide(v.first, v.second);
        std::cout << "Test Case: " << v.first << " / " << v.second << "\n======================\n";
        std::cout << "Expect: " << expect << "\n";
        std::cout << "Actual: " << actual << "\n";
        if (expect != actual) {
            std::cout << "Failed!\n\n";
        } else {
            std::cout << "Passed.\n\n";
        }
    }


#if 0
    if (argc != 2) {
        std::cerr << "usage: " << argv[0] << " [FILE]" << std::endl;
        return 1;
    }

    std::ifstream ifs{argv[1]};
    if (!ifs) {
        std::cerr << "error: unable to open file: " << argv[1] << std::endl;
        return 1;
    }

    int dividend, divisor;
    ifs >> dividend >> divisor;

    std::cout << "Expect: " << (dividend / divisor) << std::endl;;
    std::cout << "Actual: " << Solution{}.divide(dividend, divisor) << std::endl;;
#endif
    return 0;
}
