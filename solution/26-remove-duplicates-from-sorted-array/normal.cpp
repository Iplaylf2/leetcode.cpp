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
        for (auto tail = 0, end = (int)nums.size();
             end != tail;
             tail++)
        {
            auto current = nums[tail];
            if (last != current)
            {
                nums[distinct] = current;
                distinct++;
                last = current;
            }
        }
        
        return distinct;
    }
};