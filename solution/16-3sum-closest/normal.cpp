#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using std::map;
using std::vector;

class Solution
{
public:
    int threeSumClosest(vector<int> &nums, int target)
    {
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
        auto maximum = distinct[distinct_limit];

        int result;
        auto min_diff = 10000;

        // - min_diff < target - (first + second + third) < min_diff
        // first <= maximum
        // target - min_diff - 2 * maximum < first
        // first < (target + min_diff) /3

        auto min_result = target - min_diff;
        auto max_result = target + min_diff;

        auto first_left = min_result - 2 * maximum;
        auto first_right = ceil((target + min_diff) / 3.0f);
        auto first_index = findFirstGreaterFromHigh(distinct, -1, distinct_limit, first_left);
        auto first_limit = findLastLessFromLow(distinct, first_index, distinct_size, first_right);
        for (; first_index <= first_limit; first_index++)
        {
            auto first = distinct[first_index];
            auto rest = target - first;

            auto &first_count = counter[first];
            auto next_second_index = 1 < first_count ? first_index : first_index + 1;
            first_count--;

            auto second_left = min_result - first - maximum;
            auto second_right = ceil((max_result - first) / 2.0f);
            auto second_index = findFirstGreaterFromHigh(distinct, next_second_index - 1, distinct_limit, second_left);
            auto second_limit = findLastLessFromLow(distinct, second_index, distinct_size, second_right);
            for (; second_index <= second_limit; second_index++)
            {
                auto second = distinct[second_index];
                auto expect = rest - second;

                auto second_count = counter[second];
                auto next_third_index = 1 < second_count ? second_index : second_index + 1;

                auto third_index = findFirstGreaterFromHigh(distinct, next_third_index - 1, distinct_limit, expect - 1);
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

                        auto second_right = ceil((max_result - first) / 2.0f);
                        second_limit = findLastLessFromLow(distinct, second_index + 1, second_limit + 1, second_right);
                    }
                };

                if (next_third_index <= third_index_2)
                {
                    check(distinct[third_index_2]);
                }

                if (third_index <= distinct_limit)
                {
                    check(distinct[third_index]);
                }
            }
        }

        return result;
    }

private:
    static int findLastLessFromLow(int *arr, const int low, const int high, int x)
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

    static int findFirstGreaterFromHigh(int *arr, const int low, const int high, int x)
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