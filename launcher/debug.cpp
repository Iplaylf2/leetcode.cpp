#include <iostream>
#include "15-3sum/special.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<int>({-2, -3, 0, 0, -2});
    cout << Solution().threeSum(foo);
}
