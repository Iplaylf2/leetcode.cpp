#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using std::ceil;
using std::map;
using std::pair;
using std::transform;
using std::vector;

class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        auto result = vector<vector<int>>();
        if (nums.size() < 4)
        {
            return result;
        }

        auto counter = map<int, int>();
        for (auto x : nums)
        {
            auto count = counter.find(x);
            if (counter.end() == count)
            {
                counter.emplace(x, 1);
            }
            else
            {
                count->second++;
            }
        }

        auto counter_size = counter.size();
        auto counter_end = counter.end();

        auto distinct = new int[counter_size];
        transform(counter.begin(), counter.end(), distinct, [](auto &x)
                  { return x.first; });

        auto &distinct_size = counter_size;
        auto distinct_limit = distinct_size - 1;
        long minimum = distinct[0];
        long maximum = distinct[distinct_limit];

        auto first_left = target - 3 * maximum - 1;
        auto first_right = ceil((target + 1) / 4.0f);
        auto first_index = findFirstGreaterFromHigh(distinct, -1, distinct_limit, first_left);
        auto first_limit = findLastLessFromLow(distinct, first_index, distinct_size, first_right);
        for (; first_index <= first_limit; first_index++)
        {
            auto first = distinct[first_index];
            auto &first_count = counter[first];

            auto rest_3 = target - first;

            auto second_begin = 1 < first_count ? first_index : first_index + 1;
            first_count--;

            auto second_left = rest_3 - 2 * maximum - 1;
            auto second_right = ceil((rest_3 + 1) / 3.0f);
            auto second_index = findFirstGreaterFromHigh(distinct, second_begin - 1, distinct_limit, second_left);
            auto second_limit = findLastLessFromLow(distinct, second_index, distinct_size, second_right);
            for (; second_index <= second_limit; second_index++)
            {
                auto second = distinct[second_index];
                auto &second_count = counter[second];

                auto rest_2 = rest_3 - second;

                auto third_begin = 1 < second_count ? second_index : second_index + 1;
                second_count--;

                auto third_left = rest_2 - maximum - 1;
                auto third_right = ceil((rest_2 + 1) / 2.0f);
                auto third_index = findFirstGreaterFromHigh(distinct, third_begin - 1, distinct_limit, third_left);
                auto third_limit = findLastLessFromLow(distinct, third_index, distinct_size, third_right);
                for (; third_index <= third_limit; third_index++)
                {
                    auto third = distinct[third_index];
                    auto &third_count = counter[third];

                    auto fourth = rest_2 - third;
                    auto fourth_count = counter.find(fourth);
                    if (counter_end == fourth_count)
                    {
                        continue;
                    }

                    third_count--;

                    if (0 < fourth_count->second)
                    {
                        result.push_back({first, second, third, fourth});
                    }

                    third_count++;
                }

                second_count++;
            }
        }

        return result;
    }

private:
    static int findLastLessFromLow(int *arr, const int low, const int high, long x)
    {
        auto current = low;
        auto _low = low;
        auto _high = high;
        while (current < _high)
        {
            if (arr[current] < x)
            {
                auto next = current + 1;
                if (_high == next)
                {
                    return current;
                }

                if (arr[next] < x)
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
        }

        return low - 1;
    }

    static int findFirstGreaterFromHigh(int *arr, const int low, const int high, long x)
    {
        auto current = high;
        auto _low = low;
        auto _high = high;
        while (_low < current)
        {
            if (x < arr[current])
            {
                auto previous = current - 1;
                if (_low == previous)
                {
                    return current;
                }

                if (x < arr[previous])
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
        }

        return high + 1;
    }
};