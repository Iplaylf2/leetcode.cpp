#include <iostream>
#include "cout-support.cpp"
#include "4-median-of-two-sorted-arrays/normal.cpp"
#include <vector>

using std::cout;

int main(int, char **)
{
    auto a = vector{1, 4};
    auto b = vector{2, 3, 5, 6};

    cout << Solution().findMedianSortedArrays(a, b);
}
