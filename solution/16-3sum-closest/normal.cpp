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

        auto maximum = nums.back();

        auto result = nums[0] + nums[1] + nums[2];

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
        auto first_left = min_result - 2 * maximum;
        auto first_index = findFirstGreaterFromHigh(nums, -1, first_end - 1, first_left);

        auto first_right = target / 3 + 1;
        auto first_limit = findLastLessFromLow(nums, 0, first_end, first_right);
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

            auto second_left = min_result - first - maximum;
            auto second_index = findFirstGreaterFromHigh(nums, first_index, second_end - 1, second_left);

            auto second_right = (max_result - first + 1) / 2;
            auto second_limit = findLastLessFromLow(nums, first_index + 1, second_end, second_right);
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

                auto third_index = findFirstGreaterFromHigh(nums, second_index, third_end - 1, expect - 1);
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
                        
                        auto second_right = (max_result - first + 1) / 2;
                        second_limit = findLastLessFromLow(nums, second_index, second_limit + 1, second_right);
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
    static int findLastLessFromLow(vector<int> &nums, const int low, const int high, int x)
    {
        auto current = low;
        auto _low = low;
        auto _high = high;
        do
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

            current = (_low + _high) / 2;
        } while (_low != current);

        return low - 1;
    }

    static int findFirstGreaterFromHigh(vector<int> &nums, const int low, const int high, int x)
    {
        auto current = high;
        auto _low = low;
        auto _high = high;
        do
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

            current = (_low + _high) / 2;
        } while (_low != current);

        return high + 1;
    }
};