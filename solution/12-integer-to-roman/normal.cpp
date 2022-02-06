#include <string>
#include <array>

using std::array;
using std::pair;
using std::string;

class Solution
{
public:
    string intToRoman(int num)
    {
        auto result = string();
        for (auto &[atom, s] : dictionary)
        {
            while (atom <= num)
            {
                result += s;
                num -= atom;
            }

            if (num == 0)
            {
                break;
            }
        }

        return result;
    }

private:
    static const pair<int, const char *> dictionary[13];
};

const pair<int, const char *> Solution::dictionary[]{{1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}};
