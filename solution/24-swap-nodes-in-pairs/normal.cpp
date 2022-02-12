#include <algorithm>

#include "leetcode.cpp"

using std::swap;

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
    ListNode *swapPairs(ListNode *head)
    {
        ListNode *current;
        ListNode *last;
        bool to_swap;
        for (current = head, to_swap = false;
             nullptr != current;
             current = current->next, to_swap = !to_swap)
        {
            if (to_swap)
            {
                swap(last->val, current->val);
            }
            else
            {
                last = current;
            }
        }

        return head;
    }
};