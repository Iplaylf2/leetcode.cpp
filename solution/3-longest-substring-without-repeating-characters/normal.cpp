#include <string>
#include <array>
#include <algorithm>

using std::fill_n;
using std::max;
using std::string;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int end = s.size();
        switch (end)
        {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            break;
        }

        int record[127];
        fill_n(record, 127, -1);

        auto anchor = 0;

        auto maximun = 0;

        for (int i = 0; i != end; i++)
        {
            auto current = s[i];

            auto last = record[current];

            if (last != -1)
            {
                maximun = max(maximun, i - anchor);
                anchor = max(anchor, last + 1);
            }

            record[current] = i;
        }

        return max(maximun, end - anchor);
    }
};