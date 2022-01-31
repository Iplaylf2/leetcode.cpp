#include <string>
#include <cmath>

using std::string;

class Solution
{
public:
    int myAtoi(string s)
    {
        long result = 0;
        auto sign = false;

        auto begin = s.begin();
        auto end = s.end();

        for (; begin != end; begin++)
        {
            auto x = *begin;
            if (x != ' ')
            {
                break;
            }
        }

        auto x = *begin;
        if ('0' <= x && x <= '9')
        {
            result = (x - '0');
            begin++;
        }
        else if (x == '-')
        {
            sign = true;
            begin++;
        }
        else if (x == '+')
        {
            begin++;
        }
        else
        {
            return 0;
        }

        if (sign)
        {
            for (; begin != end; begin++)
            {
                auto x = *begin;
                if ('0' <= x && x <= '9')
                {
                    result = 10 * result - (x - '0');
                    if (result <= INT_MIN)
                    {
                        return INT_MIN;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            for (; begin != end; begin++)
            {
                auto x = *begin;
                if ('0' <= x && x <= '9')
                {
                    result = 10 * result + (x - '0');
                    if (INT_MAX <= result)
                    {
                        return INT_MAX;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        return result;
    }
};