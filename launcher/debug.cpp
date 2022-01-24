#include <iostream>
#include "cout-support.cpp"
#include "4-median-of-two-sorted-arrays/normal.cpp"
#include <vector>

using std::cout;

int main(int, char **)
{
    auto a = vector{1, 2};
    auto b = vector{-1, 3};

    cout << Solution().findMedianSortedArrays(a, b);
}
