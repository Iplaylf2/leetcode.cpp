#include <iostream>
#include "23-merge-k-sorted-lists/normal.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<ListNode *>{nullptr, nullptr, nullptr};
    Solution().mergeKLists(foo);
}
