#include <string>
#include <array>
#include <cmath>

using std::array;
using std::fill_n;
using std::max;
using std::string;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        return bm(haystack, needle);
    }

private:
    static int bm(const string &source, const string &target)
    {
        auto target_size = target.size();
        switch (target_size)
        {
        case 0:
            return 0;
        case 1:
        {
            auto x = target[0];
            for (auto i = 0, end = (int)source.size(); end != i; i++)
            {
                if (x == source[i])
                {
                    return i;
                }
            }
            return -1;
        }
        default:
            break;
        }

        auto source_size = source.size();
        if (source_size < target_size)
        {
            return -1;
        }

        auto _bad_char = array<int, 26>();
        _bad_char.fill(target_size);

        auto last = (int)target_size - 1;

        auto bad_char = _bad_char.data() - 'a';
        for (auto i = last - 1; - 1 != i; i--)
        {
            auto x = target[i];
            if (target_size == bad_char[x])
            {
                bad_char[x] = last - i;
            }
        }

        auto good_suffix = new int[target_size];
        good_suffix[last] = target_size;

        auto min_j = last;
        for (auto i = last - 1; - 1 != i;)
        {
            auto j = last;
            while (target[i] == target[j])
            {
                i--;
                j--;
                if (j < min_j)
                {
                    good_suffix[j] = j - i;
                    min_j = j;
                }

                if (-1 == i)
                {
                    goto finish_good_suffix;
                }
            }

            if (last == j)
            {
                i--;
            }
        }
    finish_good_suffix:
        for (auto i = 0, offset = good_suffix[min_j]; min_j != i; i++)
        {
            good_suffix[i] = offset;
        }
        good_suffix[last] = 1;

        auto result = -1;
        for (auto i = last; i < source_size;)
        {
            auto j = last;
            auto k = 0;
            while (source[i - k] == target[j - k])
            {
                if (last == k)
                {
                    result = i - k;
                    goto end;
                }

                k++;
            }

            auto offset = max(bad_char[source[i - k]] - k, good_suffix[j - k]);
            i += offset;
        }
    end:

        delete[] good_suffix;

        return result;
    }
};