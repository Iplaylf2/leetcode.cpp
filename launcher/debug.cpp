#include <iostream>
#include "16-3sum-closest/normal.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<int>({1,1,-1});
    cout << Solution().threeSumClosest(foo, 0);
}
