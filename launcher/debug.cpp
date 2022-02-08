#include <iostream>
#include "15-3sum/special.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<int>({-1, 0, 1, 2, -1, -4});
    cout << Solution().threeSum(foo);
}
