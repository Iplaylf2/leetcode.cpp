#include <vector>
#include <functional>

using std::function;
using std::vector;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int max_area;

        auto left = 0;
        auto right = ((int)height.size()) - 1;

        auto max_left_height = height[left];
        auto max_right_height = height[right];

        function<void()> moveToRight;
        function<void()> moveToLeft;

        moveToRight = [&]()
        {
            for (left++; left != right; left++)
            {
                auto left_height = height[left];
                if (max_left_height < left_height)
                {
                    max_left_height = left_height;
                    auto wide = right - left;
                    if (max_right_height < left_height)
                    {
                        auto area = wide * max_right_height;
                        if (max_area < area)
                        {
                            max_area = area;
                        }
                        return moveToLeft();
                    }
                    else
                    {
                        auto area = wide * left_height;
                        if (max_area < area)
                        {
                            max_area = area;
                        }
                    }
                }
            }
        };

        moveToLeft = [&]()
        {
            for (right--; left != right; right--)
            {
                auto right_height = height[right];
                if (max_right_height < right_height)
                {
                    max_right_height = right_height;
                    auto wide = right - left;
                    if (max_left_height < right_height)
                    {
                        auto area = wide * max_left_height;
                        if (max_area < area)
                        {
                            max_area = area;
                        }
                        return moveToRight();
                    }
                    else
                    {
                        auto area = wide * right_height;
                        if (max_area < area)
                        {
                            max_area = area;
                        }
                    }
                }
            }
        };

        auto wide = right - left;
        if (max_left_height < max_right_height)
        {
            max_area = wide * max_left_height;
            moveToRight();
        }
        else
        {
            max_area = wide * max_right_height;
            moveToLeft();
        }

        return max_area;
    }
};