#include <iostream>
#include "15-3sum/normal.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<int>({1, 1, 1});
    cout << Solution().threeSum(foo);
}
