#include <string>

using std::string;

class Solution
{
public:
    bool isValid(string s)
    {
        auto size = s.length();
        if (1 == size % 2)
        {
            return false;
        }

        auto stack = new char[size + 1]{0};

        auto i = 0;
        for (auto c : s)
        {
            switch (c)
            {
            case '(':
            case '{':
            case '[':
                i++;
                stack[i] = c;
                break;
            case ')':
                if ('(' != stack[i])
                {
                    return false;
                }
                i--;
                break;
            case '}':
                if ('{' != stack[i])
                {
                    return false;
                }
                i--;
                break;
            case ']':
                if ('[' != stack[i])
                {
                    return false;
                }
                i--;
                break;
            }
        }

        delete[] stack;

        return i == 0;
    }
};