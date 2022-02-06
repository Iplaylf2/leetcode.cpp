#include <string>
#include <vector>
#include <algorithm>

using std::move;
using std::string;
using std::transform;
using std::vector;

class Solution
{
public:
    vector<string> letterCombinations(string digits)
    {
        auto digit_ptr = digits.data();
        auto front = *digit_ptr;
        if ('\0' == front)
        {
            return {};
        }

        auto group = smart_dictionary[front];
        auto result = vector<string>(group.size());
        transform(group.begin(), group.end(), result.begin(), [](auto x)
                  { return string{x}; });

        for (auto current = *(++digit_ptr); '\0' != current; current = *(++digit_ptr))
        {
            auto group = smart_dictionary[current];
            auto new_result = vector<string>(result.size() * group.size());
            auto i = 0;
            for (auto x : result)
            {
                for (auto c : group)
                {
                    new_result[i] = x + c;
                    i++;
                }
            }

            result = move(new_result);
        }

        return result;
    }

private:
    static const string dictionary[8];
    static const string *smart_dictionary;
};

const string Solution::dictionary[8]{"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
const string *Solution::smart_dictionary = Solution::dictionary - '2';