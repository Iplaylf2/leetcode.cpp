#include <vector>
#include <algorithm>

using std::reverse;
using std::swap;
using std::vector;

class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        auto down_begin = 0;
        auto last = nums[0];
        for (int i = 1, end = (int)nums.size(); end != i; i++)
        {
            auto current = nums[i];
            if (last < current)
            {
                down_begin = i;
            }
            last = current;
        }

        reverse(nums.begin() + down_begin, nums.end());

        auto head = down_begin - 1;
        if (head < 0)
        {
            return;
        }

        auto head_value = nums[head];
        while (nums[down_begin] <= head_value)
        {
            down_begin++;
        }

        swap(nums[head], nums[down_begin]);
    }
};