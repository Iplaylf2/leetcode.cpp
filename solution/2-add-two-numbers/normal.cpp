#include "leetcode.cpp"

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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        auto carry = 0;

        auto prefix = ListNode();
        auto final = &prefix;

        while (true)
        {
            auto x = l1->val + l2->val + carry;
            if (x < 10)
            {
                carry = 0;
            }
            else
            {
                carry = 1;
                x = x - 10;
            }

            auto fresh = new ListNode(x);
            final->next = fresh;
            final = fresh;

            l1 = l1->next;
            l2 = l2->next;
            if (l1 == nullptr)
            {
                l1 = l2;
                break;
            }
            if (l2 == nullptr)
            {
                break;
            }
        }

        while (l1 != nullptr)
        {
            auto x = l1->val + carry;
            if (x < 10)
            {
                carry = 0;
            }
            else
            {
                carry = 1;
                x = x - 10;
            }

            l1->val = x;
            final->next = l1;
            final = l1;

            l1 = l1->next;
        }

        if (carry == 1)
        {
            final->next = new ListNode(1);
        }

        return prefix.next;
    }
};