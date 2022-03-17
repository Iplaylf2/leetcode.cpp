#include <vector>
#include <algorithm>
#include <climits>

#include "leetcode.cpp"

using std::function;
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
        auto last = ((int)lists.size()) - 1;
        for (auto i = last; 0 <= i; i--)
        {
            auto current = lists[i];
            if (nullptr == current)
            {
                lists[i] = lists[last];
                last--;
            }
        }

        auto size = last + 1;
        switch (size)
        {
        case 0:
            return nullptr;
        case 1:
            return lists[0];
        default:
            break;
        }

        auto heap_size = 2 * size - 1;
        auto heap = new LTNode[heap_size];

        heap[0].winner = nullptr;
        heap[0].candidate = nullptr;
        auto port_offset = size - 1;
        for (auto i = 0, end = port_offset; end != i; i++)
        {
            auto &current = heap[i];

            auto &left = heap[2 * i + 1];
            auto &right = heap[2 * i + 2];

            left.winner = &current;
            left.candidate = &right;
            left.value = INT_MIN;

            right.winner = &current;
            right.candidate = &left;
            right.value = INT_MIN;
        }

        auto port = heap + port_offset;

        auto min_index = 0;
        auto rank = [&](int index, int value)
        {
            auto winner = port[index].winner;
            do
            {
                if (winner->value < value)
                {
                    swap(winner->index, index);
                    swap(winner->value, value);
                }

                winner = winner->winner;
            } while (nullptr != winner);

            min_index = index;
        };

        for (auto i = 0, end = (int)size; end != i; i++)
        {
            auto current_list = lists[i];
            rank(i, current_list->val);
        }

        auto min_list = lists[min_index];
        auto head = min_list;
        auto current = head;

        while (true)
        {
            auto current_index = min_index;
            int current_value;

            auto next_list = min_list->next;
            if (nullptr == next_list)
            {
                auto &absent = port[current_index];
                auto winner = absent.winner;
                auto candidate = absent.candidate;

                auto next_index = winner->index;

                auto next_winner = winner->winner;
                if (nullptr == next_winner)
                {
                    if (INT_MIN == candidate->value)
                    {
                        current->next = lists[next_index];
                        break;
                    }
                    else
                    {
                        candidate->winner = nullptr;
                        candidate->candidate = nullptr;

                        min_index = next_index;
                        goto after_rank;
                    }
                }

                candidate->winner = next_winner; // jump winner
                candidate->candidate = winner->candidate;
                candidate->candidate->candidate = candidate;

                current_index = next_index;
                current_value = winner->value;
            }
            else
            {
                current_value = next_list->val;
                lists[current_index] = next_list;
            }

            rank(current_index, current_value);

        after_rank:
            min_list = lists[min_index];
            current->next = min_list;
            current = min_list;
        }

        delete[] heap;

        return head;
    }

private:
    class LTNode
    {
    public:
        LTNode *winner;
        LTNode *candidate;
        int index;
        int value;
    };
};