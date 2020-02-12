#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <list>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void printList(ListNode* head)
{
    printf("BEG LIST:\n");
    while (head) {
        printf("\t%d (%p) -> (%p)\n", head->val, head, head->next);
        head = head->next;
    }
    printf("END LIST\n\n");
}

struct Solution
{
    static int length(ListNode* head) noexcept
    {
        int i = 0;
        while (head) {
            head = head->next;
            ++i;
        }
        return i;
    }


    static ListNode* rotateOne(ListNode* head) noexcept
    {
        ListNode **p = &head;
        while (*p) {
            if (!(*p)->next) {
                // NOTE: last node != head because length > 1
                // if (*p != head) {
                    (*p)->next = head;
                    head = *p;
                    *p = NULL;
                // }
                break;
            }
            p = &(*p)->next;
        }
        return head;
    }

    static ListNode* rotateRight(ListNode* head, int k) noexcept
    {
        int n = length(head);
        if (n == 0 || n == 1)
            return head;
        k = k % n;
        while (k-- > 0) {
            head = rotateOne(head);
        }
        return head;
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

    std::vector<int> vs;
    for (const auto& v : j) {
        vs.push_back(v.get<int>());
    }

    ListNode* head = NULL;
    for (auto rit = vs.rbegin(); rit != vs.rend(); ++rit) {
        ListNode* cur = new ListNode(*rit);
        cur->next = head;
        head = cur;
    }

    ifs >> j;
    int k = j.get<int>();
    auto sol = Solution{}.rotateRight(head, k);
    const auto* p = sol;
    printf("[");
    while (p) {
        printf("%d->", p->val);
        p = p->next;
    }
    printf("NULL");
    printf("]\n");

    return 0;
}
