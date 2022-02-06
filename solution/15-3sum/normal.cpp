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
        auto result = vector<vector<int>>();

        auto size = (int)nums.size();
        if (size < 3)
        {
            return result;
        }

        sort(nums.begin(), nums.end());

        auto minimum = nums.front();
        auto maximum = nums.back();
        if (0 < minimum)
        {
            return result;
        }

        auto first_end = size - 2;
        auto second_end = size - 1;

        auto min_first = -2 * maximum; // 0 - first <= 2 * maximum
        auto first_index = findFirstGreaterFromHigh(nums, -1, first_end - 1, min_first - 1);

        auto max_first = 0;
        auto first_limit = findLastLessFromLow(nums, 0, first_end, max_first + 1);

        auto last_first = INT_MIN;
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

            auto rest = 0 - first;

            auto min_second = rest - maximum; //  0 - first - second <= maximum
            auto second_index = findFirstGreaterFromHigh(nums, first_index, second_end - 1, min_second - 1);

            auto max_second = rest / 2; //  second <= 0 - first - second
            auto second_limit = findLastLessFromLow(nums, first_index + 1, second_end, max_second + 1);

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

                auto target = rest - second;

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