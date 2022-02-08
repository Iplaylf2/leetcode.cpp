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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        auto fast = head;
        for (; 0 != n; n--)
        {
            fast = fast->next;
        }

        if (nullptr == fast)
        {
            return head->next;
        }

        ListNode *last_slow;
        auto slow = head;
        do
        {
            last_slow = slow;
            slow = slow->next;
            fast = fast->next;
        } while (nullptr != fast);

        last_slow->next = slow->next;

        return head;
    }
};