#include <string>
#include <unordered_map>
#include <algorithm>

using std::max;
using std::string;
using std::unordered_map;

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

        auto record = unordered_map<char, int>();
        auto anchor = 0;

        auto maximun = 0;

        for (int i = 0; i != end; i++)
        {
            auto current = s[i];

            auto last = record.find(current);
            if (last == record.end())
            {
                record.emplace(current, i);
            }
            else
            {
                maximun = max(maximun, i - anchor);
                anchor = max(anchor, last->second + 1);

                last->second = i;
            }
        }

        return max(maximun, end - anchor);
    }
};