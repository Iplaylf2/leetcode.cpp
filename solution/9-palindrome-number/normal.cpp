class Solution
{
public:
    bool isPalindrome(int x)
    {
        if (x < 0)
        {
            return false;
        }

        if (x == 0)
        {
            return true;
        }

        auto right = x % 10;
        if (right == 0)
        {
            return false;
        }

        for (x /= 10;
             right < x;
             right = 10 * right + x % 10, x /= 10)
            ;

        return right == x || (right / 10) == x;
    }
};