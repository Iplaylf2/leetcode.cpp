#include <vector>

using std::vector;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        auto distinct = 0;

        for (auto x : nums)
        {
            if (val != x)
            {
                nums[distinct] = x;
                distinct++;
            }
        }

        return distinct;
    }
};