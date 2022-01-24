#include <iostream>
#include "cout-support.cpp"
#include "4-median-of-two-sorted-arrays/normal.cpp"
#include <vector>

using std::cout;

int main(int, char **)
{
    auto a = vector{1, 2, 5};
    auto b = vector{3, 4, 6, 7};

    cout << Solution().findMedianSortedArrays(a, b);
}
