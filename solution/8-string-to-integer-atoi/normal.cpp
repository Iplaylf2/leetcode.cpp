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

        auto begin = s.data();

        while (true)
        {
            if (*begin != ' ')
            {
                break;
            }
            else
            {
                begin++;
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
            while (true)
            {
                x = *begin;
                if ('0' <= x && x <= '9')
                {
                    result = 10 * result - (x - '0');
                    if (result <= INT_MIN)
                    {
                        return INT_MIN;
                    }
                    begin++;
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
                x = *begin;
                if ('0' <= x && x <= '9')
                {
                    result = 10 * result + (x - '0');
                    if (INT_MAX <= result)
                    {
                        return INT_MAX;
                    }
                    begin++;
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