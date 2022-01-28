#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution
{
public:
    string longestPalindrome(string s)
    {
        auto longest_begin = 0;
        auto longest_value = 1;

        int size = s.size();
        auto virtual_size = 2 * size - 1;
        auto radius_record = new int[virtual_size];

        auto farthest_vertex = 0;
        int center_of_farthest_vertex;
        for (auto i = 1, end = virtual_size;
             i < end;
             i++)
        {
            int left;
            int right;

            if (i < farthest_vertex)
            {
                auto mirror = 2 * center_of_farthest_vertex - i;
                auto radius = radius_record[mirror];
                auto virtual_radius = 2 * radius;

                auto virtual_left = i - virtual_radius;
                if (center_of_farthest_vertex < virtual_left)
                {
                    radius_record[i] = radius;
                    continue;
                }

                auto virtual_right = i + virtual_radius;
                if (farthest_vertex < virtual_right)
                {
                    radius_record[i] = (farthest_vertex - center_of_farthest_vertex) / 2;
                    throw;
                }

                left = (virtual_left + 1) / 2;
                right = virtual_right / 2;
            }
            else
            {
                left = (i + 1) / 2;
                right = i / 2;
            }

            for (left--, right++; 0 <= left && right < size && s[left] == s[right]; left--, right++)
                ;

            auto length = right - left - 1;
            auto radius = length / 2;
            radius_record[i] = radius;

            if (longest_value < length)
            {
                longest_begin = left + 1;
                longest_value = length;
                end = virtual_size - longest_value;
            }

            auto virtual_right = i + radius * 2;
            if (farthest_vertex < virtual_right)
            {
                center_of_farthest_vertex = i;
                farthest_vertex = virtual_right;
            }
        }

        delete[] radius_record;

        return s.substr(longest_begin, longest_value);
    }
};
