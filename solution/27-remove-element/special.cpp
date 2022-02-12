#include <vector>

using std::vector;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        auto front = 0;
        auto end = (int)nums.size() - 1;
        while (front <= end)
        {
            if (val == nums[front])
            {
                nums[front] = nums[end];
                end--;
            }
            else
            {
                front++;
            }
        }

        return front;
    }
};