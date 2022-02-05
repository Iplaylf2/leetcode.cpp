#include <vector>
#include <array>
#include <algorithm>
#include <cmath>

using std::fill_n;
using std::min;
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

        auto &count = counter[0];
        switch (count)
        {
        case 0:
            break;
        case 3:
            count = 2;
            break;
        default:
            count = 1;
            break;
        }

        sort(distinct, distinct + distinct_size);

        auto min_first = -2 * maximum; // 0 - first <= 2 * maximum
        auto first_index = findGreater(distinct, -1, distinct_size, min_first - 1);

        auto max_first = 0;
        auto first_limit = findLess(distinct, -1, distinct_size, max_first + 1);
        for (; first_index <= first_limit; first_index++)
        {
            auto first = distinct[first_index];
            auto rest = 0 - first;

            auto count = counter[first];
            auto second_index_previous = 1 != count ? (first_index - 1) : first_index;
            auto min_second = rest - maximum; //  0 - first - second <= maximum
            auto second_index = findGreater(distinct, second_index_previous, distinct_size, min_second - 1);

            auto max_second = rest / 2; //  second <= 0 - first - second
            auto second_limit = findLess(distinct, second_index_previous, distinct_size, max_second + 1);
            for (; second_index <= second_limit; second_index++)
            {
                auto second = distinct[second_index];
                auto third = rest - second;
                auto count = counter[third];
                if (third == second)
                {
                    if (1 != count)
                    {
                        result.push_back({first, second, third});
                    }
                }
                else
                {
                    if (0 != count)
                    {
                        result.push_back({first, second, third});
                    }
                }
            }
        }

        counter += minimum;
        delete[] counter;
        delete[] distinct;

        return result;
    }

private:
    static int findLess(int *arr, const int low, const int high, int x)
    {
        auto _low = low;
        auto _high = high;
        for (auto current = (_low + _high) / 2; _low < current; current = (_low + _high) / 2)
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
        }

        return low;
    }

    static int findGreater(int *arr, const int low, const int high, int x)
    {
        auto _low = low;
        auto _high = high;
        for (auto current = (_low + _high) / 2; _low < current; current = (_low + _high) / 2)
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
        }

        return high;
    }
};