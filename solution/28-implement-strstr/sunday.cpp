#include <string>
#include <array>

using std::array;
using std::string;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        return sunday(haystack, needle);
    }

private:
    static int sunday(const string &source, const string &target)
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

        auto _next = array<int, 26>();
        _next.fill(target_size);

        auto next = _next.data() - 'a';
        for (auto i = 0; target_size != i; i++)
        {
            auto x = target[target_size - i];
            if (target_size == next[x])
            {
                next[x] = i;
            }
        }

        auto target_last = (int)target_size - 1;
        auto end = source_size - target_size;
        for (auto i = 0; i < end;)
        {
            auto j = 0;
            while (source[i + j] == target[j])
            {
                if (target_last == j)
                {
                    return i;
                }

                j++;
            }

            i += next[source[i + target_size]];
        }

        for (auto j = 0; source[end + j] == target[j]; j++)
        {
            if (target_last == j)
            {
                return end;
            }
        }

        return -1;
    }
};