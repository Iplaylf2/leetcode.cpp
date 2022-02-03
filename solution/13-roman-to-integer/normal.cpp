#include <string>

using std::string;

class Solution
{
public:
    int romanToInt(string s)
    {
        auto result = 0;

        auto s_ptr = s.data();
        while (true)
        {
            switch (*s_ptr)
            {
            case 'I':
                switch (s_ptr[1])
                {
                case 'V':
                    result += 4;
                    s_ptr += 2;
                    continue;
                case 'X':
                    result += 9;
                    s_ptr += 2;
                    continue;
                default:
                    result += 1;
                    break;
                }
                break;
            case 'V':
                result += 5;
                break;
            case 'X':
                switch (s_ptr[1])
                {
                case 'L':
                    result += 40;
                    s_ptr += 2;
                    continue;
                case 'C':
                    result += 90;
                    s_ptr += 2;
                    continue;
                default:
                    result += 10;
                    break;
                }
                break;
            case 'L':
                result += 50;
                break;
            case 'C':
                switch (s_ptr[1])
                {
                case 'D':
                    result += 400;
                    s_ptr += 2;
                    continue;
                case 'M':
                    result += 900;
                    s_ptr += 2;
                    continue;
                default:
                    result += 100;
                    break;
                }
                break;
            case 'D':
                result += 500;
                break;
            case 'M':
                result += 1000;
                break;
            default:
                return result;
            }
            s_ptr++;
        }

        return result; //never;
    }
};