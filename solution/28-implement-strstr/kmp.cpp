#include <string>

using std::string;

class Solution
{
public:
    int strStr(string haystack, string needle)
    {
        return kmp(haystack, needle);
    }

private:
    static int kmp(const string &source, const string &target)
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

        auto next = new int[target_size]{-1, target[0] == target[1] ? -1 : 0};

        auto suffix_index = 1;
        auto prefix_index = 0;

        auto target_last = target_size - 1;
        while (target_last != suffix_index)
        {
            if (target[suffix_index] == target[prefix_index])
            {
                next[suffix_index] = next[prefix_index];

                suffix_index++;
                prefix_index++;

                next[suffix_index] = prefix_index;
            }
            else
            {
                auto _next = next[prefix_index];

                if (-1 == _next)
                {
                    suffix_index++;
                }
                else
                {
                    prefix_index = _next;
                }
            }
        }

        auto result = -1;
        for (auto i = 0, j = 0, end = (int)source.size(); end != i;)
        {
            if (source[i] == target[j])
            {
                if (target_last == j)
                {
                    result = i - j;
                    break;
                }
                i++;
                j++;
            }
            else
            {
                j = next[j];
                if (-1 == j)
                {
                    i++;
                    j = 0;
                }
            }
        }

        delete[] next;

        return result;
    }
};