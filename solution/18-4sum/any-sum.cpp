#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using std::ceil;
using std::function;
using std::map;
using std::transform;
using std::vector;

class Byproduct
{
public:
    static vector<vector<int>> AnySum(vector<int> &source, int item, int target)
    {
        auto result = vector<vector<int>>();
        if (source.size() < item)
        {
            return result;
        }

        auto counter = map<int, int>();
        for (auto x : source)
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
        long maximum = distinct[distinct_limit];

        auto item_limit = item - 1;

        function<void(int, int, vector<int> &, int, int)> find;
        find = [&](int item, int target, vector<int> &root, int i, int begin)
        {
            if (1 == item)
            {
                auto last_count = counter.find(target);
                if (counter_end != last_count && 0 < last_count->second)
                {
                    root[i] = target;
                    result.push_back(root);
                }

                return;
            }

            auto left = target - (item - 1) * maximum - 1;
            auto right = ceil(((float)(target + 1)) / item);
            auto index = FindFirstGreaterFromHigh(distinct, begin - 1, distinct_limit, left);
            auto limit = FindLastLessFromLow(distinct, index, distinct_size, right);

            for (; index <= limit; index++)
            {
                auto current = distinct[index];
                root[i] = current;

                auto &count = counter[current];
                auto next = 1 < count ? index : index + 1;
                count--;

                find(item - 1, target - current, root, i + 1, next);

                count++;
            }
        };

        auto root = vector<int>(item);
        find(item, target, root, 0, 0);

        return result;
    }

private:
    static int FindLastLessFromLow(int *arr, const int low, const int high, long x)
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

    static int FindFirstGreaterFromHigh(int *arr, const int low, const int high, long x)
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

class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        return Byproduct::AnySum(nums, 4, target);
    }
};
