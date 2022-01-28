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
        int virtual_center_of_farthest_vertex;
        int center_of_farthest_vertex;
        for (auto i = 1, end = virtual_size;
             i < end;
             i++)
        {
            auto center = i / 2;

            int left;
            int right;

            if (center < farthest_vertex)
            {
                auto mirror = 2 * virtual_center_of_farthest_vertex - i;
                auto radius = radius_record[mirror];
                auto virtual_radius = 2 * radius;

                left = (i - virtual_radius - 1) / 2;
                right = (i + virtual_radius) / 2 + 1;

                if (center_of_farthest_vertex < left && right <= farthest_vertex)
                {
                    radius_record[i] = (right - left + 1) / 2;
                    continue;
                }

                if (farthest_vertex < right - 1)
                {
                    radius_record[i] = farthest_vertex - center;
                    continue;
                }
            }
            else
            {
                left = (i - 1) / 2;
                right = center + 1;
            }

            for (; 0 <= left && right < size && s[left] == s[right]; left--, right++)
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

            right--;
            if (farthest_vertex < right)
            {
                virtual_center_of_farthest_vertex = i;
                center_of_farthest_vertex = i / 2;
                farthest_vertex = right;
            }
        }

        delete[] radius_record;

        return s.substr(longest_begin, longest_value);
    }
};
