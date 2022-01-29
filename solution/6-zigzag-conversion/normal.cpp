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

        auto result = string(length, '\0');

        auto magic_nr = -1 + numRows;
        auto max_offset = 2 * magic_nr;

        auto i = 0;
        for (auto x = 0; x < length; x += max_offset)
        {
            result[i] = s[x];
            i++;
        }

        for (auto r = 1; r < magic_nr; r++)
        {
            for (auto x = r, offset = max_offset - 2 * r; x < length; x += offset, offset = max_offset - offset)
            {
                result[i] = s[x];
                i++;
            }
        }

        for (auto x = magic_nr; x < length; x += max_offset)
        {
            result[i] = s[x];
            i++;
        }

        return result;
    }

private:
    string twoRow(string &s)
    {
        int length = s.length();
        auto safe_length = 1 + length;

        auto result = string(safe_length, '\0');

        for (auto i = 0, end = safe_length / 2; i != end; i++)
        {
            auto x = 2 * i;

            result[i] = s[x];
            result[end + i] = s[1 + x];
        }

        result.pop_back();

        return result;
    }
};