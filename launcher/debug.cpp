#include <iostream>
#include "18-4sum/any-sum.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<int>({1, 0, -1, 0, -2, 2});
    cout << Solution().fourSum(foo, 0);
}
