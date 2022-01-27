#include <string>
#include <array>

using std::array;
using std::string;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        int size = s.size();
        if (size == 1)
        {
            return s;
        }

        auto longest_begin = 0;
        auto longest_value = 1;

        auto virtual_size = size * 2 - 1;

        auto farthest_vertex = 0;
        auto center = 0;
        for (auto i = 1, end = virtual_size; i < end; i++)
        {
            auto mirror = 2 * center - i;
            auto virtual_radius = mirror < 0 ? 0 : radius_record[mirror] * 2;

            auto right = (i + virtual_radius) / 2;
            if (virtual_radius != 0 && farthest_vertex <= right)
            {
                continue;
            }

            auto left = (i - virtual_radius + 1) / 2;

            for (left--, right++; 0 <= left && right < size && s[left] == s[right]; left--, right++)
                ;

            auto length = right - left - 1;
            radius_record[i] = length / 2;

            if (longest_value < length)
            {
                longest_begin = left + 1;
                longest_value = length;
                end = virtual_size - longest_value;
            }

            if (farthest_vertex < right)
            {
                center = i;
                farthest_vertex = right;
            }
        }

        return s.substr(longest_begin, longest_value);
    }

private:
    array<int, 1000 * 2 - 1> radius_record;
};