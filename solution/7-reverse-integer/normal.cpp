class Solution
{
public:
    int reverse(int x)
    {
        long reverse = 0;
        while (x != 0)
        {
            reverse = 10 * reverse + x % 10;
            x /= 10;
        }

        int result = reverse;

        return result == reverse ? result : 0;
    }
};