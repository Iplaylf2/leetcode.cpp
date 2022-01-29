#include <string>

using std::string;

class Solution
{
public:
    string convert(string s, int numRows)
    {
        switch (numRows)
        {
        case 1:
            return s;
        case 2:
            return twoRow(s);
        default:
            break;
        }

        int length = s.length();

        auto result = string();

        auto source = s.data();

        auto magic_nr = -1 + numRows;
        auto max_offset = 2 * magic_nr;

        for (auto x = 0; x < length; x += max_offset)
        {
            result += source[x];
        }

        for (auto r = 1; r < magic_nr; r++)
        {
            for (auto x = r, offset = max_offset - 2 * r; x < length; x += offset, offset = max_offset - offset)
            {
                result += source[x];
            }
        }

        for (auto x = magic_nr; x < length; x += max_offset)
        {
            result += source[x];
        }

        return result;
    }

private:
    string twoRow(string &s)
    {
        int length = s.length();

        auto r1 = string();
        auto r2 = string();

        auto source = s.data();

        for (auto i = 0, end = (1 + length) / 2; i != end; i++)
        {
            auto x = 2 * i;

            r1 += source[x];
            r2 += source[1 + x];
        }

        if (length % 2 == 1)
        {
            r2.pop_back();
        }

        return r1 + r2;
    }
};