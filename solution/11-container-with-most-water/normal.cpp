#include <vector>

using std::vector;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        auto max_area = 0;

        auto left = 0;
        auto right = ((int)height.size()) - 1;
        do
        {
            auto wide = right - left;

            auto left_height = height[left];
            auto right_height = height[right];
            if (left_height < right_height)
            {
                auto area = wide * left_height;
                if (max_area < area)
                {
                    max_area = area;
                }

                left++;
            }
            else
            {
                auto area = wide * right_height;
                if (max_area < area)
                {
                    max_area = area;
                }

                right--;
            }
        } while (left != right);

        return max_area;
    }
};