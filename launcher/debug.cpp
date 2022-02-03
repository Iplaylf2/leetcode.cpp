#include <iostream>
#include "15-3sum/normal.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<int>({0});
    cout << Solution().threeSum(foo);
}
