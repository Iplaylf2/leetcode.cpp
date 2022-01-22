#include <iostream>
#include "cout-support.cpp"
#include <vector>
#include "1-two-sum/normal.cpp"

int main(int, char **)
{
    vector<int> input{2, 7, 11, 15};
    cout << Solution().twoSum(input, 9);
}
