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

        auto s_ptr = s.data();

        while (true)
        {
            if (*s_ptr != ' ')
            {
                break;
            }
            else
            {
                s_ptr++;
            }
        }

        auto x = *s_ptr;
        if ('0' <= x && x <= '9')
        {
            result = (x - '0');
            s_ptr++;
        }
        else if (x == '-')
        {
            sign = true;
            s_ptr++;
        }
        else if (x == '+')
        {
            s_ptr++;
        }
        else
        {
            return 0;
        }

        if (sign)
        {
            while (true)
            {
                x = *s_ptr;
                if ('0' <= x && x <= '9')
                {
                    result = 10 * result - (x - '0');
                    if (result <= INT_MIN)
                    {
                        return INT_MIN;
                    }
                    s_ptr++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            while (true)
            {
                x = *s_ptr;
                if ('0' <= x && x <= '9')
                {
                    result = 10 * result + (x - '0');
                    if (INT_MAX <= result)
                    {
                        return INT_MAX;
                    }
                    s_ptr++;
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