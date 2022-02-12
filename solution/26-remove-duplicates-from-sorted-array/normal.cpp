#include <vector>
#include <cmath>

using std::vector;

class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        auto distinct = 0;

        auto last = INT_MIN;
        for (auto x : nums)
        {
            if (last != x)
            {
                nums[distinct] = x;
                distinct++;
                last = x;
            }
        }

        return distinct;
    }
};