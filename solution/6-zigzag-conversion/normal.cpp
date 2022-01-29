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

        auto magic_nr = -1 + numRows;
        auto max_offset = 2 * magic_nr;

        for (auto x = 0; x < length; x += max_offset)
        {
            result += s[x];
        }

        for (auto r = 1; r < magic_nr; r++)
        {
            for (auto x = r, offset = max_offset - 2 * r; x < length; x += offset, offset = max_offset - offset)
            {
                result += s[x];
            }
        }

        for (auto x = magic_nr; x < length; x += max_offset)
        {
            result += s[x];
        }

        return result;
    }

private:
    string twoRow(string &s)
    {
        int length = s.length();

        char result[length + 1];

        for (auto i = 0, end = (1 + length) / 2; i != end; i++)
        {
            auto x = 2 * i;

            result[i] = s[x];
            result[end + i] = s[1 + x];
        }

        result[length] = '\0';

        return result;
    }
};