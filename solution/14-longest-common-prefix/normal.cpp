#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution
{
public:
    string longestCommonPrefix(vector<string> &strs)
    {
        string result = "";
        auto first = strs[0];

        auto strs_size = strs.size();
        for (auto i = 0, end = (int)first.length(); end != i; i++)
        {
            auto c = first[i];

            for (auto j = 1; strs_size != j; j++)
            {
                if (c != strs[j][i])
                {
                    return result;
                }
            }

            result += c;
        }

        return result;
    }
};