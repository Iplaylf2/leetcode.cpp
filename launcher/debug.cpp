#include <iostream>
#include "16-3sum-closest/normal.cpp"
#include "cout-support.cpp"

using std::cout;

int main(int, char **)
{
    auto foo = vector<int>({3, 4, 5, 5, 7});
    cout << Solution().threeSumClosest(foo, 13);
}
