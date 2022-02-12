#include <vector>
#include "leetcode.cpp"

using std::vector;

ListNode *vector2ListNode(const vector<int> &source, ListNode *allocator)
{
    ListNode *last = nullptr;
    for (auto begin = source.rbegin(), end = source.rend(); end != begin; begin++)
    {
        allocator->next = last;
        allocator->val = *begin;
        last = allocator;

        allocator++;
    }

    return last;
}

vector<int> ListNode2vector(ListNode *x)
{
    auto result = vector<int>();
    while (nullptr != x)
    {
        result.push_back(x->val);
        x = x->next;
    }

    return result;
}