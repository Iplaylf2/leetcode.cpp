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
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        if (1 == k)
        {
            return head;
        }

        auto fast = head;
        for (auto i = 1; k != i; i++)
        {
            fast = fast->next;
        }

        auto dummy = ListNode(0, head);
        auto slow = &dummy;

        while (true)
        {
            auto current = slow->next;
            slow->next = fast;
            slow = current;

            auto last = fast->next;
            for (auto i = 0; k != i; i++)
            {
                auto next = current->next;
                current->next = last;
                last = current;
                current = next;
            }

            if (nullptr == current)
            {
                break;
            }

            auto i = 1;
            do
            {
                current = current->next;
                if (nullptr == current)
                {
                    goto end;
                }

                i++;
            } while (k != i);

            fast = current;
        }

    end:
        return dummy.next;
    }
};