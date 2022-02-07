#include <iostream>
#include "18-4sum/normal.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<int>({-1, 0, -5, -2, -2, -4, 0, 1, -2});
    cout << Solution().fourSum(foo, -9);
}
