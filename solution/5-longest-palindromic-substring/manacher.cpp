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
        auto virtual_size = size * 2 - 1;
        auto radius_record = new int[virtual_size]{0};

        auto farthest_vertex = 0;
        int virtual_center_of_farthest_vertex;
        for (auto i = 1, end = virtual_size; i < end; i++)
        {
            int left;
            int right;
            auto center = i / 2;

            if (center < farthest_vertex)
            {
                auto mirror = 2 * virtual_center_of_farthest_vertex - i;
                auto radius = radius_record[mirror];
                right = center + radius;
                if (farthest_vertex < right)
                {
                    continue;
                }
                else
                {
                    left = center + i % 2 - radius;
                }
            }
            else
            {
                right = center;
                left = center + i % 2;
            }

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

            right--;
            if (farthest_vertex < right)
            {
                virtual_center_of_farthest_vertex = i;
                farthest_vertex = right;
            }
        }

        delete[] radius_record;

        return s.substr(longest_begin, longest_value);
    }
};
