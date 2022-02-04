#include <vector>
#include <algorithm>
#include <cmath>

using std::min;
using std::sort;
using std::vector;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        auto size = (int)nums.size();
        if (nums.size() < 3)
        {
            return {};
        }

        sort(nums.begin(), nums.end());

        auto maximum = nums.back();
        if (maximum <= 0)
        {
            if (nums[size - 3] == 0)
            {
                return {{0, 0, 0}};
            }
            else
            {
                return {};
            }
        }

        auto result = vector<vector<int>>();
        auto first_index = 0;
        auto max_first = min(0, nums[size - 3]);
        auto first = nums[first_index];

        auto last_first = INT_MIN;
        auto max_second = nums[size - 2];
        auto third_end = size - 1;

        auto check_first = [&]()
        {
            if (last_first == first)
            {
                return;
            }
            else
            {
                last_first = first;
            }

            auto second_index = first_index + 1;
            auto second_high = min(max_second, (0 - first) / 2);
            auto second_low = 0 - first - maximum;
            auto second = nums[second_index];
            for (auto limit = min(second_low, second_high); second < limit; second_index++, second = nums[second_index])
                ;

            auto last_second = INT_MIN;

            auto check_second = [&]()
            {
                if (last_second == second)
                {
                    return;
                }
                else
                {
                    last_second = second;
                }

                auto target = 0 - first - second;

                auto low = second_index;
                auto high = third_end;
                auto third_index = high;
                do
                {
                    auto third = nums[third_index];
                    if (target < third)
                    {
                        high = third_index;
                    }
                    else if (target == third)
                    {
                        result.push_back({first, second, third});
                        break;
                    }
                    else
                    {
                        low = third_index;
                    }

                    third_index = (low + high) / 2;
                } while (low < third_index);
            };

            for (; second < second_high; second_index++, second = nums[second_index])
            {
                check_second();
            }

            if (second == second_high)
            {
                check_second();
            }
        };

        for (; first < max_first; first_index++, first = nums[first_index])
        {
            check_first();
        }

        if (first == max_first)
        {
            check_first();
        }

        return result;
    }
};