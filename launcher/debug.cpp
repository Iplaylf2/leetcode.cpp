#include <iostream>
#include "25-reverse-nodes-in-k-group/normal.cpp"
#include "leetcode-support.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector{1, 2, 3, 4, 5};
    auto foo_ = new ListNode[foo.size()];
    cout << ListNode2vector(Solution().reverseKGroup(vector2ListNode(foo, foo_), 2));
}
