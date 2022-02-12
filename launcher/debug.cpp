#include <iostream>
#include "23-merge-k-sorted-lists/tournament .cpp"
#include "leetcode-support.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto a = vector{-1, 1};
    auto b = vector{-3, 1, 4};
    auto c = vector{-2, -1, 0, 2};
    auto a_ = new ListNode[a.size()];
    auto b_ = new ListNode[b.size()];
    auto c_ = new ListNode[c.size()];

    auto foo = vector<ListNode *>{vector2ListNode(a, a_), vector2ListNode(b, b_), vector2ListNode(c, c_)};
    cout << ListNode2vector(Solution().mergeKLists(foo));
}
