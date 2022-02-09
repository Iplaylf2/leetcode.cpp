#include <vector>
#include <algorithm>

#include "leetcode.cpp"

using std::swap;
using std::vector;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
        auto size = lists.size();
        if (0 == size)
        {
            return nullptr;
        }

        int last = size - 1;
        for (auto i = last; 0 <= i; i--)
        {
            auto current = lists[i];
            if (nullptr == current)
            {
                swap(lists[i], lists[last]);
                last--;
            }
        }

        auto dummy = ListNode();
        auto current = &dummy;

        while (0 < last)
        {
            int minimum = lists[0]->val;
            int index = 0;

            for (auto i = 1; i <= last; i++)
            {
                auto x = lists[i];
                auto value = x->val;
                if (value < minimum)
                {
                    index = i;
                    minimum = value;
                }
            }

            auto &to_move = lists[index];
            current->next = to_move;
            current = to_move;

            to_move = to_move->next;
            if (nullptr == to_move)
            {
                swap(to_move, lists[last]);
                last--;
            }
        }
        current->next = lists[0];

        return dummy.next;
    }
};