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

        int s_length = s.length();
        auto begin_stack = new int[s_length + 1]{-1};
        int begin_stack_ptr = 0;

        for (int i = 0; s_length != i; i++)
        {
            if ('(' == s[i])
            {
                begin_stack_ptr++;
                begin_stack[begin_stack_ptr] = i;
            }
            else
            {
                if (0 == begin_stack_ptr)
                {
                    begin_stack[begin_stack_ptr] = i;
                }
                else
                {
                    begin_stack_ptr--;
                    maximum = max(maximum, i - begin_stack[begin_stack_ptr]);
                }
            }
        }

        delete[] begin_stack;

        return maximum;
    }
};