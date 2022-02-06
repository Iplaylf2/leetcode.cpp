#include <vector>
#include <algorithm>
#include <cmath>

using std::floor;
using std::min;
using std::sort;
using std::vector;

class Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        auto size = (int)nums.size();

        sort(nums.begin(), nums.end());

        auto minimun = nums.front();
        auto maximum = nums.back();

        auto result = minimun + nums[1] + nums[2];
        auto min_first = target / 3;
        if (min_first <= minimun)
        {
            return result;
        }

        auto min_diff = abs(target - result);
        // - min_diff < target - (first + second + third) < min_diff
        // first <= maximum
        // target - min_diff - 2 * maximum < first
        // first < (target + min_diff) /3

        auto min_result = target - min_diff;
        auto max_result = target + min_diff;
        auto first_end = size - 2;
        auto second_end = size - 1;
        auto third_end = size;

        auto last_first = INT_MIN;
        auto first_index = findGreater(nums, -1, first_end, min_result - 2 * maximum);
        auto first_limit = findLess(nums, first_index - 1, first_end, min_first + 1);
        for (; first_index <= first_limit; first_index++)
        {
            auto first = nums[first_index];
            if (last_first == first)
            {
                continue;
            }
            else
            {
                last_first = first;
            }

            auto rest = target - first;

            auto second_index = findGreater(nums, first_index, second_end, min_result - first - maximum);
            auto second_limit = findLess(nums, first_index, second_end, (max_result - first + 1) / 2);
            auto last_second = INT_MIN;
            for (; second_index <= second_limit; second_index++)
            {
                auto second = nums[second_index];
                if (last_second == second)
                {
                    continue;
                }
                else
                {
                    last_second = second;
                }

                auto expect = rest - second;

                auto third_index = findGreater(nums, second_index, third_end, expect - 1);
                auto third_index_2 = third_index - 1;

                auto check = [&](int third)
                {
                    auto diff = abs(expect - third);
                    if (diff < min_diff)
                    {
                        result = first + second + third;
                        min_diff = diff;

                        min_result = target - min_diff;
                        max_result = target + min_diff;
                        second_limit = findLess(nums, second_index, second_limit + 1, (max_result - first + 1) / 2);
                    }
                };

                if (second_index < third_index_2)
                {
                    check(nums[third_index_2]);
                }

                if (third_end != third_index)
                {
                    check(nums[third_index]);
                }
            }
        }

        return result;
    }

private:
    static int findLess(vector<int> &nums, const int low, const int high, int x)
    {
        auto _low = low;
        auto _high = high;
        for (auto current = (int)floor((_low + _high) / 2.0);
             _low < current;
             current = (int)floor((_low + _high) / 2.0))
        {
            if (nums[current] < x)
            {
                auto next = current + 1;
                if (_high == next)
                {
                    return current;
                }

                if (nums[next] < x)
                {
                    _low = current;
                }
                else
                {
                    return current;
                }
            }
            else
            {
                _high = current;
            }
        }

        return low;
    }

    static int findGreater(vector<int> &nums, const int low, const int high, int x)
    {
        auto _low = low;
        auto _high = high;
        for (auto current = (_low + _high) / 2; _low < current; current = (_low + _high) / 2)
        {
            if (x < nums[current])
            {
                auto previous = current - 1;
                if (_low == previous)
                {
                    return current;
                }

                if (x < nums[previous])
                {
                    _high = current;
                }
                else
                {
                    return current;
                }
            }
            else
            {
                _low = current;
            }
        }

        return high;
    }
};