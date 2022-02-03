#include <vector>
#include <algorithm>
#include <cmath>

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

        auto max = nums.back();
        if (max <= 0)
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
        auto last_first = INT_MIN;
        auto first_end = size - 2;
        auto second_end = size - 1;
        do
        {
            auto first = nums[first_index];
            if (0 < first)
            {
                break;
            }
            if (last_first == first)
            {
                first_index++;
                continue;
            }
            else
            {
                last_first = first;
            }

            auto second_index = first_index + 1;
            auto last_second = INT_MIN;
            do
            {
                auto second = nums[second_index];
                if (last_second == second)
                {
                    second_index++;
                    continue;
                }
                else
                {
                    last_second = second;
                }

                auto target = 0 - first - second;
                if (target < second)
                {
                    break;
                }

                if (max < target)
                {
                    second_index++;
                    continue;
                }

                auto low = second_index;
                auto high = second_end;
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

                second_index++;
            } while (second_end != second_index);

            first_index++;
        } while (first_end != first_index);

        return result;
    }
};