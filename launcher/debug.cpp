#include <iostream>
#include "cout-support.cpp"
#include "4-median-of-two-sorted-arrays/better.cpp"
#include <vector>

using std::cout;

int main(int, char **)
{
    auto a = vector{100001};
    auto b = vector{100000};

    cout << Solution().findMedianSortedArrays(a, b);
}
