#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

using std::fill_n;
using std::sort;
using std::swap;
using std::vector;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        auto result = vector<vector<int>>();
        auto size = nums.size();
        if (size < 3)
        {
            return result;
        }

        auto minimum = nums[0];
        auto maximum = nums[1];
        if (maximum < minimum)
        {
            swap(minimum, maximum);
        }

        for (auto i = 2; i != size; i++)
        {
            auto x = nums[i];
            if (x < minimum)
            {
                minimum = x;
            }
            else if (maximum < x)
            {
                maximum = x;
            }
        }

        if (0 < minimum || maximum < 0)
        {
            return result;
        }

        auto counter_size = maximum - minimum + 1;
        auto counter = new int[counter_size];
        fill_n(counter, counter_size, 0);
        counter -= minimum;

        auto distinct = new int[counter_size];

        auto distinct_size = 0;
        for (auto x : nums)
        {
            auto &count = counter[x];
            switch (count)
            {
            case 0:
                distinct[distinct_size] = x;
                distinct_size++;
            case 1:
            case 2:
                count++;
                break;
            default:
                break;
            }
        }

        sort(distinct, distinct + distinct_size);

        auto distinct_limit = distinct_size - 1;

        auto first_left = -2 * maximum - 1;
        auto first_right = 1;
        auto first_index = FindFirstGreaterFromHigh(distinct, -1, distinct_limit, first_left);
        auto first_limit = FindLastLessFromLow(distinct, first_index, distinct_size, first_right);
        for (; first_index <= first_limit; first_index++)
        {
            auto first = distinct[first_index];
            auto rest = 0 - first;

            auto &first_count = counter[first];
            auto next_second_index = 1 < first_count ? first_index : first_index + 1;
            first_count--;

            auto second_left = rest - maximum - 1;
            auto second_right = ceil(((float)(rest + 1)) / 2);
            auto second_index = FindFirstGreaterFromHigh(distinct, next_second_index - 1, distinct_limit, second_left);
            auto second_limit = FindLastLessFromLow(distinct, second_index, distinct_size, second_right);
            for (; second_index <= second_limit; second_index++)
            {
                auto second = distinct[second_index];
                auto &second_count = counter[second];
                second_count--;

                auto third = rest - second;
                auto third_count = counter[third];
                if (0 == third_count)
                {
                    second_count++;
                    continue;
                }

                result.push_back({first, second, third});

                second_count++;
            }
        }

        counter += minimum;
        delete[] counter;
        delete[] distinct;

        return result;
    }

private:
    static int FindLastLessFromLow(int *arr, const int low, const int high, int x)
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

    static int FindFirstGreaterFromHigh(int *arr, const int low, const int high, int x)
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