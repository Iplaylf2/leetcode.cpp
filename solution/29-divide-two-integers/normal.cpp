#include <cmath>

using std::signbit;

class Solution
{
public:
    int divide(int dividend, int divisor)
    {
        switch (divisor)
        {
        case -1:
            return INT_MIN == dividend ? INT_MAX : -dividend;
        case 1:
            return dividend;
        default:
            break;
        }

        if (INT_MIN == divisor)
        {
            return INT_MIN == dividend ? 1 : 0;
        }

        auto dividend_sign = signbit(dividend);
        auto divisor_sign = signbit(divisor);
        auto quotient_sign = dividend_sign != divisor_sign;

        if (divisor_sign)
        {
            divisor = -divisor;
        }

        if (dividend_sign)
        {
            dividend = -(dividend + divisor);
        }
        else
        {
            dividend -= divisor;
        }

        if (dividend < 0)
        {
            return 0;
        }
        auto quotient = 1;

        auto reverse = 0;
        for (auto x = dividend; divisor <= x; x >>= 1)
        {
            reverse++;
        }

        auto diff = dividend;
        while (0 < reverse)
        {
            reverse--;

            auto new_diff = diff - (divisor << reverse);
            if (0 == new_diff)
            {
                quotient += 1 << reverse;
                break;
            }
            else if (0 < new_diff)
            {
                quotient += 1 << reverse;
                diff = new_diff;
            }
        }

        return quotient_sign ? -quotient : quotient;
    }
};