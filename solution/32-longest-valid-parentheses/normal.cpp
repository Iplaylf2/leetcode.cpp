#include <stack>
#include <string>

using std::max;
using std::stack;
using std::string;

class Solution
{
public:
    int longestValidParentheses(string s)
    {
        auto maximum = 0;
        auto count_stack = stack<int>();

        auto current_count = 0;
        for (auto x : s)
        {
            switch (x)
            {
            case '(':
                count_stack.push(current_count);
                current_count = 0;
                break;
            case ')':
                if (0 == count_stack.size())
                {
                    maximum = max(maximum, current_count);

                    current_count = 0;
                }
                else
                {
                    current_count += 2 + count_stack.top();
                    count_stack.pop();
                }
                break;
            }
        }

        maximum = max(maximum, current_count);

        while (!count_stack.empty())
        {
            maximum = max(maximum, count_stack.top());

            count_stack.pop();
        }

        return maximum;
    }
};